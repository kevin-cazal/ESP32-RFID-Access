#include "shell.h"

extern tag_db_t tag_db;

cmd_t cmds[MAX_CMDS] = {
    {.name = "add", .fn = shell_memAdd, .help = "add name uid perm"},
    {.name = "del", .fn = shell_memDel, .help = "del id"},
    {.name = "load", .fn = shell_load, .help = "load file"},
    {.name = "save", .fn = shell_save, .help = "save file"},
    {.name = "savedef", .fn = shell_save_default, .help = "savedef"},
    {.name = "loaddef", .fn = shell_load_default, .help = "loaddef"},
    {.name = "hexdump", .fn = shell_hexdump, .help = "hexdump file"},
    {.name = "read", .fn = shell_read, .help = "read dest"},
    {.name = "ls", .fn = shell_ls, .help = "ls"},
    {.name = "rm", .fn = shell_rm, .help = "rm file"},
    {.name = "print", .fn = shell_print, .help = "print string"},
    {.name = "help", .fn = shell_printHelp, .help = "help"}
};

void shell_read(String args[MAX_ARGS])
{
    uint8_t c = 0;
    File f = STORAGE.open(args[1], "wb", true);

    if (!f)
        return;
    while (Serial.available()) {
        c = Serial.read();
        f.write(c);
    }
    f.close();
}

void shell_printHelp(String args[MAX_ARGS])
{
  for (int i = 0; i < MAX_CMDS; i++) {
    Serial.println(cmds[i].help);
  }
}

void shell_rm(String args[MAX_ARGS])
{
  STORAGE.remove(args[1]);
}

void shell_load(String args[MAX_ARGS])
{
  read_from_fs(&tag_db, STORAGE, args[1].c_str());
}
void shell_save(String args[MAX_ARGS])
{
  write_to_fs(&tag_db, STORAGE, args[1].c_str());
}

void shell_load_default(String args[MAX_ARGS])
{
  read_from_fs(&tag_db, STORAGE, TAG_DB_FILE);
}

void shell_save_default(String args[MAX_ARGS])
{
  write_to_fs(&tag_db, STORAGE, TAG_DB_FILE);
}

void shell_memAdd(String args[MAX_ARGS])
{
  tag_t t;
  size_t uidSize = args[2].length() / 2;
  size_t lenName = args[1].length() > 31 ? 31 : args[1].length();
  const char *name = args[1].c_str();

  memset(t.name, 0, sizeof(t.name));
  for(int i = 0; i < lenName; i++) {
      t.name[i] = name[i];
  }
  memcpy(t.name, args[1].c_str(), lenName);
  memset(t.uid.uidByte, 0, sizeof(t.uid.uidByte));
  for (int i = 0; i < uidSize; i++) {
    t.uid.uidByte[i] = strtol(args[2].substring((2 * i), 2 + (2 * i)).c_str(), 0, 16);
  }
  t.uid.size = uidSize;
  t.perm = args[3].toInt();
  insert_tag(&(tag_db), &t);
}
void shell_memDel(String args[MAX_ARGS])
{
  int id = args[1].toInt();

  // 12C4: Check ID
  delete_tag(&(tag_db), id);
}

void shell_hexdump(String args[MAX_ARGS])
{
    File f = STORAGE.open(args[1], "rb");
    uint8_t c;

    if (!f || f.isDirectory()) {
      return;
    }
    while(f.available()) {
        c = f.read();
        if (c < 0x10)
            Serial.print("0");
        Serial.print(c, HEX);
        Serial.print(" ");
    }
}

void shell_ls(String args[MAX_ARGS])
{
  
  int used = STORAGE.usedBytes();
  int total = STORAGE.totalBytes();
  int free = total - used;
  float used_percent = ((float)used / total) * 100;
  File root = STORAGE.open("/");
  File f;

  if (!root)
    return;
  if (!root.isDirectory())
    return;
  f = root.openNextFile();
  while (f) {
    if (f.isDirectory()) {
      Serial.print("DIR : /");
      Serial.println(f.name());
    } else {
      Serial.print("FILE: /");
      Serial.print(f.name());
      Serial.print("\tSIZE: ");
      Serial.println(f.size());
    }
    f = root.openNextFile();
  }
  Serial.print("\nFREE b:");
  Serial.print(free);
  Serial.print(" USED b:");
  Serial.print(used);
  Serial.print(" TOTAL b:");
  Serial.print(total);
  Serial.print(" USED %:");
  Serial.println(used_percent);
}

void shell_cmdNotFound(String args[4])
{
  Serial.println("Command not found. Use 'help' to show available commands.");
}

void shell_print(String args[4])
{
    dump_to_serial(&tag_db);
}

void shell_serialRead(void *p)
{
  String in;
  String args[MAX_ARGS];
  String help = "";

  if (!Serial.available())
    return;
  in = Serial.readStringUntil('\n');
  in.trim();
  if (!in.length())
    return;
  for (int i = 0; i < MAX_ARGS; i++) {
    in.trim();
    args[i] = in.substring(0, in.indexOf(' '));
    in = in.substring(in.indexOf(' '));
  }
  for (int i = 0; i < MAX_CMDS; i++) {
    if (args[0].equalsIgnoreCase(cmds[i].name)) {
      cmds[i].fn(args);
      Serial.println("");
      return;
    }
  }
  shell_cmdNotFound(args);
  Serial.println("");
}

