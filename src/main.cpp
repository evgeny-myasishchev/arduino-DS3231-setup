#include <Arduino.h>
#include <at.h>
#include "at-commands.h"
#include <DS3231.h>


DS3231 clock;
at::Engine atEngine(&Serial);

// AT commands
auto atPing = ATPing();
auto atTime = ATTime(&clock);

void setup()
{
    Wire.begin();
    Serial.begin(115200);

    atEngine.addCommandHandler(&atPing);
    atEngine.addCommandHandler(&atTime);
    atEngine.setup();
}

void loop()
{
    atEngine.loop();
    // Serial.print()
}