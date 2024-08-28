# ESP32_MQTT_AWS

Description:
In this project the ESP32 is connected with AWS IoT Core & publish sensor reading to AWS MQTT. 
We are using DHT22 Sensor and reading the humidity and temperature data. 
The ESP32 connects to the local WiFi network and publish DHT22 Sensor data to AWS IoT Cloud. We can also receive the data from AWS Dashboard into the ESP32 and display on serial.

![WhatsApp Image 2024-08-28 at 4 43 16 PM](https://github.com/user-attachments/assets/d0e60654-d1ac-4705-9e4e-65c015e21ea9)

### Setup AWS IOT Core
It involves setting up AWS account, creating a Thing, setting up Policy, then generating certificates.
Add certificates in the project
Subscribe and Publish data to and from AWS Dashboard on MQTT test client.

- All related libraries were added
- Ensure connectivity with WiFi, AWS and Sensor.
- The Data is sent from ESP32 to AWS cloud via MQTT protocol.
- The Data can be viewed on Serial port and AWS Dashboard

### Output

> ESP32 is connected with WiFi and AWS IoT core. Temperature and Humdity reading were sent on serial monitor and AWS Dashboard subscribed to the topic.
![CodeSnippet0](https://github.com/user-attachments/assets/fc31ff30-40e6-4b4b-b7c7-fac96f2a3f30)
![AWS Subscribe Data](https://github.com/user-attachments/assets/4acc7c1c-ff0d-4427-a983-5828d8615a9e)

.
.
.


> Similarly Data is published from AWS Dashboard to the ESP32 as can be seen on serial monitor.
![AWS Publish Data](https://github.com/user-attachments/assets/28fbd73f-a5ac-49b3-968e-ed167c787865)
![CodeSnippet](https://github.com/user-attachments/assets/510c58a5-6b5e-40ff-82fe-6222986aa09e)







