
#include "SPI.h"
#include "MFRC522.h"
#include "mem_storage.h"
#include "shell.h"
#include "nfc.h"

/*
typedef struct {
  uint32_t timestamp;
  uint16_t id;
} history_t;

tag_t last_tag;
history_t last_access;
history_t last_error;
 */

MFRC522 rfid(5, 27);
tag_db_t tag_db;

void setup()
{
    Serial.begin(115200);
    memset(&tag_db, 0, sizeof(tag_db_t));
    tag_db.sz = DB_SIZE;
    SPI.begin();
    STORAGE.begin(0);
    if (STORAGE.exists(TAG_DB_FILE))
        mem_read_from_fs(&tag_db, STORAGE, TAG_DB_FILE);
    rfid.PCD_Init();
    rfid.PCD_DumpVersionToSerial();
}

void loop()
{
    shell_serial_read();
    nfc_read_card(rfid);
}