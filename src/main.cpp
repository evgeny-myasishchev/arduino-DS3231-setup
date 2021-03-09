#include <Arduino.h>
#include <at.h>
#include "at-commands.h"
#include <DS3231.h>


DS3231 clock;
at::Engine atEngine(&Serial);

// AT commands
auto atPing = ATPing();
auto atTime = ATTime(&clock);
auto atZone = ATZone(&clock);

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    atEngine.addCommandHandler(&atPing);
    atEngine.addCommandHandler(&atTime);
    atEngine.addCommandHandler(&atZone);
    atEngine.setup();
}

void loop()
{
    atEngine.loop();
    // Serial.print()
}