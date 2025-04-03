#include <DHT.h>
#include "HT_SH1107Wire.h"
#include "LoRaWan_APP.h"
#include "Arduino.h"

// --- Configuración DHT22 ---
#define DHTPIN GPIO4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// --- Pantalla SH1107 ---
SH1107Wire pantalla(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10);

// --- LoRa ---
static RadioEvents_t RadioEvents;
bool lora_idle = true;

// --- Variables ---
float hum;
float temp;

void OnTxDone(void) {
  lora_idle = true;
}

void OnTxTimeout(void) {
  Radio.Sleep();
  lora_idle = true;
}

void setup() {
  // Iniciar pantalla
  pantalla.init();
  pantalla.flipScreenVertically();
  pantalla.setFont(ArialMT_Plain_16);
  pantalla.clear();
  pantalla.drawString(0, 10, "DHT22 + LoRa listo");
  pantalla.display();

  // Iniciar DHT22
  pinMode(DHTPIN, INPUT_PULLUP);
  dht.begin();
  delay(2000);

  // Configurar LoRa
  RadioEvents.TxDone = OnTxDone;
  RadioEvents.TxTimeout = OnTxTimeout;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(868000000);  // EU868

  Radio.SetTxConfig(MODEM_LORA, 14, 0, 0,
                    7, 1, 8,
                    false, true, 0, 0,
                    false, 3000);
}

void loop() {
  // Leer sensor
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  pantalla.clear();

  if (isnan(hum) || isnan(temp)) {
    pantalla.drawString(0, 10, "Error leyendo");
    pantalla.drawString(0, 30, "sensor DHT22");
    pantalla.display();
    delay(2000);
    return;
  }

  // Mostrar en pantalla
  pantalla.drawString(0, 10, "Temp: " + String(temp, 1) + " °C");
  pantalla.drawString(0, 30, "Hum:  " + String(hum, 1) + " %");
  pantalla.display();

  // Enviar por LoRa
  if (lora_idle) {
    char mensaje[48];
    sprintf(mensaje, "Temp: %.1f C | Hum: %.1f %%", temp, hum);
    Radio.Send((uint8_t *)mensaje, strlen(mensaje));
    lora_idle = false;
  }

  delay(2000);  // Leer cada 2 segundos
}
