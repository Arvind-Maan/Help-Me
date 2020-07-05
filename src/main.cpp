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
const int API_TIMEOUT = 10000;

void connectToWifi()
{
  //connect to wifi
  Serial.println("connecting to:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    //flash since we haven't connected to wifi yet
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    delay(100);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW

  Serial.println("\nWifi connected!\nIP address: ");
  Serial.println(WiFi.localIP());
}

BearSSL::WiFiClientSecure sendRequest()
{

  BearSSL::WiFiClientSecure client;
  client.setInsecure();
  client.setTimeout(API_TIMEOUT);
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, port))
  {
    while (1)
    {
      digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
      delay(1000);
    }
  }
  String url = "/trigger/ESP/with/key/";
  client.print(String("GET ") + url + makerKey + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  return client;
}

void readResponse(BearSSL::WiFiClientSecure client)
{
  //get the headers
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    if (line == "\r")
      break; //headers received!
  }
  String line = client.readStringUntil('\n');
  Serial.println("Server response:");
  Serial.println(line);
}
// the setup function runs once when you press reset or power the board
void setup()
{
  //initialize LED
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  connectToWifi();
  BearSSL::WiFiClientSecure client = sendRequest();
  readResponse(client);
}

// the loop function runs over and over again forever
void loop()
{
}