# SPIbus

SPI interface library in C++ for working with **Espressif ESP32 IoT Development Framework _(esp-idf)_**, that supports master mode.

This SPIbus library is designed just as a high-level access of the ESP32's SPI peripheral, that actually, incorporates some of the _basic functionality_ of `spi_master` driver from _esp-idf_, translating the SPI functions as object oriented code. Its purpose is to simplify the usage of the native spi-master driver, and it is most for communication with **8-bit register sensors**.

So if you want to interact with a simple sensor over SPI protocol using C++, you can use this library to do so, a bit easier.

## Install

You can clone it right into your project components directory or in your specific library path.

```git
 git clone https://github.com/natanaeljr/esp32-SPIbus.git SPIbus
```

## Usage

The ESP32 has four SPI peripheral devices, called SPI0, SPI1, HSPI and VSPI.

SPI0 is entirely dedicated to the flash cache, the ESP32 uses to map the SPI flash device it is connected to into memory. SPI1 is connected to the same hardware lines as SPI0 and is used to write to the flash chip. HSPI and VSPI are free to use and are the currently implemented ones in the esp-idf.

So we can start off initializing the default global objects `hspi` and `vspi` as follows:

```C++
hspi.begin(MOSI_1, MISO_1, SCLK_1)
vspi.begin(MOSI_2, MISO_2, SCLK_2)
```

HSPI and VSPI all have three chip select lines, allowing them to drive up to three SPI devices each as a master.
To add a device to the controller, simply call addDevice() with the device configuration and a handle.

```C++
spi_device_handle_t sensor_handle
hspi.addDevice(SPIMODE, CLOCK, CS_PIN, &sensor_handle);
```

Now we read and write to the device with the specific methods.

```C++
hspi.writeByte(sensor_handle, REGISTER_ADDR, VALUE)
hspi.readBit(sensor_handle, REGISTER_ADDR, BITNUM, BUFFER)
```

The library has several methods to read/write which simplifies communication. See the header file for more info.

---

See also I2Cbus library: https://github.com/natanaeljr/esp32-I2Cbus

Copyright © 2017 Natanael Josue Rabello [_natanael.rabello@outlook.com_]
