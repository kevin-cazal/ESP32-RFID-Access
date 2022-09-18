
#ifndef SHELL_H
#define SHELL_H
    #include "Arduino.h"
    #include "mem_storage.h"
    #define MAX_ARGS 4
    #define MAX_CMDS 14

    typedef struct  {
        String name;
        void (*fn) (String args[MAX_ARGS]);
        String help;
    } cmd_t;

    void shell_print_help(String args[MAX_ARGS]);
    void shell_load(String args[MAX_ARGS]);
    void shell_save(String args[MAX_ARGS]);
    void shell_mem_add(String args[MAX_ARGS]);
    void shell_mem_del(String args[MAX_ARGS]);
    void shell_read(String args[MAX_ARGS]);
    void shell_hexdump(String args[MAX_ARGS]);
    void shell_ls(String args[MAX_ARGS]);
    void shell_show_mem(String args[MAX_ARGS]);
    void shell_cmd_not_found(String args[MAX_ARGS]);
    void shell_load_default(String args[MAX_ARGS]);
    void shell_save_default(String args[MAX_ARGS]);
    void shell_get_time(String args[MAX_ARGS]);
    void shell_set_time(String args[MAX_ARGS]);
    void shell_rm(String args[MAX_ARGS]);
    void shell_serial_read();
#endif