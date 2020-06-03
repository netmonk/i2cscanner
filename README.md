---

A simple I2C scanner using esp-idf Espressif framework for ESP32.

Mostly inspired by https://github.com/espressif/esp-idf/tree/master/examples/peripherals/i2c/i2c_tools
to focus only on peripherals detection. 

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


Output:
```
plonky@citoyx:~/esp/i2cscanner$ idf.py monitor
Executing action: monitor
Choosing default port /dev/ttyUSB0 (use '-p PORT' option to set a specific serial port)
Running idf_monitor in directory /home/plonky/esp/i2cscanner
Executing "/home/plonky/.espressif/python_env/idf4.1_py2.7_env/bin/python /home/plonky/esp/esp-idf/tools/idf_monitor.py -p /dev/ttyUSB0 -b 115200 /home/plonky
/esp/i2cscanner/build/i2cscanner.elf -m '/home/plonky/.espressif/python_env/idf4.1_py2.7_env/bin/python' '/home/plonky/esp/esp-idf/tools/idf.py'"...
--- idf_monitor on /dev/ttyUSB0 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
I (12) boot: ESP-IDF v4.1-dev-281-g96b96ae24 2nd stage bootloader
I (12) boot: compile time 11:02:12
I (13) boot: Enabling RNG early entropy source...
I (17) boot: SPI Speed      : 40MHz
I (22) boot: SPI Mode       : DIO
I (26) boot: SPI Flash Size : 4MB
I (30) boot: Partition Table:
I (33) boot: ## Label            Usage          Type ST Offset   Length
I (40) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (48) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (55) boot:  2 factory          factory app      00 00 00010000 00100000
I (63) boot: End of partition table
I (67) esp_image: segment 0: paddr=0x00010020 vaddr=0x3f400020 size=0x0695c ( 26972) map
I (86) esp_image: segment 1: paddr=0x00016984 vaddr=0x3ffb0000 size=0x020b4 (  8372) load
I (89) esp_image: segment 2: paddr=0x00018a40 vaddr=0x40080000 size=0x00400 (  1024) load
0x40080000: _WindowOverflow4 at /home/plonky/esp/esp-idf/components/freertos/xtensa_vectors.S:1778

I (94) esp_image: segment 3: paddr=0x00018e48 vaddr=0x40080400 size=0x071c8 ( 29128) load
I (115) esp_image: segment 4: paddr=0x00020018 vaddr=0x400d0018 size=0x14914 ( 84244) map
0x400d0018: _stext at ??:?

I (145) esp_image: segment 5: paddr=0x00034934 vaddr=0x400875c8 size=0x03750 ( 14160) load
0x400875c8: spi_flash_ll_set_addr_bitlen at /home/plonky/esp/esp-idf/components/soc/esp32/include/hal/spi_flash_ll.h:333
 (inlined by) spi_flash_hal_configure_host_read_mode at /home/plonky/esp/esp-idf/components/soc/src/hal/spi_flash_hal_iram.c:63

I (159) boot: Loaded app from partition at offset 0x10000
I (159) boot: Disabling RNG early entropy source...
I (159) cpu_start: Pro cpu up.
I (163) cpu_start: Application information:
I (168) cpu_start: Project name:     i2cscanner
I (173) cpu_start: App version:      1
I (177) cpu_start: Compile time:     Jun  3 2020 11:05:31
I (183) cpu_start: ELF file SHA256:  4497c7346423e5ab...
I (189) cpu_start: ESP-IDF:          v4.1-dev-281-g96b96ae24
I (196) cpu_start: Starting app cpu, entry point is 0x400810b8
0x400810b8: call_start_cpu1 at /home/plonky/esp/esp-idf/components/esp32/cpu_start.c:271

I (0) cpu_start: App cpu up.
I (206) heap_init: Initializing. RAM available for dynamic allocation:
I (213) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (219) heap_init: At 3FFB30B0 len 0002CF50 (179 KiB): DRAM
I (225) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (232) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (238) heap_init: At 4008AD18 len 000152E8 (84 KiB): IRAM
I (244) cpu_start: Pro cpu start user code
I (262) spi_flash: detected chip: generic
I (263) spi_flash: flash io: dio
I (263) cpu_start: Chip Revision: 1
W (265) cpu_start: Chip revision is higher than the one configured in menuconfig. Suggest to upgrade it.
I (275) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.

    0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
```
