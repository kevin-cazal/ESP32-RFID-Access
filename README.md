# RFID-Access

## Quick start guide
- Install platformioIO Core (CLI) or platformIO IDE (VScode extension).
- Change upload_port value in platformio.ini to match your ESP32 serial port (/dev/ttyUSB* on Linux, /dev/cu.usbserial-* on MacOS)
- Compile with `pio run`
- Upload with `pio run --target upload`
- Connect to the serial interface with `pio device monitor`

## Serial interface - quick start guide
- Put a tag in front of the reader to print its UID 
- To add a tag in memory: `add <name> <uid> <permission>` ex: `add kevin 0482EABA6480 1` 
- To delete a tag in memory `del <id>` ex: `del 42`
- To save the content of the memory in the flash storage (total size: 1.5 Mb): `save <path>`
- To load the content of a file stored on flash storage in memory: `load <path>`
- `savedef` and `loaddef` respectively saves and loads from the default file in flash (defined in TAG_DB_FILE, this file automatically is loaded in memory on boot)
- To print the content of memory in human-readable format `print`
- To print the content of a file in hexadecimal format `cat <file>`
- `ls` and `rm`

When a tag is put in front of the reader its UID is always compared to UID stored in RAM. Flash storage is only used to make data persistant (To reload the list of registered tags after a reboot or to backup/restore the list of registered tags).
  
## Serial interface - quicker start guide
  - Put a tag in front of the reader to print its UID 
  - `help`

## TODO: Logging 
