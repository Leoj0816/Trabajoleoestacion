/*
  LoRaWAN TTGO LoRa32 v2.1 (SX1276 915 MHz)
  Basado en ejemplo RadioLib LoRaWAN Starter
  Configurado para región US915 (Colombia)
*/

#include "config.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(2000);
  Serial.println(F("\n=== Inicio de configuración TTGO LoRa32 ==="));

  // --- Inicialización del radio ---
  Serial.println(F("Inicializando módulo SX1276..."));
  int16_t state = radio.begin(915.0);
  debug(state != RADIOLIB_ERR_NONE, F("Fallo inicialización radio"), state, true);

  // --- Configurar frecuencia de operación (Colombia usa 915 MHz) ---
  state = radio.setFrequency(915.0);
  debug(state != RADIOLIB_ERR_NONE, F("Error configurando frecuencia"), state, true);

  Serial.print(F("Frecuencia configurada: "));
  Serial.print(radio.setFrequency(915.0));
  Serial.println(F(" MHz"));

  // --- Inicializar nodo LoRaWAN en modo OTAA ---
  Serial.println(F("Configurando sesión OTAA..."));
  state = node.beginOTAA(joinEUI, devEUI, nwkKey, appKey);
  debug(state != RADIOLIB_ERR_NONE, F("Fallo al inicializar nodo LoRaWAN"), state, true);

  // --- Intentar unirse a la red ---
  Serial.println(F("Intentando unirse a la red LoRaWAN (OTAA)..."));
  state = node.activateOTAA();
  debug(state != RADIOLIB_LORAWAN_NEW_SESSION, F("Error al unirse a la red"), state, true);

  Serial.println(F("✅ Nodo unido correctamente a la red LoRaWAN"));
  Serial.println(F("Listo para enviar datos...\n"));
}

void loop() {
  Serial.println(F("📡 Enviando uplink LoRaWAN..."));

  // --- Datos simulados ---
  uint8_t valor1 = radio.random(100);
  uint16_t valor2 = radio.random(2000);

  // --- Armar payload ---
  uint8_t payload[3];
  payload[0] = valor1;
  payload[1] = highByte(valor2);
  payload[2] = lowByte(valor2);

  // --- Enviar mensaje uplink ---
  int16_t state = node.sendReceive(payload, sizeof(payload));
  debug(state < RADIOLIB_ERR_NONE, F("Error en sendReceive()"), state, false);

  // --- Revisar respuesta ---
  if (state > 0) {
    Serial.println(F("📥 Downlink recibido"));
  } else {
    Serial.println(F("Sin downlink recibido"));
  }

  Serial.print(F("⏱️ Próximo envío en "));
  Serial.print(uplinkIntervalSeconds);
  Serial.println(F(" segundos.\n"));

  delay(uplinkIntervalSeconds * 1000UL);
}
