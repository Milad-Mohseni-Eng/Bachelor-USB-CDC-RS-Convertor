# Bachelor-USB-CDC-RS-Convertor
USB CDC virtual COM (AT90USBxx) - USB to RS232 Convertor


# USB-to-RS232 Omega (USB CDC Virtual COM)

*Project*: USB CDC Virtual COM -> RS232 converter (AT90USB82 / AT90USB162)  
*Author*: Milad Mohseni

## Summary
USB CDC-based virtual COM port converter for connecting legacy RS-232 industrial devices (scales, card readers, displays) to modern PCs. Firmware written in *C* (WinAVR). Tested up to 57600 bps.

## Repo structure
- hardware/ — schematic (PDF), BOM
- firmware/ — Source (main.c, usbcdc libs), Makefile, cdc.hex
- driver/ — Windows driver files (INF, SYS)
- docs/ — test plan, build & flash instructions

## Build (WinAVR)
```bash
cd firmware/Source
make clean
make
# output: firmware/cdc.hex
