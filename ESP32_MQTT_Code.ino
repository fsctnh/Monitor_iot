#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define LDR_PIN 35
#define DHT_PIN 18

const char* ssid = ""; //ADD YOUR DESIRED WI-FI SSID HERE
const char* password = ""; //ADD YOUR DESIRED WI-FI PASSWORD HERE

const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

int temperature = 0,
    humidity = 0, 
    ldrlum,
    ldrvalue;

char payload[10];
char payloadTEMP[10];
char payloadHUM[10];
char payloadLUM[10];

String message_global = "null";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHT11);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  dht.begin();
  
  analogSetAttenuation(ADC_11db);
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    display.setCursor(0, 0);
    display.printf("Conectando...");
    display.display();
    delay(1000);
  }
  display.setCursor(0, 10);
  display.printf("Conectando ao Wifi...");
  display.display();

  client.setServer(mqttServer, mqttPort);

  while(!client.connected()) {
    display.setCursor(0, 20);
    display.printf("Conectando ao MQTT...");
    display.display();

    if(client.connect("userid")) {
      display.setCursor(0, 30);
      display.printf("Conectado ao MQTT...");
      display.display();
      delay(5000);
    } else {
      display.setCursor(0, 40);
      display.printf("Falha de Conexao");
      display.display();
      delay(5000);
    }
  }
}

void DisplayDHT11()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.printf("Temperatura: %d %cC", temperature, 0XF7);
  display.setCursor(0, 10);
  display.printf("Umidade: %d %%", humidity);
  display.setCursor(0, 20);
  display.printf("Luminosidade: %d %%", ldrvalue);
  display.setCursor(0, 30);
  display.display();
}

void DHT11Read()
{
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}


void SendMQTT()
{
  snprintf(payloadTEMP, sizeof(payloadTEMP), "%d", temperature);
  client.publish("temp", payloadTEMP);
  snprintf(payloadHUM, sizeof(payloadHUM), "%d", humidity);
  client.publish("umidade", payloadHUM);
  snprintf(payloadLUM, sizeof(payloadLUM), "%d", ldrvalue);
  client.publish("luminosidade", payloadLUM);
}

void LDR_read(){
  ldrlum  =  analogRead(LDR_PIN);
  ldrvalue = map(ldrlum, 0, 4095, 0, 100);
  delay(100);
}

void loop() {
  client.loop(); 
  delay(100);
  DHT11Read();
  delay(100);
  LDR_read();
  delay(100);
  DisplayDHT11();
  SendMQTT();
  display.setCursor(0,100);
  display.printf("STATUS SUB: %s", message_global);
  display.display();
}