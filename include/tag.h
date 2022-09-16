#ifndef TAG_H
  #define TAG_H
  #include "MFRC522.h"
  #include "Arduino.h"

  typedef struct {
    uint16_t id;
    MFRC522::Uid uid;
    uint8_t perm;
    uint8_t name[32];
  } tag_t;

  enum perm {
    INVALID,
    FULL,
    LIMITED
  };

  void print_hex(uint8_t *bytes, int sz);
  void tag_print(tag_t *t);

#endif