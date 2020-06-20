#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WifiClientSecure.h>

//****TO DO: Fill out the following variables with your information******
const char *ssid = "";     // your SSID
const char *password = ""; //your wifi password

//your secret key from http://maker.ifttt.com.
//(can be found in settings or https://ifttt.com/maker_webhooks/settings)
const char *makerKey = "";
//******************** end of TO-DO ********************

const char *host = "maker.ifttt.com";
const int port = 443;
// the setup function runs once when you press reset or power the board
void setup()
{
  //initialize LED
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  //connect to wifi
  Serial.println("connecting to:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    //flash since we haven't connected to wifi yet
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(250);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    delay(250);                      // wait for a second
    Serial.print(".");
  }
  Serial.println("\nWifi connected!\nIP address: ");
  Serial.println(WiFi.localIP());
}

// the loop function runs over and over again forever
void loop()
{
}