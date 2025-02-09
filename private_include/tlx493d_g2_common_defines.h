#pragma once

#ifndef TLX493D_G2_COMMON_DEFINES_H
#define TLX493D_G2_COMMON_DEFINES_H


/** Register map. */
#define GEN_2_REG_MAP_SIZE                          23

/** Sensor general defines. */
#define GEN_2_FULL_RANGE_FIELD_SENSITIVITY          7.7
#define GEN_2_SHORT_RANGE_FIELD_SENSITIVITY         15.4
#define GEN_2_EXTRA_SHORT_RANGE_FIELD_SENSITIVITY   30.8

#define GEN_2_TEMP_RESOLUTION                       0.24
#define GEN_2_TEMP_OFFSET                           1180.0
#define GEN_2_TEMP_REF                              25.0

/** IIC address for generation 2. */
#define GEN_2_STD_IIC_ADDR_WRITE_A0                 0x6A
#define GEN_2_STD_IIC_ADDR_READ_A0                  0x6B

#define GEN_2_STD_IIC_ADDR_WRITE_A1                 0x44
#define GEN_2_STD_IIC_ADDR_READ_A1                  0x45

#define GEN_2_STD_IIC_ADDR_WRITE_A2                 0xF0
#define GEN_2_STD_IIC_ADDR_READ_A2                  0xF1

#define GEN_2_STD_IIC_ADDR_WRITE_A3                 0x88
#define GEN_2_STD_IIC_ADDR_READ_A3                  0x89


#endif // TLX493D_G2_COMMON_DEFINES_H
