#include "DHT.h"
#include <Adafruit_Sensor.h>
#include "WiFi.h"
#include "../../../credentials.h"
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>


// put function declarations here:
#define WIFI_TIMEOUT_MS 20000
#define LED_PIN 22
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
#define DHT_PIN 5

DHT my_sensor(DHT_PIN,DHT22);
float temp, humd;

//WiFiClientSecure espClient;8883(for secure MQTT-SSL/TLS);
WiFiClientSecure espClient = WiFiClientSecure();
PubSubClient client(espClient);

void ConnectToWifi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA); //set station mode for already existing wifi, Other mode is AP=Acess Point mode.
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  unsigned long startAttemptTime=millis();//return uptime of esp32
  while(WiFi.status() != WL_CONNECTED && (millis()-startAttemptTime < WIFI_TIMEOUT_MS)){
    Serial.print(".");
    delay(100);
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println(" Failed!");
  }else{
    Serial.print("Connected! IP is: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_PIN, HIGH); // turn LED ON when wifi is connected
  }
}

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

void ConnectToAWS(){
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  espClient.setCACert(AWS_CERT_CA);
  espClient.setCertificate(AWS_CERT_CRT);
  espClient.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  // Create a message handler
  client.setCallback(messageHandler);
  Serial.println("Connecting to AWS IOT");

  while(!client.connect(THINGSNAME))
  {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected())
  {
    Serial.println(" AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["humidity"] = humd;
  doc["temperature"] = temp;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  ConnectToWifi();
  ConnectToAWS();
  my_sensor.begin();
}

void loop() {
  humd = my_sensor.readHumidity();
  temp = my_sensor.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("C, Humidity: ");
  Serial.print(humd);
  Serial.print("%");
  Serial.print("\n");
  
  publishMessage();

  client.loop();

  // Example: Publish temperature every 10 seconds
  delay(10000);  // Delay in milliseconds
}