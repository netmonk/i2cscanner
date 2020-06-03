---

A simple I2C scanner using esp-idf Espressif framework for ESP32.


The code work for ESP32-WROOM-devkit1 with pins 21/22 as i2c port. 

update pins to adapt to your own board. 

```
plonky@citoyx:~/esp/i2cscanner$ idf.py build
Executing action: all (aliases: build)
Running ninja in directory /home/plonky/esp/i2cscanner/build
Executing "ninja all"...
[575/835] Performing configure step for 'bootloader'
-- Project version: v4.1-dev-281-g96b96ae24
-- Building ESP-IDF components for target esp32
-- Adding linker script /home/plonky/esp/esp-idf/components/esp32/ld/esp32.peripherals.ld
-- Adding linker script /home/plonky/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.ld
-- Adding linker script /home/plonky/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.newlib-funcs.ld
-- Adding linker script /home/plonky/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.libgcc.ld
-- Adding linker script /home/plonky/esp/esp-idf/components/bootloader/subproject/main/esp32.bootloader.ld
-- Adding linker script /home/plonky/esp/esp-idf/components/bootloader/subproject/main/esp32.bootloader.rom.ld
-- Components: bootloader bootloader_support efuse esp32 esp_common esp_rom esptool_py log main micro-ecc partition_table soc spi_flash xtensa
-- Component paths: /home/plonky/esp/esp-idf/components/bootloader /home/plonky/esp/esp-idf/components/bootloader_support /home/plonky/esp/esp-idf/components/efuse /home/plonky/esp/esp-idf/components/esp32 /home/plonky/esp/esp-idf/components/esp_common /home/plonky/esp/esp-idf/components/esp_rom /home/plonky/esp/esp-idf/components/esptool_py /home/plonky/esp/esp-idf/components/log /home/plonky/esp/esp-idf/components/bootloader/subproject/main /home/plonky/esp/esp-idf/components/bootloader/subproject/components/micro-ecc /home/plonky/esp/esp-idf/components/partition_table /home/plonky/esp/esp-idf/components/soc /home/plonky/esp/esp-idf/components/spi_flash /home/plonky/esp/esp-idf/components/xtensa
-- Configuring done
-- Generating done
-- Build files have been written to: /home/plonky/esp/i2cscanner/build/bootloader
[632/835] Performing build step for 'bootloader'
[1/2] Linking C executable bootloader.elf
[2/2] Generating binary image from built executable
esptool.py v2.8-dev
Generated /home/plonky/esp/i2cscanner/build/bootloader/bootloader.bin
[835/835] Generating binary image from built executable
esptool.py v2.8-dev
Generated /home/plonky/esp/i2cscanner/build/i2cscanner.bin

Project build complete. To flash, run this command:
../esp-idf/components/esptool_py/esptool/esptool.py -p (PORT) -b 460800 --after hard_reset write_flash --flash_mode dio --flash_size detect --flash_freq 40m 0x1000 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin 0x10000 build/i2cscanner.bin
or run 'idf.py -p (PORT) flash'
```
