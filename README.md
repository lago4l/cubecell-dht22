# CubeCell LoRa – Emisor y Receptor con Sensor DHT22

Este proyecto demuestra cómo comunicar dos placas **CubeCell HTCC-AB02** mediante **LoRa**, enviando datos de temperatura y humedad desde un sensor **DHT22** conectado al emisor, y visualizando esos datos en pantalla en ambas placas.

---

## Requisitos

- 2 placas **Heltec CubeCell HTCC-AB02**
- 2 antenas **LoRa** (una por placa)
- **Arduino IDE**
- Sensor **DHT22** conectado a la placa emisora
- Pantalla **SH1107** conectada a cada placa (I2C)
- Librerías necesarias:
  - `DHT sensor library` (de Adafruit)
  - `Adafruit Unified Sensor`
  - `HT_SH1107Wire`
  - `LoRaWan_APP` (incluida en el soporte oficial de CubeCell)

---

## Contenido del repositorio

- **CÓDIGO EMISOR** – Código que lee el sensor DHT22 y envía por LoRa los datos cada pocos segundos.
- **CÓDIGO RECEPTOR** – Código que recibe los datos por LoRa y los muestra por pantalla.
- **DOCUMENTACIÓN CUBECELL-DHT22.docx** – Guía paso a paso para conectar el sensor, configurar el entorno en Arduino IDE, y comprender el flujo del proyecto.

---

## Funcionalidad

### Emisor

- Lee la **temperatura y humedad** del sensor DHT22.
- Envía los datos en un mensaje LoRa al receptor.
- Muestra los datos por pantalla:

### Receptor

- Escucha mensajes LoRa de forma continua.
- Muestra los datos recibidos por pantalla

---

## Para más detalles

Consulta el documento **`DOCUMENTACIÓN CUBECELL-DHT22.docx`** incluido en el repositorio, donde se explica paso a paso:

- Conexiones físicas del sensor DHT22 a CubeCell
- Instalación de dependencias en Arduino IDE
- Uso del código de emisor y receptor

---
