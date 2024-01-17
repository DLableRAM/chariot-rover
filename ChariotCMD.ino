#include "consts.h"
#include "classes.h"
#include "LW20-Api/Arduino/source/LW20.h"

LW20 lw20(Serial1, 115200);

void setup() 
{
    //TODO: Better error checking on startup.
    // Start serial monitor port.
    Serial.begin(115200);
    while(!serial);

    // Setup LW20.
    lw20.init();

    // Basic Setup.
    lw20.setLaserParams(LWMS_48);
}

void loop() 
{
    //API reading examples
    float distance = lw20.getLaserDistance(LWPT_FIRST, LWRF_RAW);
    float temperature = lw20.getLaserTemperature();

    Serial.print("Distance: "); Serial.print(distance); Serial.print(" - Temp: "); Serial.println(temperature);
  
    delay(25);
}