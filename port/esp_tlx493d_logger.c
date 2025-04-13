#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/** project interfaces includes. */
#include "Logger.h"

/** project includes. */
#include "tlx493d_types.h"

/** ESP-IDF includes. */
#include "esp_log.h"


static const char* TAG = "tlx493d_logger";

const uint16_t LOGGER_BUFFER_SIZE = 512U;

static void logMessage(const char* prefix, const char* format, const va_list vaList) {
    char buffer[LOGGER_BUFFER_SIZE];

    const size_t prefixSize = strlen(prefix);
    memcpy(buffer, prefix, prefixSize);
    const int ret = vsnprintf(buffer + prefixSize, LOGGER_BUFFER_SIZE - prefixSize, format, vaList);

    if ((ret + prefixSize) >= LOGGER_BUFFER_SIZE) {
        ESP_LOGE(TAG, "FATAL: Buffer overflow (> %d characters) because message too long!", LOGGER_BUFFER_SIZE);
    }

    printf("%s", buffer);
}

void logPrintRegisters(const TLx493D_t* sensor, const char* headLine) {
    printf("\n");

    if (headLine != NULL) {
        printf("%s", headLine);
    }

    for (uint8_t i = 0; i < sensor->regMapSize; ++i) {
        logPrint("    0x%02X", sensor->regMap[i]);
    }

    printf("\n");
}

void logPrintDouble(double d) {
    printf("%f", d);
}

void logPrint(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    logMessage("", format, ap);
    va_end(ap);
}

void logPrintln(const char* prefix, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    logMessage(prefix, format, ap);
    va_end(ap);

    printf("\n");
}

void logFlush() {
    fflush(stdout);
}
