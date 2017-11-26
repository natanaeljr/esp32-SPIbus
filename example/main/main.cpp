/* =========================================================================
The MIT License (MIT)

Copyright 2017 Natanael Josue Rabello. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
 ========================================================================= */

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "SPIbus.hpp"
#include "esp_log.h"
#include "esp_err.h"


#define SPI_MODE  0
#define MISO_PIN  17
#define MOSI_PIN  5
#define SCLK_PIN  23
#define CS_PIN    16
#define SPI_CLOCK 1000000  // 1 MHz

/*
 *  HSPI and VSPI are the default SPI controller objects
 */

extern "C" void app_main() {
    printf("\033[7m[APP]\033[0m\n");

    SPIbus_t &SPI = VSPI;
    
    spi_device_handle_t device;
    ESP_ERROR_CHECK(SPI.begin(MOSI_PIN, MISO_PIN, SCLK_PIN));
    ESP_ERROR_CHECK(SPI.addDevice(SPI_MODE, SPI_CLOCK, CS_PIN, &device));

    uint8_t buffer[6];
    while (1) {
        ESP_ERROR_CHECK(SPI.readBytes(device, 0x3B, 6, buffer));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelay(portMAX_DELAY);
}
