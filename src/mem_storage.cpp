#include "mem_storage.h"

uint16_t mem_find_next_tag_slot(tag_db_t *db)
{
    uint16_t i = 0;

    while (db->tags[i].perm && i < DB_SIZE) {
        i++;
    }
    return (i < DB_SIZE ? i : -1);
}

void mem_match_tag(tag_db_t *db, tag_t *rfid)
{
    int i = 0;

    while (i < DB_SIZE) {
        if (memcmp(rfid->uid.uidByte, db->tags[i].uid.uidByte, rfid->uid.size) == 0) {
            Serial.print("FOUND");
            tag_print(&db->tags[i]);
            return;
        }
        i++;
    }
    Serial.println("NOT FOUND");
}

int mem_insert_tag(tag_db_t *db, tag_t *t)
{
    int next_slot = mem_find_next_tag_slot(db);

    Serial.println(next_slot);
    if (next_slot == -1)
        err(TAG_DB_INSERT_ERR);
    memcpy((void *) (&db->tags[next_slot]), t, sizeof(tag_t));
    db->tags[next_slot].id = next_slot;
    return next_slot;
}

int mem_delete_tag(tag_db_t *db, uint16_t id)
{
    memset(&(db->tags[id]), 0, sizeof(tag_t));
    return id;
}

void mem_dump_to_serial(tag_db_t *db)
{
    uint16_t i = 0;

    while (i < DB_SIZE) {
        if (db->tags[i].perm)
            tag_print(&db->tags[i]);
        i++;
    }
}

void mem_write_to_fs(tag_db_t *db, fs::FS &fs, const char *path)
{
    File f = fs.open(path, "wb", true);

    f.write((uint8_t *) db, sizeof(tag_db_t));
    f.close();
}

void mem_read_from_fs(tag_db_t *db, fs::FS &fs, const char *path)
{
    File f = fs.open(path, "rb");

    if (!f)
        err(TAG_DB_OPEN_ERR);
    f.read((uint8_t *) db, sizeof(tag_db_t));
    f.close();
}