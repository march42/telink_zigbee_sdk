Redefined symbols in libraries, to fix duplicate names when linking against Gnu libc or libg.

see also
- `tl_zigbee_sdk/platform/chip_8258/random.h`
- `tl_zigbee_sdk/platform/chip_826x/bsp.h`
- `tl_zigbee_sdk/platform/chip_8278/random.h`
- `tl_zigbee_sdk/proj/drivers/drv_hw.c`

```
cp libdrivers_8258.a libdrivers_8258-original.a
tc32-elf-objcopy --redefine-sym rand=telink_rand libdrivers_8258-original.a libdrivers_8258.a
cp libdrivers_826x.a libdrivers_826x-original.a
tc32-elf-objcopy --redefine-sym rand=telink_rand libdrivers_826x-original.a libdrivers_826x.a
cp libdrivers_8278.a libdrivers_8278-original.a
tc32-elf-objcopy --redefine-sym rand=telink_rand libdrivers_8278-original.a libdrivers_8278.a
```
