#include "nfc.h"

extern tag_db_t tag_db;

void nfc_read_card(MFRC522 r)
{
    tag_t t;
    if (!r.PICC_IsNewCardPresent())
        return;
    if (!r.PICC_ReadCardSerial())
        return;
    memset(&t, 0, sizeof(tag_t));
    t.uid = r.uid;
    tag_print(&t);
    mem_match_tag(&tag_db, &t);
}