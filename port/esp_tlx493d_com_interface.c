#include <stdbool.h>

/** project interfaces includes. */
#include "CommunicationInterface.h"

/** project includes. */
#include "tlx493d_types.h"


bool tlx493d_transfer(TLx493D_t* sensor, uint8_t* txBuffer, uint8_t txLen, uint8_t* rxBuffer, uint8_t rxLen) {
    if (sensor->comIFType == TLx493D_I2C_e) {
        return sensor->comInterface.comLibFuncs->transfer.iic_transfer(
            sensor, txBuffer, txLen, rxBuffer, rxLen
        );
    }

    if (sensor->comIFType == TLx493D_SPI_e) {
        return sensor->comInterface.comLibFuncs->transfer.spi_transfer(
            sensor, txBuffer, txLen, rxBuffer, rxLen
        );
    }

    return false;
}

void tlx493d_setReadAddress(TLx493D_t* sensor, uint8_t address) {
    if (sensor->comIFType == TLx493D_I2C_e) {
        sensor->comInterface.comLibFuncs->setReadAddress.iic_setReadAddress(sensor, address);
    } else if (sensor->comIFType == TLx493D_SPI_e) {
        sensor->comInterface.comLibFuncs->setReadAddress.spi_setReadAddress(sensor, address);
    }
}

void deinitCommunication(TLx493D_t* sensor, bool executeDeinit) {
    /* TODO */
}
