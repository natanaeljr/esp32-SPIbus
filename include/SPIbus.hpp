/* =========================================================================
SPIbus library is placed under the MIT License
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

#ifndef _SPIBUS_HPP_
#define _SPIBUS_HPP_

#include <stdint.h>
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "esp_err.h"

// Defaults
#define SPIBUS_READ     (0x80)  /*!< addr | SPIBUS_READ */
#define SPIBUS_WRITE    (0x7F)  /*!< addr & SPIBUS_WRITE */

// Forward declaration
class SPIbus_t;

// Default objects
extern SPIbus_t HSPI;
extern SPIbus_t VSPI;


/* ^^^^^^
 * SPIBUS
 * ^^^^^^ */
class SPIbus_t {
 private:
    spi_host_device_t host;

 public:
    explicit SPIbus_t(spi_host_device_t host);
    ~SPIbus_t();

    esp_err_t begin(int mosi_io_num, int miso_io_num, int sclk_io_num, int max_transfer_sz = SPI_MAX_DMA_LEN);
    esp_err_t close();

    esp_err_t addDevice(uint8_t mode, uint32_t clock_speed_hz, int cs_io_num, spi_device_handle_t *handle);
    esp_err_t addDevice(spi_device_interface_config_t *dev_config, spi_device_handle_t *handle);
    esp_err_t removeDevice(spi_device_handle_t handle);

    esp_err_t writeBit(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitNum, uint8_t data);
    esp_err_t writeBits(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
    esp_err_t writeByte(spi_device_handle_t handle, uint8_t regAddr, uint8_t data);
    esp_err_t writeBytes(spi_device_handle_t handle, uint8_t regAddr, size_t length, const uint8_t *data);

    esp_err_t readBit(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
    esp_err_t readBits(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
    esp_err_t readByte(spi_device_handle_t handle, uint8_t regAddr, uint8_t *data);
    esp_err_t readBytes(spi_device_handle_t handle, uint8_t regAddr, size_t length, uint8_t *data);
};


 
 #endif  // end of include guard: _SPIBUS_HPP_
