#pragma once

#ifndef TLX493D_A1B6_H
#define TLX493D_A1B6_H

#include <stdbool.h>
#include <stdint.h>

#include "tlx493d_types.h"


typedef enum {
    TLx493D_A1B6_LOW_POWER_PERIOD_100MS_default,
    TLx493D_A1B6_LOW_POWER_PERIOD_12MS
} TLx493D_A1B6_Reg_LOW_POWER_PERIOD_t;


typedef struct {
    uint8_t FAST;
    uint8_t LOW_POWER;
    uint8_t LP;
    uint16_t MEAS_TIME;
} TLx493D_A1B6_PowerModeCombinations_t;


bool TLx493D_A1B6_init(TLx493D_t* sensor);
bool TLx493D_A1B6_deinit(TLx493D_t* sensor);

bool TLx493D_A1B6_readRegisters(TLx493D_t* sensor);
bool TLx493D_A1B6_readRegistersAndCheck(TLx493D_t* sensor);

void TLx493D_A1B6_calculateRawTemperature(const TLx493D_t* sensor, int16_t* temperature);
bool TLx493D_A1B6_getRawTemperature(TLx493D_t* sensor, int16_t* temperature);

void TLx493D_A1B6_calculateRawMagneticField(const TLx493D_t* sensor, int16_t* x, int16_t* y, int16_t* z);
bool TLx493D_A1B6_getRawMagneticField(TLx493D_t* sensor, int16_t* x, int16_t* y, int16_t* z);

void TLx493D_A1B6_calculateRawMagneticFieldAndTemperature(
    const TLx493D_t* sensor, int16_t* x, int16_t* y, int16_t* z, int16_t* temperature
);
bool TLx493D_A1B6_getRawMagneticFieldAndTemperature(
    TLx493D_t* sensor, int16_t* x, int16_t* y, int16_t* z, int16_t* temperature
);


void TLx493D_A1B6_calculateTemperature(const TLx493D_t* sensor, double* temp);
bool TLx493D_A1B6_getTemperature(TLx493D_t* sensor, double* temp);

void TLx493D_A1B6_calculateMagneticField(const TLx493D_t* sensor, double* x, double* y, double* z);
bool TLx493D_A1B6_getMagneticField(TLx493D_t* sensor, double* x, double* y, double* z);

void TLx493D_A1B6_calculateMagneticFieldAndTemperature(
    const TLx493D_t* sensor, double* x, double* y, double* z, double* temp
);
bool TLx493D_A1B6_getMagneticFieldAndTemperature(
    TLx493D_t* sensor, double* x, double* y, double* z, double* temp
);

bool TLx493D_A1B6_setMeasurement(TLx493D_t* sensor, TLx493D_MeasurementType_t mVals);

bool TLx493D_A1B6_setTrigger(const TLx493D_t* sensor, TLx493D_TriggerType_t trig);
bool TLx493D_A1B6_setSensitivity(const TLx493D_t* sensor, TLx493D_SensitivityType_t sens);


bool TLx493D_A1B6_setDefaultConfig(TLx493D_t* sensor);
bool TLx493D_A1B6_setIICAddress(TLx493D_t* sensor, TLx493D_IICAddressType_t addr);

bool TLx493D_A1B6_enable1ByteReadMode(const TLx493D_t* sensor);

bool TLx493D_A1B6_enableCollisionAvoidance(const TLx493D_t* sensor);
bool TLx493D_A1B6_disableCollisionAvoidance(const TLx493D_t* sensor);

bool TLx493D_A1B6_enableInterrupt(TLx493D_t* sensor);
bool TLx493D_A1B6_disableInterrupt(TLx493D_t* sensor);

bool TLx493D_A1B6_setPowerMode(TLx493D_t* sensor, TLx493D_PowerModeType_t mode);
bool TLx493D_A1B6_setUpdateRate(const TLx493D_t* sensor, TLx493D_UpdateRateType_t rate);


bool TLx493D_A1B6_hasValidData(const TLx493D_t* sensor);
bool TLx493D_A1B6_isFunctional(const TLx493D_t* sensor);

bool TLx493D_A1B6_hasWakeUp(const TLx493D_t* sensor);
bool TLx493D_A1B6_isWakeUpEnabled(const TLx493D_t* sensor);
bool TLx493D_A1B6_enableWakeUpMode(const TLx493D_t* sensor);
bool TLx493D_A1B6_disableWakeUpMode(const TLx493D_t* sensor);

bool TLx493D_A1B6_setWakeUpThresholdsAsInteger(
    const TLx493D_t* sensor,
    int16_t xlTh, int16_t xhTh,
    int16_t ylTh, int16_t yhTh,
    int16_t zlTh, int16_t zhTh
);
bool TLx493D_A1B6_setWakeUpThresholds(
    const TLx493D_t* sensor,
    double temperature,
    double xLow, double xHigh,
    double yLow, double yHigh,
    double zLow, double zHigh
);

bool TLx493D_A1B6_softwareReset(const TLx493D_t* sensor);


uint8_t TLx493D_A1B6_calculateFuseParity(const TLx493D_t* sensor);
uint8_t TLx493D_A1B6_calculateBusParity(const TLx493D_t* sensor);
uint8_t TLx493D_A1B6_calculateConfigurationParity(const TLx493D_t* sensor);

bool TLx493D_A1B6_hasValidTBit(const TLx493D_t* sensor);
bool TLx493D_A1B6_hasValidIICadr(const TLx493D_t* sensor);

bool TLx493D_A1B6_hasValidFuseParity(const TLx493D_t* sensor);
bool TLx493D_A1B6_hasValidBusParity(const TLx493D_t* sensor);
bool TLx493D_A1B6_hasValidConfigurationParity(const TLx493D_t* sensor);

bool TLx493D_A1B6_hasValidWakeUpParity(const TLx493D_t* sensor);
bool TLx493D_A1B6_isInTestMode(const TLx493D_t* sensor);

void TLx493D_A1B6_setResetValues(const TLx493D_t* sensor);
void TLx493D_A1B6_setReservedRegisterValues(const TLx493D_t* sensor);

uint8_t TLx493D_A1B6_selectIICAddress(const TLx493D_t* sensor, TLx493D_IICAddressType_t addr);

void TLx493D_A1B6_calculateRawMagneticFieldAtTemperature(
    const TLx493D_t* sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
    double xInmT, double yInmT, double zInmT,
    int16_t* x, int16_t* y, int16_t* z
);

double TLx493D_A1B6_getSensitivityScaleFactor(const TLx493D_t* sensor);

bool TLx493D_A1B6_transferWriteRegisters(TLx493D_t* sensor);

bool TLx493D_A1B6_enableParityTest(TLx493D_t* sensor);
bool TLx493D_A1B6_disableParityTest(TLx493D_t* sensor);

uint8_t TLx493D_A1B6_returnBitfield(const TLx493D_t* sensor, uint8_t bitField);
void TLx493D_A1B6_setBitfield(const TLx493D_t* sensor, uint8_t bitField, uint8_t newBitFieldValue);

bool TLx493D_A1B6_hasValidPDBit(const TLx493D_t* sensor);

void TLx493D_A1B6_printRegisters(const TLx493D_t* sensor);


#endif // TLX493D_A1B6_H
