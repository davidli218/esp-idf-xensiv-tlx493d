// ReSharper disable CppParameterMayBeConstPtrOrRef
// ReSharper disable CppParameterMayBeConst

#include <stdlib.h>

/** project includes. */
#include "Logger.h"

/** ESP-IDF port includes. */
#include "esp_tlx493d_base_types.h"
#include "esp_tlx493d_com_iic.h"


static bool initIIC(TLx493D_t* sensor) {
    const i2c_device_config_t i2c_dev_config = {
        .scl_speed_hz = 400000,
        .device_address = sensor->comInterface.comLibParams.iic_params.address
    };

    i2c_master_bus_add_device(
        sensor->comInterface.comLibObj.iic_obj->i2c_bus_handle,
        &i2c_dev_config, &sensor->comInterface.comLibObj.iic_obj->i2c_dev
    );

    return true;
}

static bool deinitIIC(TLx493D_t* sensor) {
    if (sensor->comInterface.comLibObj.iic_obj->i2c_dev != NULL) {
        i2c_master_bus_rm_device(sensor->comInterface.comLibObj.iic_obj->i2c_dev);
        sensor->comInterface.comLibObj.iic_obj->i2c_dev = NULL;
    }

    return true;
}

static bool transferIIC(TLx493D_t* sensor, uint8_t* txBuffer, uint8_t txLen, uint8_t* rxBuffer, uint8_t rxLen) {
    if ((txLen > 0) && (txBuffer != NULL)) {
        i2c_master_transmit(
            sensor->comInterface.comLibObj.iic_obj->i2c_dev, txBuffer, txLen, -1
        );
    }

    if ((rxLen > 0) && (rxBuffer != NULL)) {
        i2c_master_receive(
            sensor->comInterface.comLibObj.iic_obj->i2c_dev, rxBuffer, rxLen, -1
        );
    }

    return true;
}

static void setReadAddressIIC(TLx493D_t* sensor, uint8_t address) {
    (void)sensor;
    (void)address;
    logWarn("Function 'setReadAddressIIC' not supported !");
}

static TLx493D_ComLibraryFunctions_t comLibFuncs_iic = {
    .init = {.iic_init = initIIC},
    .deinit = {.iic_deinit = deinitIIC},
    .transfer = {.iic_transfer = transferIIC},
    .setReadAddress = {.iic_setReadAddress = setReadAddressIIC},
};

bool tlx493d_init_com_iic(TLx493D_t* sensor, i2c_master_bus_handle_t bus_handle, TLx493D_IICAddressType_t iicAdr) {
    sensor->comInterface.comLibObj.iic_obj = (TLx493D_I2CObject_t*)malloc(sizeof(TLx493D_I2CObject_t));

    if (sensor->comInterface.comLibObj.iic_obj == NULL) {
        return (false);
    }

    sensor->comInterface.comLibObj.iic_obj->i2c_bus_handle = bus_handle;
    sensor->comInterface.comLibObj.iic_obj->i2c_dev = NULL;

    sensor->comInterface.comLibFuncs = &comLibFuncs_iic;
    sensor->comInterface.comLibParams.iic_params.address = sensor->functions->selectIICAddress(sensor, iicAdr) >> 1;

    sensor->comInterface.comLibFuncs->init.iic_init(sensor);

    return true;
}
