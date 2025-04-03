#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "HT_SH1107Wire.h"

// Pantalla SH1107
SH1107Wire pantalla(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10);

// Buffer de mensajes
#define BUFFER_SIZE 64
char rxpacket[BUFFER_SIZE];

// Radio
static RadioEvents_t RadioEvents;

int16_t rssi = 0;
int16_t rxSize = 0;

// Función para mostrar mensaje recibido (temperatura y humedad separadas)
void mostrarPantalla(const char* mensaje) {
  pantalla.clear();
  pantalla.setFont(ArialMT_Plain_16);
  pantalla.drawString(0, 0, "Datos recibidos:");

  String msg = String(mensaje);
  int sep = msg.indexOf("|");

  if (sep > 0) {
    pantalla.drawString(0, 20, msg.substring(0, sep - 1));   // Temperatura
    pantalla.drawString(0, 40, msg.substring(sep + 2));      // Humedad
  } else {
    pantalla.drawString(0, 30, msg); // Mensaje completo en caso de error
  }

  pantalla.display();
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t _rssi, int8_t snr) {
  Radio.Sleep();

  rssi = _rssi;
  rxSize = size;
  memcpy(rxpacket, payload, size);
  rxpacket[size] = '\0';  // Asegurar string terminado

  mostrarPantalla(rxpacket);
  Radio.Rx(0);  // Reanudar recepción
}

void setup() {
  Serial.begin(115200);

  pantalla.init();
  pantalla.flipScreenVertically();
  pantalla.setFont(ArialMT_Plain_16);
  pantalla.clear();
  pantalla.drawString(0, 10, "Esperando datos...");
  pantalla.display();

  // LoRa
  RadioEvents.RxDone = OnRxDone;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(868000000);

  Radio.SetRxConfig(MODEM_LORA, 0, 7, 1, 0, 8, 0,
                    false, 0, true, 0, 0,
                    false, true);

  Radio.Rx(0);
}

void loop() {
  // No se necesita lógica aquí, todo ocurre en OnRxDone()
}
