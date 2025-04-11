#pragma once

/** project includes. */
#include "../../tlx493d-arduino/src/tlx493d_types.h"

/** ESP-IDF includes. */
#include "driver/i2c_master.h"


bool tlx493d_init_com_iic(TLx493D_t* sensor, i2c_master_bus_handle_t bus_handle, TLx493D_IICAddressType_t iicAdr);
