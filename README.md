# Monitor_iot
Humidity, Temperature and Light intensity monitor with MQTT IoT features and a Node-RED front-end.
Built with ESP-32 compatibility in mind.

! WIP ! This readme is currently being written. !

Libraries used: 
* Adafruit_GFX
* Adafruit_SSD1306
* PubSubClient
* DHT.h (By Adafruit)

## Example view of Node-Red GUI: 
![alt text](https://github.com/fsctnh/Monitor_iot/blob/098a293ff1bf891c41aeddcbee5d0485844b33c9/ExamplePhoto.png)

## View of OLED Display:
![alt text](https://github.com/fsctnh/Monitor_iot/blob/d8d5da900191723b257c4294729785bc7d2f6b3c/OLED_Display.jpeg)

## Schematic:
(Will be Added Soon!)

## Bill of Materials:
* SSD1306 OLED Display
* DHT11 Temperature and Humidity sensor (can be swapped for a DHT22)
* LDR + 10kOhm resistor
* ESP32-S2-WROOM (can be any microcontroller with wi-fi capabilities)

# Instructions of use:
* Run a Node-RED instance locally in your machine
* Import the "Flows_NodeRed.json" file to the instance and click "deploy" on the top right
* Compile and send the code (ESP32_MQTT_Code.ino) to your ESP32 circuit (Avoid using ADC2 pins for the LDR! They are disabled during Wi-Fi communication)
* Check for a successful connection and enjoy!
