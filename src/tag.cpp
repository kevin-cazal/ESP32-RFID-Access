#include "tag.h"

void print_hex(uint8_t *bytes, int sz)
{
  int i = 0;

  while (i < sz) {
    if (bytes[i] < 0x10)
      Serial.print("0");
    Serial.print(bytes[i], HEX);
    i++;
    if (i < sz)
      Serial.print(" ");
  }
}

void tag_print(tag_t *t)
{
  Serial.print("ID:");
  Serial.print(t->id);
  Serial.print(",UID:");
    print_hex(t->uid.uidByte, t->uid.size);
  Serial.print(",PERM:");
  Serial.print(t->perm, BIN);
  Serial.print(",NAME:");
  Serial.println((char *)t->name);
}