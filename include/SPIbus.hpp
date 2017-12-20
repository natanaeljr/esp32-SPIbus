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
#define SPIBUS_READ     (0x80)  /*!< addr | SPIBUS_READ  */
#define SPIBUS_WRITE    (0x7F)  /*!< addr & SPIBUS_WRITE */

// Forward declaration
class SPI;

// Default objects
extern SPI hspi;
extern SPI vspi;


/* ^^^
 * SPI
 * ^^^ */
typedef
class SPI {
 private:
    spi_host_device_t host;     /*!< HSPI_HOST or VSPI_HOST */

 public:
    explicit SPI(spi_host_device_t host);
    ~SPI();

    /**
     * @brief   Config SPI bus and initialize
     * @param   mosi_io_num     [GPIO number for Master-out Slave-in]
     * @param   miso_io_num     [GPIO number for Master-in Slave-out]
     * @param   miso_io_num     [GPIO number for clock line]
     * @param   max_transfer_sz [Maximum transfer size, in bytes. Defaults to 4094 if 0.]
     * @return  - ESP_ERR_INVALID_ARG   if configuration is invalid
     *          - ESP_ERR_INVALID_STATE if host already is in use
     *          - ESP_ERR_NO_MEM        if out of memory
     *          - ESP_OK                on success
     * */
    esp_err_t begin(int mosi_io_num, int miso_io_num, int sclk_io_num, int max_transfer_sz = SPI_MAX_DMA_LEN);

    /**
     * @brief   Free the SPI bus
     * @warning In order for this to succeed, all devices have to be removed first.
     * @return  - ESP_ERR_INVALID_ARG   if parameter is invalid
     *          - ESP_ERR_INVALID_STATE if not all devices on the bus are freed
     *          - ESP_OK                on success
     * */
    esp_err_t close();

    /**
     * @brief   Allocate a device on a SPI bus. (Up to three devices per peripheral)
     * @param   mode            [SPI mode (0-3)]
     * @param   clock_speed_hz  [Clock speed, in Hz]
     * @param   cs_io_num       [ChipSelect GPIO pin for this device, or -1 if not used]
     * @param   handle          [Pointer to variable to hold the device handle]
     * @param   dev_config      [SPI interface protocol config for the device (for more custom configs)]
     *                          @see driver/spi_master.h
     * @return  - ESP_ERR_INVALID_ARG   if parameter is invalid
     *          - ESP_ERR_NOT_FOUND     if host doesn't have any free CS slots
     *          - ESP_ERR_NO_MEM        if out of memory
     *          - ESP_OK                on success
     * */
    esp_err_t addDevice(uint8_t mode, uint32_t clock_speed_hz, int cs_io_num, spi_device_handle_t *handle);
    esp_err_t addDevice(spi_device_interface_config_t *dev_config, spi_device_handle_t *handle);
    esp_err_t removeDevice(spi_device_handle_t handle);

    /**
     * *** WRITING interface ***
     * @brief  SPI commands for writing to a 8-bit slave device register.
     *         All of them returns standard esp_err_t codes. So it can be used
     *         with ESP_ERROR_CHECK();
     * @param  handle    [SPI device handle]
     * @param  regAddr   [Register address to write to]
     * @param  bitNum    [Bit position number to write to (bit 7~0)]
     * @param  bitStart  [Start bit number when writing a bit-sequence (MSB)]
     * @param  data      [Value(s) to be write to the register]
     * @param  length    [Number of bytes to write (should be within the data buffer size)]
     *                   [writeBits() -> Number of bits after bitStart (including)]
     * @return  - ESP_ERR_INVALID_ARG   if parameter is invalid
     *          - ESP_OK                on success
     */
    esp_err_t writeBit(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitNum, uint8_t data);
    esp_err_t writeBits(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
    esp_err_t writeByte(spi_device_handle_t handle, uint8_t regAddr, uint8_t data);
    esp_err_t writeBytes(spi_device_handle_t handle, uint8_t regAddr, size_t length, const uint8_t *data);

    /**
     * *** READING interface ***
     * @breif  SPI commands for reading a 8-bit slave device register.
     *         All of them returns standard esp_err_t codes.So it can be used
     *         with ESP_ERROR_CHECK();
     * @param  handle    [SPI device handle]
     * @param  regAddr   [Register address to read from]
     * @param  bitNum    [Bit position number to write to (bit 7~0)]
     * @param  bitStart  [Start bit number when writing a bit-sequence (MSB)]
     * @param  data      [Buffer to store the read value(s)]
     * @param  length    [Number of bytes to read (should be within the data buffer size)]
     * @return  - ESP_ERR_INVALID_ARG   if parameter is invalid
     *          - ESP_OK                on success
     */
    esp_err_t readBit(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
    esp_err_t readBits(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
    esp_err_t readByte(spi_device_handle_t handle, uint8_t regAddr, uint8_t *data);
    esp_err_t readBytes(spi_device_handle_t handle, uint8_t regAddr, size_t length, uint8_t *data);
} SPI_t;


/* Get default objects */
constexpr SPI_t& getSPI(spi_host_device_t host) {
    return host == 1 ? hspi : vspi;
}



 #endif  // end of include guard: _SPIBUS_HPP_
