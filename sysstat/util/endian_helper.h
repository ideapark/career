/*
 * sysstat/util/endian_helper.h - endian converting helper
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#ifndef ENDIAN_HELPER_H
#define ENDIAN_HELPER_H

#include <stdint.h>
#include "core/config.h"

int16_t static inline NTOH16(int16_t x, int32_t magic)
{
    if (magic == SYSSTAT_MAGIC)
        return x;
    else
        return ((((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8));
}

int32_t static inline NTOH32(int32_t x, int32_t magic)
{
    if (magic == SYSSTAT_MAGIC)
        return x;
    else
        return ((((x) & 0x000000ff) << 24) |
                (((x) & 0x0000ff00) <<  8) |
                (((x) & 0x00ff0000) >>  8) |
                (((x) & 0xff000000) >> 24));
}

#endif /* ENDIAN_HELPER_H */
