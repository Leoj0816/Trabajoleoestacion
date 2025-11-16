#ifndef _RADIOLIB_EX_LORAWAN_CONFIG_H
#define _RADIOLIB_EX_LORAWAN_CONFIG_H

#include <RadioLib.h>

// --- Configuración del módulo para TTGO LoRa32 v2.1 (SX1276 868/915 MHz)
SX1276 radio = new Module(18, 26, 14, 33);  // CS, DIO0, RST, DIO1

// --- Intervalo de envío ---
const uint32_t uplinkIntervalSeconds = 60;  // 1 minuto

// --- Credenciales OTAA ---
#define RADIOLIB_LORAWAN_JOIN_EUI  0x0000000000000000
#ifndef RADIOLIB_LORAWAN_DEV_EUI
#define RADIOLIB_LORAWAN_DEV_EUI   0x70B3D57ED0073CDC
#endif
#ifndef RADIOLIB_LORAWAN_APP_KEY
#define RADIOLIB_LORAWAN_APP_KEY   0x04,0xB4,0x28,0x6E,0xFA,0xE5,0xA6,0xCD,0xB2,0xBF,0xF9,0x2B,0xA3,0x9E,0xD2,0xC5
#endif
#ifndef RADIOLIB_LORAWAN_NWK_KEY
#define RADIOLIB_LORAWAN_NWK_KEY   0x9A,0xC4,0x59,0x2B,0xA2,0xD0,0x6E,0x93,0xCD,0x20,0x0D,0x1B,0x02,0xEB,0xE7,0xFB
#endif

// --- Configuración regional (Colombia usa US915) ---
const LoRaWANBand_t Region = US915;
const uint8_t subBand = 2;

// ============================================================================

uint64_t joinEUI =   RADIOLIB_LORAWAN_JOIN_EUI;
uint64_t devEUI  =   RADIOLIB_LORAWAN_DEV_EUI;
uint8_t appKey[] = { RADIOLIB_LORAWAN_APP_KEY };
uint8_t nwkKey[] = { RADIOLIB_LORAWAN_NWK_KEY };

LoRaWANNode node(&radio, &Region, subBand);

// Funciones auxiliares de depuración (sin cambios)
String stateDecode(const int16_t result) {
  switch (result) {
    case RADIOLIB_ERR_NONE: return "ERR_NONE";
    case RADIOLIB_ERR_CHIP_NOT_FOUND: return "ERR_CHIP_NOT_FOUND";
    case RADIOLIB_ERR_NETWORK_NOT_JOINED: return "RADIOLIB_ERR_NETWORK_NOT_JOINED";
    case RADIOLIB_LORAWAN_NEW_SESSION: return "RADIOLIB_LORAWAN_NEW_SESSION";
  }
  return "Ver lista completa en RadioLib docs";
}

void debug(bool failed, const __FlashStringHelper* message, int state, bool halt) {
  if(failed) {
    Serial.print(message);
    Serial.print(" - ");
    Serial.print(stateDecode(state));
    Serial.print(" (");
    Serial.print(state);
    Serial.println(")");
    while(halt) { delay(1); }
  }
}

void arrayDump(uint8_t *buffer, uint16_t len) {
  for(uint16_t c = 0; c < len; c++) {
    char b = buffer[c];
    if(b < 0x10) { Serial.print('0'); }
    Serial.print(b, HEX);
  }
  Serial.println();
}

#endif
