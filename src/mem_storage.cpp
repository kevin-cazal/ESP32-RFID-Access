#include "mem_storage.h"

int find_next_tag_slot(tag_db_t *db)
{
  int i = 0;

  while (db->tags[i].perm && i < DB_SIZE) {
    i++;
  }
  
  return (i < DB_SIZE ? i : -1);
}

void onTagPresent(tag_db_t *db, tag_t *rfid)
{
    int i = 0;

    while (i < DB_SIZE) {
        if (memcmp(rfid->uid.uidByte, db->tags[i].uid.uidByte, rfid->uid.size) == 0) {
            Serial.print("opening for:");
            print_tag(&db->tags[i]);
            return;
        }
        i++;
    }
    Serial.println("not open");
}

int insert_tag(tag_db_t *db, tag_t *t)
{
  int next_slot = find_next_tag_slot(db);

  Serial.print("INSERT: ");
  Serial.println(next_slot);
  if (next_slot == -1)
    err(TAG_DB_INSERT_ERR);
  memcpy((void *)(&db->tags[next_slot]), t, sizeof(tag_t));
  db->tags[next_slot].id = next_slot;
  return next_slot;
}

int delete_tag(tag_db_t *db, uint16_t id)
{
  memset(&(db->tags[id]), 0, sizeof(tag_t));
  return id;
}

void dump_to_serial(tag_db_t *db)
{
  uint16_t i = 0;

  while (i < DB_SIZE) {
    if (db->tags[i].perm)
      print_tag(&db->tags[i]);
    i++;
  }
}

void write_to_fs(tag_db_t *db, fs::FS &fs, const char *path)
{
    File f = fs.open(path, "w", true);
    size_t sz = 0;

    if (!f)
        err(TAG_DB_OPEN_ERR);
    int s = 0;
    sz = f.write((uint8_t *)db, sizeof(tag_db_t));
    f.close();
    Serial.print("Wrote: ");
    Serial.println(sz);
}

void read_from_fs(tag_db_t *db, fs::FS &fs, const char *path)
{
    File f = fs.open(path);
    size_t sz = 0;

    if (!f)
        err(TAG_DB_OPEN_ERR);
    sz =  f.read((uint8_t *)db, sizeof(tag_db_t));
    f.close();
    if (sz == -1)
        err(TAG_DB_READ_ERR);
}