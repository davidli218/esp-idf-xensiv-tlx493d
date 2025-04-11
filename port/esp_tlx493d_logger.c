#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/** project interfaces includes. */
#include "Logger.h"

/** project includes. */
#include "tlx493d_types.h"

/** ESP-IDF includes. */
#include "esp_log.h"


static const char* TAG = "TLx493D_LOGGER";

const uint16_t LOGGER_BUFFER_SIZE = 512U;

static void logMessage(const char* prefix, const char* format, va_list vaList) {
    char buffer[LOGGER_BUFFER_SIZE];

    const size_t prefixSize = strlen(prefix);
    memcpy(buffer, prefix, prefixSize);
    const int ret = vsnprintf(buffer + prefixSize, LOGGER_BUFFER_SIZE - prefixSize, format, vaList);

    if ((ret + prefixSize) >= LOGGER_BUFFER_SIZE) {
        ESP_LOGE(TAG, "FATAL: Buffer overflow (> %d characters) because message too long!", LOGGER_BUFFER_SIZE);
    }

    ESP_LOGI(TAG, "%s", buffer);
}

void logPrintRegisters(const TLx493D_t* sensor, const char* headLine) {
    ESP_LOGI(TAG, "");

    if (headLine != NULL) {
        ESP_LOGI(TAG, "%s", headLine);
    }

    for (uint8_t i = 0; i < sensor->regMapSize; ++i) {
        ESP_LOGI(TAG, "    0x%02X", sensor->regMap[i]);
    }

    ESP_LOGI(TAG, "");
}


void logPrintDouble(double d) {
    ESP_LOGI(TAG, "%f", d);
}


void logPrint(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    logMessage("", format, ap);
    va_end(ap);
}

void logPrintln(const char* prefix, const char* format, ...) {
    ESP_LOGI(TAG, "");
    va_list ap;
    va_start(ap, format);
    logMessage(prefix, format, ap);
    va_end(ap);
    ESP_LOGI(TAG, "");
}

void logFlush() {
}
