#pragma once

#ifndef TLX493D_G1_COMMON_DEFINES_H
#define TLX493D_G1_COMMON_DEFINES_H


/** Register map. */
#define GEN_1_REG_MAP_SIZE                          14
#define GEN_1_READ_REGISTERS_MAX_COUNT              10
#define GEN_1_WRITE_REGISTERS_MAX_COUNT             4
#define GEN_1_WRITE_REGISTERS_OFFSET                10

#define GEN_1_BITFIELDS_COUNT                       28

/** Sensor general defines. */
#define GEN_1_TEMP_REF                              25.0
#define GEN_1_TEMP_MULT                             1.10
#define GEN_1_TEMP_OFFSET                           340.0

#define GEN_1_MAG_FIELD_MULT                        0.098

/**
 * IIC address for generation 1.
 * (A0-A3 - for SDA/ADDR high at power-up).
 * (A4-A7 - for SDA/ADDR low at power-up).
 */
#define GEN_1_STD_IIC_ADDR                          0xBC
#define GEN_1_STD_IIC_ADDR_WRITE_A0                 0xBC
#define GEN_1_STD_IIC_ADDR_WRITE_A1                 0xB4
#define GEN_1_STD_IIC_ADDR_WRITE_A2                 0x9C
#define GEN_1_STD_IIC_ADDR_WRITE_A3                 0x94
#define GEN_1_STD_IIC_ADDR_WRITE_A4                 0x3E
#define GEN_1_STD_IIC_ADDR_WRITE_A5                 0x36
#define GEN_1_STD_IIC_ADDR_WRITE_A6                 0x1E
#define GEN_1_STD_IIC_ADDR_WRITE_A7                 0x16


#endif // TLX493D_G1_COMMON_DEFINES_H
