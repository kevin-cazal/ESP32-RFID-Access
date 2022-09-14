#include "tag.h"


int uidCmp(tag_t *a, tag_t *b)
{
    return memcmp(a->uid.uidByte, b->uid.uidByte, a->uid.size) ? 1 : 0;
}

void printHex(uint8_t *bytes, int sz)
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

void print_tag(tag_t *t)
{
  Serial.print("ID:");
  Serial.print(t->id);
  Serial.print(",UID:");
  printHex(t->uid.uidByte, t->uid.size);
  Serial.print(",PERM:");
  printHex(&(t->perm), 1);
  Serial.print(",NAME:");
  Serial.println((char *)t->name);
}