#ifndef MEM_STORAGE_H
#define MEM_STORAGE_H
#include "FS.h"
#include "tag.h"
#include "err.h"
#include "SPIFFS.h"
#include "LittleFS.h"
#define STORAGE LittleFS

#define DB_SIZE 1024
#define TAG_DB_FILE "/tag.db"
#define HISTORY_FILE "/history.log"
#define ERR_FILE "/errors.log"
#define FATAL_ERR_LOG "Fatal Error. Restarting in 10 seconds. Check log file"
#define FATAL_ERR_NO_LOG "Fatal Error. Restarting in 10 seconds. No log"

typedef struct {
    uint16_t sz;
    tag_t tags[DB_SIZE];
} tag_db_t;

uint16_t mem_find_next_tag_slot(tag_db_t *db);
int mem_insert_tag(tag_db_t *db, tag_t *t);
int mem_delete_tag(tag_db_t *db, uint16_t id);
void mem_dump_to_serial(tag_db_t *db);
void mem_write_to_fs(tag_db_t *db, fs::FS &fs, const char *path);
void mem_read_from_fs(tag_db_t *db, fs::FS &fs, const char *path);
void mem_match_tag(tag_db_t *db, tag_t *rfid);

#endif