#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "esp_log.h"

#include "tlx493d_common.h"
#include "tlx493d_types.h"
#include "communication_if.h"


static const char* TAG = "tlx493d_common";


/**************************************************************
 *                    1. Init and Deinit.                     *
 **************************************************************/

bool tlx493d_common_init(
    TLx493D_t* sensor,
    const uint8_t regMapSize, TLx493D_Register_t* regDef, TLx493D_CommonFunctions_t* commonFuncs,
    const TLx493D_SupportedSensorType_t sensorType, const TLx493D_SupportedComLibraryInterfaceType_t comIFType
) {
    sensor->regMap = (uint8_t*)malloc(sizeof(uint8_t) * regMapSize);

    if (sensor->regMap == NULL) {
        ESP_LOGE(TAG, "Malloc regMap failed !");
        return false;
    }

    sensor->regDef = regDef;
    sensor->functions = commonFuncs;
    sensor->regMapSize = regMapSize;
    sensor->sensorType = sensorType;
    sensor->comIFType = comIFType;

    sensor->comInterface.comLibFuncs = NULL;
    sensor->comInterface.comLibObj.iic_obj = NULL;

    (void)memset(sensor->regMap, 0, sensor->regMapSize);
    sensor->functions->setResetValues(sensor);

    return true;
}

bool tlx493d_common_deinit(TLx493D_t* sensor) {
    if (sensor->regMap != NULL) {
        free(sensor->regMap);
        sensor->regMap = NULL;
    }

    sensor->comInterface.comLibFuncs = NULL;
    sensor->comInterface.comLibObj.iic_obj = NULL;

    return true;
}


/**************************************************************
 *              2. Register & Bitfield Access.                *
 **************************************************************/

static bool tlx493d_hasNotOnly0xFFInRegmap(const TLx493D_t* sensor) {
    /* Skip address 0 ! Seems to be ok even if other entries are not. */
    for (uint8_t i = 1; i < sensor->regMapSize; ++i) {
        if (sensor->regMap[i] != 0xFFU) { return true; }
    }

    return false;
}

/**
 * Only applicable for generation 2 and 3, not 1.
 */
bool tlx493d_common_readRegisters(TLx493D_t* sensor) {
    bool isOk = tlx493d_transfer(sensor, NULL, 0, sensor->regMap, sensor->regMapSize);

    isOk &= tlx493d_hasNotOnly0xFFInRegmap(sensor);

    return isOk;
}

/**
 * Only applicable for generation 2 and 3, not 1.
 */
bool tlx493d_common_readRegistersAndCheck(TLx493D_t* sensor) {
    uint8_t regMapSnapshot[sensor->regMapSize];

    (void)memcpy(regMapSnapshot, sensor->regMap, sensor->regMapSize);

    do {
        bool isOk = tlx493d_transfer(sensor, NULL, 0, sensor->regMap, sensor->regMapSize);
        isOk &= tlx493d_hasNotOnly0xFFInRegmap(sensor);

        if (!(isOk && sensor->functions->hasValidData(sensor) && sensor->functions->hasValidFuseParity(sensor))) {
            (void)memcpy(sensor->regMap, regMapSnapshot, sensor->regMapSize);
        } else {
            break;
        }
    } while (true);

    return true;
}

bool tlx493d_common_writeRegister(TLx493D_t* sensor, const uint8_t bitField) {
    const TLx493D_Register_t* bf = &sensor->regDef[bitField];

    if (bf->accessMode == TLx493D_WRITE_MODE_e || bf->accessMode == TLx493D_READ_WRITE_MODE_e) {
        uint8_t transBuffer[2] = {bf->address, sensor->regMap[bf->address]};

        return tlx493d_transfer(sensor, transBuffer, sizeof(transBuffer), NULL, 0);
    }

    return false;
}

uint8_t tlx493d_common_returnBitfield(const TLx493D_t* sensor, const uint8_t bitField) {
    const TLx493D_Register_t* bf = &sensor->regDef[bitField];

    if (bf->accessMode == TLx493D_READ_MODE_e || bf->accessMode == TLx493D_READ_WRITE_MODE_e) {
        return (sensor->regMap[bf->address] & bf->mask) >> bf->offset;
    }

    tlx493d_errorBitfieldNotReadableForSensorType(sensor, bitField);
    return 0U;
}

void tlx493d_common_getBitfield(const TLx493D_t* sensor, const uint8_t bitField, uint8_t* bitFieldValue) {
    *bitFieldValue = tlx493d_common_returnBitfield(sensor, bitField);
}

void tlx493d_common_setBitfield(const TLx493D_t* sensor, const uint8_t bitField, const uint8_t newBitFieldValue) {
    const TLx493D_Register_t* bf = &sensor->regDef[bitField];

    if (bf->accessMode == TLx493D_WRITE_MODE_e || bf->accessMode == TLx493D_READ_WRITE_MODE_e) {
        sensor->regMap[bf->address] = (uint8_t)(
            sensor->regMap[bf->address] & (uint8_t)~bf->mask | newBitFieldValue << bf->offset & bf->mask
        );
    } else {
        tlx493d_errorBitfieldNotWritableForSensorType(sensor, bitField);
    }
}


/**************************************************************
 *                  3. Sensor Data Access.                    *
 **************************************************************/

void tlx493d_common_calculateRawTemperature(
    const TLx493D_t* sensor, const uint8_t tempMSBBF, const uint8_t tempLSBBF, int16_t* temperature
) {
    tlx493d_common_concatBytes(sensor, tempMSBBF, tempLSBBF, temperature);
}

bool tlx493d_common_getRawTemperature(TLx493D_t* sensor, int16_t* temperature) {
    if (sensor->functions->readRegistersAndCheck(sensor)) {
        sensor->functions->calculateRawTemperature(sensor, temperature);
        return true;
    }

    return false;
}

void tlx493d_common_calculateRawMagneticField(
    const TLx493D_t* sensor,
    const uint8_t bxMSBBF, const uint8_t bxLSBBF,
    const uint8_t byMSBBF, const uint8_t byLSBBF,
    const uint8_t bzMSBBF, const uint8_t bzLSBBF,
    int16_t* x, int16_t* y, int16_t* z
) {
    tlx493d_common_concatBytes(sensor, bxMSBBF, bxLSBBF, x);
    tlx493d_common_concatBytes(sensor, byMSBBF, byLSBBF, y);
    tlx493d_common_concatBytes(sensor, bzMSBBF, bzLSBBF, z);
}

bool tlx493d_common_getRawMagneticField(TLx493D_t* sensor, int16_t* x, int16_t* y, int16_t* z) {
    if (sensor->functions->readRegistersAndCheck(sensor)) {
        sensor->functions->calculateRawMagneticField(sensor, x, y, z);
        return true;
    }

    return false;
}

bool tlx493d_common_getRawMagneticFieldAndTemperature(
    TLx493D_t* sensor, int16_t* x, int16_t* y, int16_t* z, int16_t* temperature
) {
    if (sensor->functions->readRegistersAndCheck(sensor)) {
        sensor->functions->calculateRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
        return true;
    }

    return false;
}

bool tlx493d_common_getTemperature(TLx493D_t* sensor, double* temperature) {
    if (sensor->functions->readRegistersAndCheck(sensor)) {
        sensor->functions->calculateTemperature(sensor, temperature);
        return true;
    }

    return false;
}

bool tlx493d_common_getMagneticField(TLx493D_t* sensor, double* x, double* y, double* z) {
    if (sensor->functions->readRegistersAndCheck(sensor)) {
        sensor->functions->calculateMagneticField(sensor, x, y, z);
        return true;
    }

    return false;
}

bool tlx493d_common_getMagneticFieldAndTemperature(
    TLx493D_t* sensor, double* x, double* y, double* z, double* temperature
) {
    if (sensor->functions->readRegistersAndCheck(sensor)) {
        sensor->functions->calculateMagneticFieldAndTemperature(sensor, x, y, z, temperature);
        return true;
    }

    return false;
}


/**************************************************************
 *                       4. Utilities.                        *
 **************************************************************/

uint8_t tlx493d_common_calculateParity(const uint8_t dataIn) {
    uint8_t data = dataIn;
    data ^= data >> 4;
    data ^= data >> 2;
    data ^= data >> 1;
    return data & 1U;
}

uint8_t tlx493d_common_getOddParity(const uint8_t parity) {
    return (parity ^ 1U) & 1U;
}

uint8_t tlx493d_common_getEvenParity(const uint8_t parity) {
    return parity & 1U;
}

/**
 * More generic version wrt size and offsets of MSB and LSB. Register values are in two's complement form.
 * Assumptions :
 *    - registers are 8 bits wide
*/
void tlx493d_common_concatBytes(
    const TLx493D_t* sensor, const uint8_t msbBitfield, const uint8_t lsbBitfield, int16_t* result
) {
    const TLx493D_Register_t* msb = &sensor->regDef[msbBitfield];
    const TLx493D_Register_t* lsb = &sensor->regDef[lsbBitfield];

    /**
     * 1. Set the MSB bits to the leftmost bits of the result.
     * 2. Shift the MSB bits to the correct position, with sign extension.
     * 3. Merge the MSB and LSB bits with OR operation.
     */
    *result = (int16_t)((sensor->regMap[msb->address] & msb->mask) << 16U - msb->numBits - msb->offset);
    *result = (int16_t)(*result >> 16U - msb->numBits - lsb->numBits);
    *result = (int16_t)(*result | (sensor->regMap[lsb->address] & lsb->mask) >> lsb->offset);
}

const char* tlx493d_common_getTypeAsString(const TLx493D_t* sensor) {
    switch (sensor->sensorType) {
        case TLx493D_A1B6_e: return "TLx493D_A1B6";
        case TLx493D_A2B6_e: return "TLx493D_A2B6";
        case TLx493D_A2BW_e: return "TLx493D_A2BW";
        case TLx493D_P2B6_e: return "TLx493D_P2B6";
        case TLx493D_W2B6_e: return "TLx493D_W2B6";
        case TLx493D_W2BW_e: return "TLx493D_W2BW";
        case TLx493D_P3B6_e: return "TLx493D_P3B6";
        case TLx493D_P3I8_e: return "TLx493D_P3I8";
        default: return "ERROR : Unknown sensorType !";
    }
}

void tlx493d_common_setIICAddress(TLx493D_t* sensor, const uint8_t addr) {
    sensor->comInterface.comLibParams.iic_params.address = addr;
}


/**************************************************************
 *                    5. Error Handling.                      *
 **************************************************************/

void tlx493d_warnFeatureNotAvailableForSensorType(const TLx493D_t* sensor, const char* featureName) {
    ESP_LOGW(
        TAG, "Feature '%s' not available for sensor type '%s'!", featureName, tlx493d_common_getTypeAsString(sensor)
    );
}

void tlx493d_errorBitfieldNotReadableForSensorType(const TLx493D_t* sensor, const uint8_t bf) {
    ESP_LOGE(TAG, "Bitfield '%d' not readable for sensor type '%s'!", bf, tlx493d_common_getTypeAsString(sensor));
}

void tlx493d_errorBitfieldNotWritableForSensorType(const TLx493D_t* sensor, const uint8_t bf) {
    ESP_LOGE(TAG, "Bitfield '%d' not writable for sensor type '%s'!", bf, tlx493d_common_getTypeAsString(sensor));
}

void tlx493d_errorFunctionNotSupportedForSensorType(const TLx493D_t* sensor, const char* func) {
    ESP_LOGE(TAG, "Function '%s' not supported for sensor type '%s'!", func, tlx493d_common_getTypeAsString(sensor));
}


void tlx493d_errorSelectionNotSupportedForSensorType(const TLx493D_t* sensor, const uint8_t sel, const char* selType) {
    ESP_LOGE(
        TAG, "Selection '%d' for type '%s' not supported for sensor type '%s'!",
        sel, selType, tlx493d_common_getTypeAsString(sensor)
    );
}
