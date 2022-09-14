#include "nfc.h"

extern MFRC522 mfrc522;
extern tag_db_t tag_db;

void read_card(MFRC522 r)
{
  tag_t t;
  if (!r.PICC_IsNewCardPresent())
    return;
  if (!r.PICC_ReadCardSerial())
    return;
  memset(&t, 0, sizeof(tag_t));
  t.uid = r.uid;
  Serial.println("tag present");
  print_tag(&t);
  onTagPresent(&tag_db, &t);
}