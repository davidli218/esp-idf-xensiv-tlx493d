#pragma once

#ifndef TLX493D_LOGGER_H
#define TLX493D_LOGGER_H

#include "tlx493d_types.h"

#define logInfo(...)    logPrintln("INFO : ", __VA_ARGS__)
#define logWarn(...)    logPrintln("WARN : ", __VA_ARGS__)
#define logError(...)   logPrintln("ERROR : ", __VA_ARGS__)


void logPrintRegisters(const TLx493D_t* sensor, const char* headLine);

void logPrintDouble(double d);

void logPrint(const char* format, ...);

void logPrintln(const char* prefix, const char* format, ...);


#endif /* TLX493D_LOGGER_H */
