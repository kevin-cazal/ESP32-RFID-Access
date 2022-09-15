
#include "SPI.h"
#include "SPIFFS.h"
#include "MFRC522.h"
#include "tag.h"
#include "mem_storage.h"
#include "shell.h"
#include "nfc.h"

MFRC522 rfid(5, 27);

typedef struct {
  uint32_t timestamp;
  uint16_t id;
} history_t;

tag_t last_tag = {0};
tag_db_t tag_db = {0};
history_t last_access = {0};
history_t last_error = {0};

void setup()
{
  Serial.begin(115200);
  memset(&tag_db, 0, sizeof(tag_db_t));
  tag_db.sz = DB_SIZE;
  SPI.begin();
  STORAGE.begin(0);
  if (STORAGE.exists(TAG_DB_FILE))
    read_from_fs(&tag_db, STORAGE, TAG_DB_FILE);
  rfid.PCD_Init();
  rfid.PCD_DumpVersionToSerial();
}

void loop()
{
  shell_serialRead(NULL);
  read_card(rfid);
}

/*
void create_random_tag(tag_t *t)
{
  int sz_map[3] = {4, 7, 10};
  int nlen = random(5, 30);
  int uidsz = random(3);

  for (int i = 0; i < nlen; i++) {
    t->name[i] = random('a', 'z'+1);
  }
  t->perm = random(1, 3);
  t->uid.size = sz_map[uidsz];
  for(int i = 0; i < t->uid.size; i++) {
    t->uid.uidByte[i] = random(256);
  }
}
 */
