/* This file is generated by venus-protocol.  See vn_protocol_driver.h. */

/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VN_PROTOCOL_DRIVER_SEMAPHORE_H
#define VN_PROTOCOL_DRIVER_SEMAPHORE_H

#include "vn_instance.h"
#include "vn_protocol_driver_structs.h"

/*
 * These structs/unions/commands are not included
 *
 *   vkGetSemaphoreFdKHR
 *   vkImportSemaphoreFdKHR
 */

/* struct VkExportSemaphoreCreateInfo chain */

static inline size_t
vn_sizeof_VkExportSemaphoreCreateInfo_pnext(const void *val)
{
    /* no known/supported struct */
    return vn_sizeof_simple_pointer(NULL);
}

static inline size_t
vn_sizeof_VkExportSemaphoreCreateInfo_self(const VkExportSemaphoreCreateInfo *val)
{
    size_t size = 0;
    /* skip val->{sType,pNext} */
    size += vn_sizeof_VkFlags(&val->handleTypes);
    return size;
}

static inline size_t
vn_sizeof_VkExportSemaphoreCreateInfo(const VkExportSemaphoreCreateInfo *val)
{
    size_t size = 0;

    size += vn_sizeof_VkStructureType(&val->sType);
    size += vn_sizeof_VkExportSemaphoreCreateInfo_pnext(val->pNext);
    size += vn_sizeof_VkExportSemaphoreCreateInfo_self(val);

    return size;
}

static inline void
vn_encode_VkExportSemaphoreCreateInfo_pnext(struct vn_cs_encoder *enc, const void *val)
{
    /* no known/supported struct */
    vn_encode_simple_pointer(enc, NULL);
}

static inline void
vn_encode_VkExportSemaphoreCreateInfo_self(struct vn_cs_encoder *enc, const VkExportSemaphoreCreateInfo *val)
{
    /* skip val->{sType,pNext} */
    vn_encode_VkFlags(enc, &val->handleTypes);
}

static inline void
vn_encode_VkExportSemaphoreCreateInfo(struct vn_cs_encoder *enc, const VkExportSemaphoreCreateInfo *val)
{
    assert(val->sType == VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO);
    vn_encode_VkStructureType(enc, &(VkStructureType){ VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO });
    vn_encode_VkExportSemaphoreCreateInfo_pnext(enc, val->pNext);
    vn_encode_VkExportSemaphoreCreateInfo_self(enc, val);
}

/* struct VkSemaphoreCreateInfo chain */

static inline size_t
vn_sizeof_VkSemaphoreCreateInfo_pnext(const void *val)
{
    const VkBaseInStructure *pnext = val;
    size_t size = 0;

    while (pnext) {
        switch ((int32_t)pnext->sType) {
        case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO:
            size += vn_sizeof_simple_pointer(pnext);
            size += vn_sizeof_VkStructureType(&pnext->sType);
            size += vn_sizeof_VkSemaphoreCreateInfo_pnext(pnext->pNext);
            size += vn_sizeof_VkExportSemaphoreCreateInfo_self((const VkExportSemaphoreCreateInfo *)pnext);
            return size;
        case VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO:
            size += vn_sizeof_simple_pointer(pnext);
            size += vn_sizeof_VkStructureType(&pnext->sType);
            size += vn_sizeof_VkSemaphoreCreateInfo_pnext(pnext->pNext);
            size += vn_sizeof_VkSemaphoreTypeCreateInfo_self((const VkSemaphoreTypeCreateInfo *)pnext);
            return size;
        default:
            /* ignore unknown/unsupported struct */
            break;
        }
        pnext = pnext->pNext;
    }

    return vn_sizeof_simple_pointer(NULL);
}

static inline size_t
vn_sizeof_VkSemaphoreCreateInfo_self(const VkSemaphoreCreateInfo *val)
{
    size_t size = 0;
    /* skip val->{sType,pNext} */
    size += vn_sizeof_VkFlags(&val->flags);
    return size;
}

static inline size_t
vn_sizeof_VkSemaphoreCreateInfo(const VkSemaphoreCreateInfo *val)
{
    size_t size = 0;

    size += vn_sizeof_VkStructureType(&val->sType);
    size += vn_sizeof_VkSemaphoreCreateInfo_pnext(val->pNext);
    size += vn_sizeof_VkSemaphoreCreateInfo_self(val);

    return size;
}

static inline void
vn_encode_VkSemaphoreCreateInfo_pnext(struct vn_cs_encoder *enc, const void *val)
{
    const VkBaseInStructure *pnext = val;

    while (pnext) {
        switch ((int32_t)pnext->sType) {
        case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO:
            vn_encode_simple_pointer(enc, pnext);
            vn_encode_VkStructureType(enc, &pnext->sType);
            vn_encode_VkSemaphoreCreateInfo_pnext(enc, pnext->pNext);
            vn_encode_VkExportSemaphoreCreateInfo_self(enc, (const VkExportSemaphoreCreateInfo *)pnext);
            return;
        case VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO:
            vn_encode_simple_pointer(enc, pnext);
            vn_encode_VkStructureType(enc, &pnext->sType);
            vn_encode_VkSemaphoreCreateInfo_pnext(enc, pnext->pNext);
            vn_encode_VkSemaphoreTypeCreateInfo_self(enc, (const VkSemaphoreTypeCreateInfo *)pnext);
            return;
        default:
            /* ignore unknown/unsupported struct */
            break;
        }
        pnext = pnext->pNext;
    }

    vn_encode_simple_pointer(enc, NULL);
}

static inline void
vn_encode_VkSemaphoreCreateInfo_self(struct vn_cs_encoder *enc, const VkSemaphoreCreateInfo *val)
{
    /* skip val->{sType,pNext} */
    vn_encode_VkFlags(enc, &val->flags);
}

static inline void
vn_encode_VkSemaphoreCreateInfo(struct vn_cs_encoder *enc, const VkSemaphoreCreateInfo *val)
{
    assert(val->sType == VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO);
    vn_encode_VkStructureType(enc, &(VkStructureType){ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO });
    vn_encode_VkSemaphoreCreateInfo_pnext(enc, val->pNext);
    vn_encode_VkSemaphoreCreateInfo_self(enc, val);
}

/* struct VkSemaphoreWaitInfo chain */

static inline size_t
vn_sizeof_VkSemaphoreWaitInfo_pnext(const void *val)
{
    /* no known/supported struct */
    return vn_sizeof_simple_pointer(NULL);
}

static inline size_t
vn_sizeof_VkSemaphoreWaitInfo_self(const VkSemaphoreWaitInfo *val)
{
    size_t size = 0;
    /* skip val->{sType,pNext} */
    size += vn_sizeof_VkFlags(&val->flags);
    size += vn_sizeof_uint32_t(&val->semaphoreCount);
    if (val->pSemaphores) {
        size += vn_sizeof_array_size(val->semaphoreCount);
        for (uint32_t i = 0; i < val->semaphoreCount; i++)
            size += vn_sizeof_VkSemaphore(&val->pSemaphores[i]);
    } else {
        size += vn_sizeof_array_size(0);
    }
    if (val->pValues) {
        size += vn_sizeof_array_size(val->semaphoreCount);
        size += vn_sizeof_uint64_t_array(val->pValues, val->semaphoreCount);
    } else {
        size += vn_sizeof_array_size(0);
    }
    return size;
}

static inline size_t
vn_sizeof_VkSemaphoreWaitInfo(const VkSemaphoreWaitInfo *val)
{
    size_t size = 0;

    size += vn_sizeof_VkStructureType(&val->sType);
    size += vn_sizeof_VkSemaphoreWaitInfo_pnext(val->pNext);
    size += vn_sizeof_VkSemaphoreWaitInfo_self(val);

    return size;
}

static inline void
vn_encode_VkSemaphoreWaitInfo_pnext(struct vn_cs_encoder *enc, const void *val)
{
    /* no known/supported struct */
    vn_encode_simple_pointer(enc, NULL);
}

static inline void
vn_encode_VkSemaphoreWaitInfo_self(struct vn_cs_encoder *enc, const VkSemaphoreWaitInfo *val)
{
    /* skip val->{sType,pNext} */
    vn_encode_VkFlags(enc, &val->flags);
    vn_encode_uint32_t(enc, &val->semaphoreCount);
    if (val->pSemaphores) {
        vn_encode_array_size(enc, val->semaphoreCount);
        for (uint32_t i = 0; i < val->semaphoreCount; i++)
            vn_encode_VkSemaphore(enc, &val->pSemaphores[i]);
    } else {
        vn_encode_array_size(enc, 0);
    }
    if (val->pValues) {
        vn_encode_array_size(enc, val->semaphoreCount);
        vn_encode_uint64_t_array(enc, val->pValues, val->semaphoreCount);
    } else {
        vn_encode_array_size(enc, 0);
    }
}

static inline void
vn_encode_VkSemaphoreWaitInfo(struct vn_cs_encoder *enc, const VkSemaphoreWaitInfo *val)
{
    assert(val->sType == VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO);
    vn_encode_VkStructureType(enc, &(VkStructureType){ VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO });
    vn_encode_VkSemaphoreWaitInfo_pnext(enc, val->pNext);
    vn_encode_VkSemaphoreWaitInfo_self(enc, val);
}

/* struct VkSemaphoreSignalInfo chain */

static inline size_t
vn_sizeof_VkSemaphoreSignalInfo_pnext(const void *val)
{
    /* no known/supported struct */
    return vn_sizeof_simple_pointer(NULL);
}

static inline size_t
vn_sizeof_VkSemaphoreSignalInfo_self(const VkSemaphoreSignalInfo *val)
{
    size_t size = 0;
    /* skip val->{sType,pNext} */
    size += vn_sizeof_VkSemaphore(&val->semaphore);
    size += vn_sizeof_uint64_t(&val->value);
    return size;
}

static inline size_t
vn_sizeof_VkSemaphoreSignalInfo(const VkSemaphoreSignalInfo *val)
{
    size_t size = 0;

    size += vn_sizeof_VkStructureType(&val->sType);
    size += vn_sizeof_VkSemaphoreSignalInfo_pnext(val->pNext);
    size += vn_sizeof_VkSemaphoreSignalInfo_self(val);

    return size;
}

static inline void
vn_encode_VkSemaphoreSignalInfo_pnext(struct vn_cs_encoder *enc, const void *val)
{
    /* no known/supported struct */
    vn_encode_simple_pointer(enc, NULL);
}

static inline void
vn_encode_VkSemaphoreSignalInfo_self(struct vn_cs_encoder *enc, const VkSemaphoreSignalInfo *val)
{
    /* skip val->{sType,pNext} */
    vn_encode_VkSemaphore(enc, &val->semaphore);
    vn_encode_uint64_t(enc, &val->value);
}

static inline void
vn_encode_VkSemaphoreSignalInfo(struct vn_cs_encoder *enc, const VkSemaphoreSignalInfo *val)
{
    assert(val->sType == VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO);
    vn_encode_VkStructureType(enc, &(VkStructureType){ VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO });
    vn_encode_VkSemaphoreSignalInfo_pnext(enc, val->pNext);
    vn_encode_VkSemaphoreSignalInfo_self(enc, val);
}

/* struct VkImportSemaphoreResourceInfoMESA chain */

static inline size_t
vn_sizeof_VkImportSemaphoreResourceInfoMESA_pnext(const void *val)
{
    /* no known/supported struct */
    return vn_sizeof_simple_pointer(NULL);
}

static inline size_t
vn_sizeof_VkImportSemaphoreResourceInfoMESA_self(const VkImportSemaphoreResourceInfoMESA *val)
{
    size_t size = 0;
    /* skip val->{sType,pNext} */
    size += vn_sizeof_VkSemaphore(&val->semaphore);
    size += vn_sizeof_uint32_t(&val->resourceId);
    return size;
}

static inline size_t
vn_sizeof_VkImportSemaphoreResourceInfoMESA(const VkImportSemaphoreResourceInfoMESA *val)
{
    size_t size = 0;

    size += vn_sizeof_VkStructureType(&val->sType);
    size += vn_sizeof_VkImportSemaphoreResourceInfoMESA_pnext(val->pNext);
    size += vn_sizeof_VkImportSemaphoreResourceInfoMESA_self(val);

    return size;
}

static inline void
vn_encode_VkImportSemaphoreResourceInfoMESA_pnext(struct vn_cs_encoder *enc, const void *val)
{
    /* no known/supported struct */
    vn_encode_simple_pointer(enc, NULL);
}

static inline void
vn_encode_VkImportSemaphoreResourceInfoMESA_self(struct vn_cs_encoder *enc, const VkImportSemaphoreResourceInfoMESA *val)
{
    /* skip val->{sType,pNext} */
    vn_encode_VkSemaphore(enc, &val->semaphore);
    vn_encode_uint32_t(enc, &val->resourceId);
}

static inline void
vn_encode_VkImportSemaphoreResourceInfoMESA(struct vn_cs_encoder *enc, const VkImportSemaphoreResourceInfoMESA *val)
{
    assert(val->sType == VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_RESOURCE_INFO_MESA);
    vn_encode_VkStructureType(enc, &(VkStructureType){ VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_RESOURCE_INFO_MESA });
    vn_encode_VkImportSemaphoreResourceInfoMESA_pnext(enc, val->pNext);
    vn_encode_VkImportSemaphoreResourceInfoMESA_self(enc, val);
}

static inline size_t vn_sizeof_vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreateSemaphore_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_simple_pointer(pCreateInfo);
    if (pCreateInfo)
        cmd_size += vn_sizeof_VkSemaphoreCreateInfo(pCreateInfo);
    cmd_size += vn_sizeof_simple_pointer(pAllocator);
    if (pAllocator)
        assert(false);
    cmd_size += vn_sizeof_simple_pointer(pSemaphore);
    if (pSemaphore)
        cmd_size += vn_sizeof_VkSemaphore(pSemaphore);

    return cmd_size;
}

static inline void vn_encode_vkCreateSemaphore(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreateSemaphore_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    if (vn_encode_simple_pointer(enc, pCreateInfo))
        vn_encode_VkSemaphoreCreateInfo(enc, pCreateInfo);
    if (vn_encode_simple_pointer(enc, pAllocator))
        assert(false);
    if (vn_encode_simple_pointer(enc, pSemaphore))
        vn_encode_VkSemaphore(enc, pSemaphore);
}

static inline size_t vn_sizeof_vkCreateSemaphore_reply(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreateSemaphore_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    VkResult ret;
    cmd_size += vn_sizeof_VkResult(&ret);
    /* skip device */
    /* skip pCreateInfo */
    /* skip pAllocator */
    cmd_size += vn_sizeof_simple_pointer(pSemaphore);
    if (pSemaphore)
        cmd_size += vn_sizeof_VkSemaphore(pSemaphore);

    return cmd_size;
}

static inline VkResult vn_decode_vkCreateSemaphore_reply(struct vn_cs_decoder *dec, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkCreateSemaphore_EXT);

    VkResult ret;
    vn_decode_VkResult(dec, &ret);
    /* skip device */
    /* skip pCreateInfo */
    /* skip pAllocator */
    if (vn_decode_simple_pointer(dec)) {
        vn_decode_VkSemaphore(dec, pSemaphore);
    } else {
        pSemaphore = NULL;
    }

    return ret;
}

static inline size_t vn_sizeof_vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroySemaphore_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_VkSemaphore(&semaphore);
    cmd_size += vn_sizeof_simple_pointer(pAllocator);
    if (pAllocator)
        assert(false);

    return cmd_size;
}

static inline void vn_encode_vkDestroySemaphore(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroySemaphore_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    vn_encode_VkSemaphore(enc, &semaphore);
    if (vn_encode_simple_pointer(enc, pAllocator))
        assert(false);
}

static inline size_t vn_sizeof_vkDestroySemaphore_reply(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroySemaphore_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip device */
    /* skip semaphore */
    /* skip pAllocator */

    return cmd_size;
}

static inline void vn_decode_vkDestroySemaphore_reply(struct vn_cs_decoder *dec, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkDestroySemaphore_EXT);

    /* skip device */
    /* skip semaphore */
    /* skip pAllocator */
}

static inline size_t vn_sizeof_vkGetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkGetSemaphoreCounterValue_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_VkSemaphore(&semaphore);
    cmd_size += vn_sizeof_simple_pointer(pValue); /* out */

    return cmd_size;
}

static inline void vn_encode_vkGetSemaphoreCounterValue(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkGetSemaphoreCounterValue_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    vn_encode_VkSemaphore(enc, &semaphore);
    vn_encode_simple_pointer(enc, pValue); /* out */
}

static inline size_t vn_sizeof_vkGetSemaphoreCounterValue_reply(VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkGetSemaphoreCounterValue_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    VkResult ret;
    cmd_size += vn_sizeof_VkResult(&ret);
    /* skip device */
    /* skip semaphore */
    cmd_size += vn_sizeof_simple_pointer(pValue);
    if (pValue)
        cmd_size += vn_sizeof_uint64_t(pValue);

    return cmd_size;
}

static inline VkResult vn_decode_vkGetSemaphoreCounterValue_reply(struct vn_cs_decoder *dec, VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkGetSemaphoreCounterValue_EXT);

    VkResult ret;
    vn_decode_VkResult(dec, &ret);
    /* skip device */
    /* skip semaphore */
    if (vn_decode_simple_pointer(dec)) {
        vn_decode_uint64_t(dec, pValue);
    } else {
        pValue = NULL;
    }

    return ret;
}

static inline size_t vn_sizeof_vkWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWaitSemaphores_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_simple_pointer(pWaitInfo);
    if (pWaitInfo)
        cmd_size += vn_sizeof_VkSemaphoreWaitInfo(pWaitInfo);
    cmd_size += vn_sizeof_uint64_t(&timeout);

    return cmd_size;
}

static inline void vn_encode_vkWaitSemaphores(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWaitSemaphores_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    if (vn_encode_simple_pointer(enc, pWaitInfo))
        vn_encode_VkSemaphoreWaitInfo(enc, pWaitInfo);
    vn_encode_uint64_t(enc, &timeout);
}

static inline size_t vn_sizeof_vkWaitSemaphores_reply(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWaitSemaphores_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    VkResult ret;
    cmd_size += vn_sizeof_VkResult(&ret);
    /* skip device */
    /* skip pWaitInfo */
    /* skip timeout */

    return cmd_size;
}

static inline VkResult vn_decode_vkWaitSemaphores_reply(struct vn_cs_decoder *dec, VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkWaitSemaphores_EXT);

    VkResult ret;
    vn_decode_VkResult(dec, &ret);
    /* skip device */
    /* skip pWaitInfo */
    /* skip timeout */

    return ret;
}

static inline size_t vn_sizeof_vkSignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSignalSemaphore_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_simple_pointer(pSignalInfo);
    if (pSignalInfo)
        cmd_size += vn_sizeof_VkSemaphoreSignalInfo(pSignalInfo);

    return cmd_size;
}

static inline void vn_encode_vkSignalSemaphore(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSignalSemaphore_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    if (vn_encode_simple_pointer(enc, pSignalInfo))
        vn_encode_VkSemaphoreSignalInfo(enc, pSignalInfo);
}

static inline size_t vn_sizeof_vkSignalSemaphore_reply(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSignalSemaphore_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    VkResult ret;
    cmd_size += vn_sizeof_VkResult(&ret);
    /* skip device */
    /* skip pSignalInfo */

    return cmd_size;
}

static inline VkResult vn_decode_vkSignalSemaphore_reply(struct vn_cs_decoder *dec, VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkSignalSemaphore_EXT);

    VkResult ret;
    vn_decode_VkResult(dec, &ret);
    /* skip device */
    /* skip pSignalInfo */

    return ret;
}

static inline size_t vn_sizeof_vkWaitSemaphoreResourceMESA(VkDevice device, VkSemaphore semaphore)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWaitSemaphoreResourceMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_VkSemaphore(&semaphore);

    return cmd_size;
}

static inline void vn_encode_vkWaitSemaphoreResourceMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, VkSemaphore semaphore)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWaitSemaphoreResourceMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    vn_encode_VkSemaphore(enc, &semaphore);
}

static inline size_t vn_sizeof_vkWaitSemaphoreResourceMESA_reply(VkDevice device, VkSemaphore semaphore)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWaitSemaphoreResourceMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip device */
    /* skip semaphore */

    return cmd_size;
}

static inline void vn_decode_vkWaitSemaphoreResourceMESA_reply(struct vn_cs_decoder *dec, VkDevice device, VkSemaphore semaphore)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkWaitSemaphoreResourceMESA_EXT);

    /* skip device */
    /* skip semaphore */
}

static inline size_t vn_sizeof_vkImportSemaphoreResourceMESA(VkDevice device, const VkImportSemaphoreResourceInfoMESA* pImportSemaphoreResourceInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkImportSemaphoreResourceMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_simple_pointer(pImportSemaphoreResourceInfo);
    if (pImportSemaphoreResourceInfo)
        cmd_size += vn_sizeof_VkImportSemaphoreResourceInfoMESA(pImportSemaphoreResourceInfo);

    return cmd_size;
}

static inline void vn_encode_vkImportSemaphoreResourceMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkImportSemaphoreResourceInfoMESA* pImportSemaphoreResourceInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkImportSemaphoreResourceMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    if (vn_encode_simple_pointer(enc, pImportSemaphoreResourceInfo))
        vn_encode_VkImportSemaphoreResourceInfoMESA(enc, pImportSemaphoreResourceInfo);
}

static inline size_t vn_sizeof_vkImportSemaphoreResourceMESA_reply(VkDevice device, const VkImportSemaphoreResourceInfoMESA* pImportSemaphoreResourceInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkImportSemaphoreResourceMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip device */
    /* skip pImportSemaphoreResourceInfo */

    return cmd_size;
}

static inline void vn_decode_vkImportSemaphoreResourceMESA_reply(struct vn_cs_decoder *dec, VkDevice device, const VkImportSemaphoreResourceInfoMESA* pImportSemaphoreResourceInfo)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkImportSemaphoreResourceMESA_EXT);

    /* skip device */
    /* skip pImportSemaphoreResourceInfo */
}

static inline void vn_submit_vkCreateSemaphore(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkCreateSemaphore_reply(device, pCreateInfo, pAllocator, pSemaphore) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkCreateSemaphore(enc, cmd_flags, device, pCreateInfo, pAllocator, pSemaphore);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkDestroySemaphore(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkDestroySemaphore(device, semaphore, pAllocator);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkDestroySemaphore_reply(device, semaphore, pAllocator) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkDestroySemaphore(enc, cmd_flags, device, semaphore, pAllocator);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkGetSemaphoreCounterValue(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, VkDevice device, VkSemaphore semaphore, uint64_t* pValue, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkGetSemaphoreCounterValue(device, semaphore, pValue);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkGetSemaphoreCounterValue_reply(device, semaphore, pValue) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkGetSemaphoreCounterValue(enc, cmd_flags, device, semaphore, pValue);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkWaitSemaphores(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkWaitSemaphores(device, pWaitInfo, timeout);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkWaitSemaphores_reply(device, pWaitInfo, timeout) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkWaitSemaphores(enc, cmd_flags, device, pWaitInfo, timeout);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkSignalSemaphore(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkSignalSemaphore(device, pSignalInfo);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkSignalSemaphore_reply(device, pSignalInfo) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkSignalSemaphore(enc, cmd_flags, device, pSignalInfo);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkWaitSemaphoreResourceMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, VkDevice device, VkSemaphore semaphore, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkWaitSemaphoreResourceMESA(device, semaphore);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkWaitSemaphoreResourceMESA_reply(device, semaphore) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkWaitSemaphoreResourceMESA(enc, cmd_flags, device, semaphore);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkImportSemaphoreResourceMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkImportSemaphoreResourceInfoMESA* pImportSemaphoreResourceInfo, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkImportSemaphoreResourceMESA(device, pImportSemaphoreResourceInfo);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkImportSemaphoreResourceMESA_reply(device, pImportSemaphoreResourceInfo) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkImportSemaphoreResourceMESA(enc, cmd_flags, device, pImportSemaphoreResourceInfo);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline VkResult vn_call_vkCreateSemaphore(struct vn_instance *vn_instance, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkCreateSemaphore(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, pCreateInfo, pAllocator, pSemaphore, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        const VkResult ret = vn_decode_vkCreateSemaphore_reply(dec, device, pCreateInfo, pAllocator, pSemaphore);
        vn_instance_free_command_reply(vn_instance, &submit);
        return ret;
    } else {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
}

static inline void vn_async_vkCreateSemaphore(struct vn_instance *vn_instance, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkCreateSemaphore(vn_instance, 0, device, pCreateInfo, pAllocator, pSemaphore, &submit);
}

static inline void vn_call_vkDestroySemaphore(struct vn_instance *vn_instance, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkDestroySemaphore(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, semaphore, pAllocator, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkDestroySemaphore_reply(dec, device, semaphore, pAllocator);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkDestroySemaphore(struct vn_instance *vn_instance, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkDestroySemaphore(vn_instance, 0, device, semaphore, pAllocator, &submit);
}

static inline VkResult vn_call_vkGetSemaphoreCounterValue(struct vn_instance *vn_instance, VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkGetSemaphoreCounterValue(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, semaphore, pValue, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        const VkResult ret = vn_decode_vkGetSemaphoreCounterValue_reply(dec, device, semaphore, pValue);
        vn_instance_free_command_reply(vn_instance, &submit);
        return ret;
    } else {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
}

static inline void vn_async_vkGetSemaphoreCounterValue(struct vn_instance *vn_instance, VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkGetSemaphoreCounterValue(vn_instance, 0, device, semaphore, pValue, &submit);
}

static inline VkResult vn_call_vkWaitSemaphores(struct vn_instance *vn_instance, VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkWaitSemaphores(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, pWaitInfo, timeout, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        const VkResult ret = vn_decode_vkWaitSemaphores_reply(dec, device, pWaitInfo, timeout);
        vn_instance_free_command_reply(vn_instance, &submit);
        return ret;
    } else {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
}

static inline void vn_async_vkWaitSemaphores(struct vn_instance *vn_instance, VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkWaitSemaphores(vn_instance, 0, device, pWaitInfo, timeout, &submit);
}

static inline VkResult vn_call_vkSignalSemaphore(struct vn_instance *vn_instance, VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkSignalSemaphore(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, pSignalInfo, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        const VkResult ret = vn_decode_vkSignalSemaphore_reply(dec, device, pSignalInfo);
        vn_instance_free_command_reply(vn_instance, &submit);
        return ret;
    } else {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
}

static inline void vn_async_vkSignalSemaphore(struct vn_instance *vn_instance, VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkSignalSemaphore(vn_instance, 0, device, pSignalInfo, &submit);
}

static inline void vn_call_vkWaitSemaphoreResourceMESA(struct vn_instance *vn_instance, VkDevice device, VkSemaphore semaphore)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkWaitSemaphoreResourceMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, semaphore, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkWaitSemaphoreResourceMESA_reply(dec, device, semaphore);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkWaitSemaphoreResourceMESA(struct vn_instance *vn_instance, VkDevice device, VkSemaphore semaphore)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkWaitSemaphoreResourceMESA(vn_instance, 0, device, semaphore, &submit);
}

static inline void vn_call_vkImportSemaphoreResourceMESA(struct vn_instance *vn_instance, VkDevice device, const VkImportSemaphoreResourceInfoMESA* pImportSemaphoreResourceInfo)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkImportSemaphoreResourceMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, pImportSemaphoreResourceInfo, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkImportSemaphoreResourceMESA_reply(dec, device, pImportSemaphoreResourceInfo);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkImportSemaphoreResourceMESA(struct vn_instance *vn_instance, VkDevice device, const VkImportSemaphoreResourceInfoMESA* pImportSemaphoreResourceInfo)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkImportSemaphoreResourceMESA(vn_instance, 0, device, pImportSemaphoreResourceInfo, &submit);
}

#endif /* VN_PROTOCOL_DRIVER_SEMAPHORE_H */
