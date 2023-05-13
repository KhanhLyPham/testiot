#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

#if defined(ARDUINO_ARCH_AVR)
#define SERIAL  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define SERIAL  SerialUSB
#else
#define SERIAL  Serial
#endif

void setup() 
{
    lcd.begin(16, 2);
    lcd.setRGB(255, 0, 0);
    SERIAL.begin(115200); 
    Wire.begin();
    dht.begin();
}

void loop() 
{
    float temp_hum_val[2] = {0};
    if(!dht.readTempAndHumidity(temp_hum_val)){
        lcd.setCursor(0,0);
        lcd.print("Do am: "); 
        lcd.print(temp_hum_val[0]);
        lcd.print(" %");
        lcd.setCursor(0,1);
        lcd.print("Nhiet: "); 
        lcd.print(temp_hum_val[1]);
        lcd.println(" *C ");
    }
    else{
       SERIAL.println("Failed to get temprature and humidity value.");
    }

   delay(1500);
}
