#pragma once

/** ESP-IDF includes. */
#include "driver/i2c_master.h"


struct TLx493D_I2CObject_t {
    i2c_master_bus_handle_t i2c_bus_handle;
    i2c_master_dev_handle_t i2c_dev;
};
