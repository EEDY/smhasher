/* crc32_simd.h
 *
 * Copyright 2017 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the Chromium source repository LICENSE file.
 */

#include <stdint.h>
#include <stddef.h>


#define ZLIB_INTERNAL

typedef size_t z_size_t;




#if defined (USE_SSE42_CRC32C)

#define COMP_CRC32C_CHROMIUM(crc, data, len) \
    ((crc) = crc32_sse42_simd_((data), (len), (crc)))

/*
 * crc32_sse42_simd_(): compute the crc32 of the buffer, where the buffer
 * length must be at least 64, and a multiple of 16.
 */
uint32_t ZLIB_INTERNAL crc32_sse42_simd_(
    const unsigned char *buf,
    z_size_t len,
    uint32_t crc);

/*
 * crc32_sse42_simd_ buffer size constraints: see the use in zlib/crc32.c
 * for computing the crc32 of an arbitrary length buffer.
 */
#define Z_CRC32_SSE42_MINIMUM_LENGTH 64
#define Z_CRC32_SSE42_CHUNKSIZE_MASK 15

#elif defined(USE_ARMV8_CRC32C)

#define COMP_CRC32C_CHROMIUM(crc, data, len) \
    ((crc) = armv8_crc32_little((crc), (data), (len)))

/*
 * CRC32 checksums using ARMv8-a crypto instructions.
 */
uint32_t ZLIB_INTERNAL armv8_crc32_little(unsigned long crc,
                                          const unsigned char* buf,
                                          z_size_t len);

#endif
