#ifndef NFC_H
#define NFC_H
#include "tag.h"
#include "mem_storage.h"
#include "MFRC522.h"

void nfc_read_card(MFRC522 r);

#endif