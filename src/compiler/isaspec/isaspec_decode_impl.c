/*
 * Copyright © 2020 Google, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* This file should not be built directly. Instead, it is included in the C
 * file generated by isaspec/decode.py and built along with it.
 */

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/bitset.h"
#include "util/compiler.h"
#include "util/half_float.h"
#include "util/hash_table.h"
#include "util/ralloc.h"
#include "util/u_debug.h"
#include "util/u_math.h"

#include "isa.h"

/**
 * The set of leaf node bitsets in the bitset hiearchy which defines all
 * the possible instructions.
 *
 * TODO maybe we want to pass this in as parameter so this same decoder
 * can work with multiple different instruction sets.
 */
extern const struct isa_bitset *__instruction[];

struct decode_state;

/**
 * Decode scope.  When parsing a field that is itself a bitset, we push a
 * new scope to the stack.  A nested bitset is allowed to resolve fields
 * from an enclosing scope (needed, for example, to decode src register
 * bitsets, where half/fullness is determined by fields outset if bitset
 * in the instruction containing the bitset.
 *
 * But the field being resolved could be a derived field, or different
 * depending on an override at a higher level of the stack, requiring
 * expression evaluation which could in turn reference variables which
 * triggers a recursive field lookup.  But those lookups should not start
 * from the top of the stack, but instead the current stack level.  This
 * prevents a field from accidentally resolving to different values
 * depending on the starting point of the lookup.  (Not only causing
 * confusion, but this is behavior we don't want to depend on if we
 * wanted to optimize things by caching field lookup results.)
 */
struct decode_scope {
	/**
	 * Enclosing scope
	 */
	struct decode_scope *parent;

	/**
	 * Current bitset value being decoded
	 */
	bitmask_t val;

	/**
	 * Current bitset.
	 */
	const struct isa_bitset *bitset;

	/**
	 * Field name remapping.
	 */
	const struct isa_field_params *params;

	/**
	 * Pointer back to decode state, for convenience.
	 */
	struct decode_state *state;

	/**
	 * Cache expression evaluation results.  Expressions for overrides can
	 * be repeatedly evaluated for each field being resolved.  And each
	 * field reference to a derived field (potentially from another expr)
	 * would require re-evaluation.  But for a given scope, each evaluation
	 * of an expression gives the same result.  So we can cache to speed
	 * things up.
	 *
	 * TODO we could maybe be clever and assign a unique idx to each expr
	 * and use a direct lookup table?  Would be a bit more clever if it was
	 * smart enough to allow unrelated expressions that are never involved
	 * in a given scope to have overlapping cache lookup idx's.
	 */
	struct hash_table *cache;
};

/**
 * Current decode state
 */
struct decode_state {
	const struct isa_decode_options *options;
	FILE *out;

	/**
	 * Current instruction being decoded:
	 */
	unsigned n;

	/**
	 * Number of instructions being decoded
	 */
	unsigned num_instr;

	/**
	 * Column number of current line
	 */
	unsigned line_column;

	/**
	 * Bitset of instructions that are branch targets (if options->branch_labels
	 * is enabled)
	 */
	BITSET_WORD *branch_targets;

	/**
	 * We allow a limited amount of expression evaluation recursion, but
	 * not recursive evaluation of any given expression, to prevent infinite
	 * recursion.
	 */
	int expr_sp;
	isa_expr_t expr_stack[8];

	/**
	 * Current topmost/innermost level of scope used for decoding fields,
	 * including derived fields which may in turn rely on decoding other
	 * fields, potentially from a lower/out level in the stack.
	 */
	struct decode_scope *scope;

	/**
	 * A small fixed upper limit on # of decode errors to capture per-
	 * instruction seems reasonable.
	 */
	unsigned num_errors;
	char *errors[4];
};

static void
print(struct decode_state *state, const char *fmt, ...)
{
	char *buffer;
	va_list args;
	int ret;

	va_start(args, fmt);
	ret = vasprintf(&buffer, fmt, args);
	va_end(args);

	if (ret != -1) {
		const size_t len = strlen(buffer);

		for (size_t i = 0; i < len; i++) {
			const char c = buffer[i];

			fputc(c, state->out);
			state->line_column++;

			if (c == '\n') {
				state->line_column = 0;
			}
      }

		free(buffer);

		return;
	}
}

static void display(struct decode_scope *scope);
static void decode_error(struct decode_state *state, const char *fmt, ...) _util_printf_format(2,3);

static void
decode_error(struct decode_state *state, const char *fmt, ...)
{
	if (!state->options->show_errors) {
		return;
	}

	if (state->num_errors == ARRAY_SIZE(state->errors)) {
		/* too many errors, bail */
		return;
	}

	va_list ap;
	va_start(ap, fmt);
	vasprintf(&state->errors[state->num_errors++], fmt, ap);
	va_end(ap);
}

static unsigned
flush_errors(struct decode_state *state)
{
	unsigned num_errors = state->num_errors;
	if (num_errors > 0)
		print(state, "\t; ");
	for (unsigned i = 0; i < num_errors; i++) {
		print(state, "%s%s", (i > 0) ? ", " : "", state->errors[i]);
		free(state->errors[i]);
	}
	state->num_errors = 0;
	return num_errors;
}


static bool
push_expr(struct decode_state *state, isa_expr_t expr)
{
	for (int i = state->expr_sp - 1; i > 0; i--) {
		if (state->expr_stack[i] == expr) {
			return false;
		}
	}
	state->expr_stack[state->expr_sp++] = expr;
	return true;
}

static void
pop_expr(struct decode_state *state)
{
	assert(state->expr_sp > 0);
	state->expr_sp--;
}

static struct decode_scope *
push_scope(struct decode_state *state, const struct isa_bitset *bitset, bitmask_t val)
{
	struct decode_scope *scope = rzalloc_size(state, sizeof(*scope));

	BITSET_COPY(scope->val.bitset, val.bitset);
	scope->bitset = bitset;
	scope->parent = state->scope;
	scope->state  = state;

	state->scope = scope;

	return scope;
}

static void
pop_scope(struct decode_scope *scope)
{
	assert(scope->state->scope == scope);  /* must be top of stack */

	scope->state->scope = scope->parent;
	ralloc_free(scope);
}

/**
 * Evaluate an expression, returning it's resulting value
 */
static uint64_t
evaluate_expr(struct decode_scope *scope, isa_expr_t expr)
{
	if (scope->cache) {
		struct hash_entry *entry = _mesa_hash_table_search(scope->cache, expr);
		if (entry) {
			return *(uint64_t *)entry->data;
		}
	} else {
		scope->cache = _mesa_pointer_hash_table_create(scope);
	}

	if (!push_expr(scope->state, expr))
		return 0;

	uint64_t ret = expr(scope);

	pop_expr(scope->state);

	uint64_t *retp = ralloc_size(scope->cache, sizeof(*retp));
	*retp = ret;
	_mesa_hash_table_insert(scope->cache, expr, retp);

	return ret;
}

/**
 * Find the bitset in NULL terminated bitset hiearchy root table which
 * matches against 'val'
 */
static const struct isa_bitset *
find_bitset(struct decode_state *state, const struct isa_bitset **bitsets,
		bitmask_t val)
{
	const struct isa_bitset *match = NULL;
	for (int n = 0; bitsets[n]; n++) {
		if (state->options->gpu_id > bitsets[n]->gen.max)
			continue;
		if (state->options->gpu_id < bitsets[n]->gen.min)
			continue;

		// m = (val & bitsets[n]->mask) & ~bitsets[n]->dontcare;
		bitmask_t m = { 0 };
		bitmask_t not_dontcare;

		BITSET_AND(m.bitset, val.bitset, bitsets[n]->mask.bitset);

		BITSET_COPY(not_dontcare.bitset, bitsets[n]->dontcare.bitset);
		BITSET_NOT(not_dontcare.bitset);

		BITSET_AND(m.bitset, m.bitset, not_dontcare.bitset);

		if (!BITSET_EQUAL(m.bitset, bitsets[n]->match.bitset)) {
			continue;
		}

		/* We should only have exactly one match
		 *
		 * TODO more complete/formal way to validate that any given
		 * bit pattern will only have a single match?
		 */
		if (match) {
			decode_error(state, "bitset conflict: %s vs %s", match->name,
					bitsets[n]->name);
			return NULL;
		}

		match = bitsets[n];
	}

	if (match) {
		bitmask_t m = { 0 };
		BITSET_AND(m.bitset, match->dontcare.bitset, val.bitset);

		if (BITSET_COUNT(m.bitset)) {
			decode_error(state, "dontcare bits in %s: %"BITSET_FORMAT,
					match->name, BITSET_VALUE(m.bitset));
		}
	}

	return match;
}

static const struct isa_field *
find_field(struct decode_scope *scope, const struct isa_bitset *bitset,
		const char *name, size_t name_len)
{
	for (unsigned i = 0; i < bitset->num_cases; i++) {
		const struct isa_case *c = bitset->cases[i];

		if (c->expr) {
			struct decode_state *state = scope->state;

			/* When resolving a field for evaluating an expression,
			 * temporarily assume the expression evaluates to true.
			 * This allows <override/>'s to speculatively refer to
			 * fields defined within the override:
			 */
			isa_expr_t cur_expr = NULL;
			if (state->expr_sp > 0)
				cur_expr = state->expr_stack[state->expr_sp - 1];
			if ((cur_expr != c->expr) && !evaluate_expr(scope, c->expr))
				continue;
		}

		for (unsigned i = 0; i < c->num_fields; i++) {
			if (!strncmp(name, c->fields[i].name, name_len) &&
			   (c->fields[i].name[name_len] == '\0')) {
				return &c->fields[i];
			}
		}
	}

	if (bitset->parent) {
		const struct isa_field *f = find_field(scope, bitset->parent, name, name_len);
		if (f) {
			return f;
		}
	}

	return NULL;
}

static bitmask_t
extract_field(struct decode_scope *scope, const struct isa_field *field)
{
   bitmask_t val, mask;

   BITSET_COPY(val.bitset, scope->val.bitset);
   BITSET_ZERO(mask.bitset);

   BITSET_SET_RANGE(mask.bitset, field->low, field->high);
   BITSET_AND(val.bitset, val.bitset, mask.bitset);
   BITSET_SHR(val.bitset, field->low);

   return val;
}

/**
 * Find the display template for a given bitset, recursively searching
 * parents in the bitset hierarchy.
 */
static const char *
find_display(struct decode_scope *scope, const struct isa_bitset *bitset)
{
	for (unsigned i = 0; i < bitset->num_cases; i++) {
		const struct isa_case *c = bitset->cases[i];
		if (c->expr && !evaluate_expr(scope, c->expr))
			continue;
		/* since this is the chosen case, it seems like a good place
		 * to check asserted bits:
		 */
		for (unsigned j = 0; j < c->num_fields; j++) {
			if (c->fields[j].type == TYPE_ASSERT) {
				const struct isa_field *f = &c->fields[j];
				bitmask_t val;

				val = extract_field(scope, f);
				if (!BITSET_EQUAL(val.bitset, f->val.bitset)) {
					decode_error(scope->state, "WARNING: unexpected "
							"bits[%u:%u] in %s: %"BITSET_FORMAT" vs %"BITSET_FORMAT,
							f->low, f->high, bitset->name,
							BITSET_VALUE(val.bitset), BITSET_VALUE(f->val.bitset));
				}
			}
		}
		if (!c->display)
			continue;
		return c->display;
	}

	/**
	 * If we didn't find something check up the bitset hierarchy.
	 */
	if (bitset->parent) {
		return find_display(scope, bitset->parent);
	}

	return NULL;
}

/**
 * Decode a field that is itself another bitset type
 */
static void
display_bitset_field(struct decode_scope *scope, const struct isa_field *field, bitmask_t val)
{
	const struct isa_bitset *b = find_bitset(scope->state, field->bitsets, val);
	if (!b) {
		decode_error(scope->state, "no match: FIELD: '%s.%s': %"BITSET_FORMAT,
				scope->bitset->name, field->name, BITSET_VALUE(val.bitset));
		return;
	}

	struct decode_scope *nested_scope =
			push_scope(scope->state, b, val);
	nested_scope->params = field->params;
	display(nested_scope);
	pop_scope(nested_scope);
}

static void
display_enum_field(struct decode_scope *scope, const struct isa_field *field, bitmask_t val)
{
	const struct isa_enum *e = field->enums;
	const uint64_t ui = bitmask_to_uint64_t(val);

	for (unsigned i = 0; i < e->num_values; i++) {
		if (e->values[i].val == ui) {
			print(scope->state, "%s", e->values[i].display);
			return;
		}
	}

	print(scope->state, "%u", (unsigned)ui);
}

static const struct isa_field *
resolve_field(struct decode_scope *scope, const char *field_name, size_t field_name_len, bitmask_t *valp)
{
	if (!scope) {
		/* We've reached the bottom of the stack! */
		return NULL;
	}

	const struct isa_field *field =
			find_field(scope, scope->bitset, field_name, field_name_len);

	if (!field && scope->params) {
		for (unsigned i = 0; i < scope->params->num_params; i++) {
			if (!strncmp(field_name, scope->params->params[i].as, field_name_len) &&
			   (scope->params->params[i].as[field_name_len] == '\0')) {
				const char *param_name = scope->params->params[i].name;
				return resolve_field(scope->parent, param_name, strlen(param_name), valp);
			}
		}
	}

	if (!field) {
		return NULL;
	}

	/* extract out raw field value: */
	if (field->expr) {
		uint64_t val = evaluate_expr(scope, field->expr);

		*valp = uint64_t_to_bitmask(val);
	} else {
		*valp = extract_field(scope, field);
	}

	return field;
}

/* This is also used from generated expr functions */
uint64_t
isa_decode_field(struct decode_scope *scope, const char *field_name)
{
	bitmask_t val;
	const struct isa_field *field = resolve_field(scope, field_name, strlen(field_name), &val);
	if (!field) {
		decode_error(scope->state, "no field '%s'", field_name);
		return 0;
	}

	return bitmask_to_uint64_t(val);
}

static void
display_field(struct decode_scope *scope, const char *field_name)
{
	const struct isa_decode_options *options = scope->state->options;
	struct decode_state *state = scope->state;
	size_t field_name_len = strlen(field_name);
	int num_align = 0;

	/* alignment handling */
	const char *align = strstr(field_name, ":align=");

	if (align) {
		const char *value = strstr(align, "=") + 1;

		field_name_len = align - field_name;
		num_align = atoi(value);
	}

	/* Special case ':algin=' should only do alignment */
	if (field_name == align) {
		while (scope->state->line_column < num_align)
			print(state, " ");

		return;
	}

	/* Special case 'NAME' maps to instruction/bitset name: */
	if (!strncmp("NAME", field_name, field_name_len)) {
		if (options->field_cb) {
			options->field_cb(options->cbdata, field_name, &(struct isa_decode_value){
				.str = scope->bitset->name,
			});
		}

		while (scope->state->line_column < num_align)
			print(state, " ");

		print(scope->state, "%s", scope->bitset->name);

		return;
	}

	bitmask_t v;
	const struct isa_field *field = resolve_field(scope, field_name, field_name_len, &v);
	if (!field) {
		decode_error(scope->state, "no field '%.*s'", (int)field_name_len, field_name);
		return;
	}

	uint64_t val = bitmask_to_uint64_t(v);

	if (options->field_cb) {
		options->field_cb(options->cbdata, field_name, &(struct isa_decode_value){
			.num = val,
		});
	}

	unsigned width = 1 + field->high - field->low;

	while (scope->state->line_column < num_align)
		print(state, " ");

	switch (field->type) {
	/* Basic types: */
	case TYPE_BRANCH:
		if (scope->state->options->branch_labels) {
			int offset = util_sign_extend(val, width) + scope->state->n;
			if (offset < scope->state->num_instr) {
				print(scope->state, "l%d", offset);
				BITSET_SET(scope->state->branch_targets, offset);
				break;
			}
		}
		FALLTHROUGH;
	case TYPE_INT:
		print(scope->state, "%"PRId64, util_sign_extend(val, width));
		break;
	case TYPE_UINT:
		print(scope->state, "%"PRIu64, val);
		break;
	case TYPE_HEX:
		// TODO format # of digits based on field width?
		print(scope->state, "%"PRIx64, val);
		break;
	case TYPE_OFFSET:
		if (val != 0) {
			print(scope->state, "%+"PRId64, util_sign_extend(val, width));
		}
		break;
	case TYPE_UOFFSET:
		if (val != 0) {
			print(scope->state, "+%"PRIu64, val);
		}
		break;
	case TYPE_FLOAT:
		if (width == 16) {
			print(scope->state, "%f", _mesa_half_to_float(val));
		} else {
			assert(width == 32);
			print(scope->state, "%f", uif(val));
		}
		break;
	case TYPE_BOOL:
		if (field->display) {
			if (val) {
				print(scope->state, "%s", field->display);
			}
		} else {
			print(scope->state, "%u", (unsigned)val);
		}
		break;
	case TYPE_ENUM:
		display_enum_field(scope, field, v);
		break;

	case TYPE_ASSERT:
		/* assert fields are not for display */
		assert(0);
		break;

	/* For fields that are decoded with another bitset hierarchy: */
	case TYPE_BITSET:
		display_bitset_field(scope, field, v);
		break;
	default:
		decode_error(scope->state, "Bad field type: %d (%s)",
				field->type, field->name);
	}
}

static void
display(struct decode_scope *scope)
{
	const struct isa_bitset *bitset = scope->bitset;
	const char *display = find_display(scope, bitset);

	if (!display) {
		decode_error(scope->state, "%s: no display template", bitset->name);
		return;
	}

	const char *p = display;

	while (*p != '\0') {
		if (*p == '{') {
			const char *e = ++p;
			while (*e != '}') {
				e++;
			}

			char *field_name = strndup(p, e-p);
			display_field(scope, field_name);
			free(field_name);

			p = e;
		} else {
			fputc(*p, scope->state->out);
			scope->state->line_column++;
		}
		p++;
	}
}

static void
decode(struct decode_state *state, void *bin, int sz)
{
	BITSET_WORD *instrs = bin;
	unsigned errors = 0;   /* number of consecutive unmatched instructions */

	assert(sz % BITMASK_WORDS == 0);

	for (state->n = 0; state->n < state->num_instr; state->n++) {
		bitmask_t instr = { 0 };

		next_instruction(&instr, &instrs[state->n * BITMASK_WORDS]);
      state->line_column = 0;

		if (state->options->max_errors && (errors > state->options->max_errors)) {
			break;
		}

		if (state->options->branch_labels &&
				BITSET_TEST(state->branch_targets, state->n)) {
			if (state->options->instr_cb) {
				state->options->instr_cb(state->options->cbdata,
						state->n, instr.bitset);
			}
			print(state, "l%d:\n", state->n);
		}

		if (state->options->instr_cb) {
			state->options->instr_cb(state->options->cbdata, state->n, instr.bitset);
		}

		const struct isa_bitset *b = find_bitset(state, __instruction, instr);
		if (!b) {
			if (state->options->no_match_cb) {
				state->options->no_match_cb(state->out, instr.bitset, BITMASK_WORDS);
			} else {
				print(state, "no match: %"BITSET_FORMAT"\n", BITSET_VALUE(instr.bitset));
			}
			errors++;
			continue;
		}

		struct decode_scope *scope = push_scope(state, b, instr);

		display(scope);
		if (flush_errors(state)) {
			errors++;
		} else {
			errors = 0;
		}
		print(state, "\n");

		pop_scope(scope);

		if (state->options->stop) {
			break;
		}
	}
}

void
isa_decode(void *bin, int sz, FILE *out, const struct isa_decode_options *options)
{
	const struct isa_decode_options default_options = {
		.gpu_id = options ? options->gpu_id : 0,
		.branch_labels = options ? options->branch_labels : false
	};
	struct decode_state *state;

	if (!options)
		options = &default_options;

	state = rzalloc_size(NULL, sizeof(*state));
	state->options = options;
	state->num_instr = sz / (BITMASK_WORDS * sizeof(BITSET_WORD));

	if (state->options->branch_labels) {
		state->branch_targets = rzalloc_size(state,
				sizeof(BITSET_WORD) * BITSET_WORDS(state->num_instr));

		/* Do a pre-pass to find all the branch targets: */
		state->out = fopen("/dev/null", "w");
		state->options = &default_options;   /* skip hooks for prepass */
		decode(state, bin, sz);
		fclose(state->out);
		if (options) {
			state->options = options;
		}
	}

	state->out = out;

	decode(state, bin, sz);

	ralloc_free(state);
}
