
#ifndef SHELL_H
#define SHELL_H
#include "Arduino.h"
#include "mem_storage.h"
#define MAX_ARGS 4
#define MAX_CMDS 12

typedef struct  {
    String name;
    void (*fn) (String args[MAX_ARGS]);
    String help;
} cmd_t;

void shell_printHelp(String args[MAX_ARGS]);
void shell_load(String args[MAX_ARGS]);
void shell_save(String args[MAX_ARGS]);
void shell_memAdd(String args[MAX_ARGS]);
void shell_memDel(String args[MAX_ARGS]);
void shell_read(String args[MAX_ARGS]);
void shell_hexdump(String args[MAX_ARGS]);
void shell_ls(String args[MAX_ARGS]);
void shell_print(String args[MAX_ARGS]);
void shell_cmdNotFound(String args[MAX_ARGS]);
void shell_load_default(String args[MAX_ARGS]);
void shell_save_default(String args[MAX_ARGS]);
void shell_serialRead(void *p);
void shell_rm(String args[MAX_ARGS]);


#endif