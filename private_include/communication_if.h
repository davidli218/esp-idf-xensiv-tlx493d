#pragma once

#ifndef TLX493D_COMMUNICATION_IF_H
#define TLX493D_COMMUNICATION_IF_H

#include <stdbool.h>
#include <stdint.h>

#include "driver/i2c_master.h"

#include "tlx493d_types.h"


bool tlx493d_initCommunication_IIC(
    TLx493D_t* sensor, i2c_master_bus_handle_t* i2cBusHandle, uint8_t i2cAddress
);

/**
 * @brief The function `tlx493d_transfer` is a generic function to transfer data.
 * It is implemented for each communication interface offered by the different senors (SPI, I2C, etc.).
 * 
 * @param[in, out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in, out] txBuffer Buffer for the data that should be transferred.
 * @param[in] txLen Length of the transfer buffer.
 * @param[in, out] rxBuffer Buffer for the data that should be received.
 * @param[in] rxLen Length of the reception buffer.
 * 
 * @return The function `tlx493d_transfer` is returning a boolean value.
 * @retval false Error.
 * @retval true Transfer of the data was successful.
*/
bool tlx493d_transfer(TLx493D_t* sensor, uint8_t* txBuffer, uint8_t txLen, uint8_t* rxBuffer, uint8_t rxLen);

/**
 * @brief The function `tlx493d_setReadAddress` sets the address for the communication interface.
 * This address will be used to communicate with the used sensor device.
 * 
 * @param[in, out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in] address Desired read address for the communication interface.
*/
void tlx493d_setReadAddress(TLx493D_t* sensor, uint8_t address);

/**
 * @brief The function `deinitCommunication` is used to de-initialize the communication interface of the used sensor.
 * 
 * @param[in, out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in] executeDeinit Boolean value to determine if the communication interface should be de-initialized or not.
*/
void tlx493d_deinitCommunication(TLx493D_t* sensor, bool executeDeinit);


#endif // TLX493D_COMMUNICATION_IF_H
