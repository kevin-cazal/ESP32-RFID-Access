#include "Arduino.h"

void err(int code)
{
    Serial.print("ERR: ");
    Serial.println(code);
    delay(1000);
    ESP.restart();
}