
#include "SPI.h"
#include "MFRC522.h"
#include "mem_storage.h"
#include "shell.h"
#include "nfc.h"

/*
 * Real Time Clock tests
 */

#include "ErriezDS1302.h"
#define DS1302_CLK_PIN 0
#define DS1302_IO_PIN 2
#define DS1302_CE_PIN 4
#include "miniz.h"
void testclock()
{
    ErriezDS1302 rtc = ErriezDS1302(DS1302_CLK_PIN, DS1302_IO_PIN, DS1302_CE_PIN);
    while (!rtc.begin()) {
        Serial.println(("RTC not found"));
        delay(3000);
    }
    Serial.println("rtc begin ok");
    if (!rtc.isRunning()) {
        Serial.println("rtc not running, enabling clock");
        // Error: RTC oscillator stopped. Date/time cannot be trusted.
        // Set new date/time before reading date/time.
        if (!rtc.setTime(12, 0, 0)) {
            // Error: Set time failed
        }
        // Enable oscillator
        rtc.clockEnable(true);
    }

    uint8_t hour;
    uint8_t minute;
    uint8_t second;

// Read time from RTC
    while (1) {
        if (!rtc.getTime(&hour, &minute, &second)) {
            // Error: RTC read failed
            Serial.println("get time failed");
        } else {
            Serial.print("HOUR:");
            Serial.print(hour);
            Serial.print("MIN:");
            Serial.print(minute);
            Serial.print("SEC:");
            Serial.println(second);
        }
        delay(100);
    }

}



/*
typedef struct {
  uint32_t timestamp;
  uint16_t id;
} history_t;

tag_t last_tag;
history_t last_access;
history_t last_error;
 */

MFRC522 rfid(5, 27);
tag_db_t tag_db;

void setup()
{
    Serial.begin(115200);
    memset(&tag_db, 0, sizeof(tag_db_t));
    tag_db.sz = DB_SIZE;
    SPI.begin();
    STORAGE.begin(0);
    if (STORAGE.exists(TAG_DB_FILE))
        mem_read_from_fs(&tag_db, STORAGE, TAG_DB_FILE);
    rfid.PCD_Init();
    rfid.PCD_DumpVersionToSerial();
    //testclock();
}

void loop()
{
    shell_serial_read();
    nfc_read_card(rfid);
}