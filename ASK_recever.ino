
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

 RH_ASK driver(2000, 2, 9, 5); // ESP8266 or ESP32: do not use pin 11

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("hello");
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	int i;
      String str = "";

      for(int i = 0; i < buflen; i++) {
        str += (char)buf[i];
      }

      Serial.println(str);
    }
}
