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

  void printHex(uint8_t *, int);
  void print_tag(tag_t *);
  int uidCmp(tag_t *a, tag_t *b);

#endif