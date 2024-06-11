/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: Arduino 24h Binary Clock (17 LEDs) und Reset

**************************************************************************************************
Version: 22.11.2023
**************************************************************************************************
Board: NANO
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino
D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
C++ Arduino IDE V1.8.19

**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/

// pins s, m h
int ledPinsSec[] = {2, 3, 4, 5, 6, 7};
int ledPinsMin[] = {8, 9, 10, 11, 12, 13}; 
int ledPinsHr[] = {14, 15, 16, 17, 18, 19};

// Startzeit
int countH = 11;  // h
int countM = 20;  // m
int countS = 0;   // s

byte countSec;
byte countMin;
byte countHr;
#define nBitsSec sizeof(ledPinsSec)/sizeof(ledPinsSec[0])
#define nBitsMin sizeof(ledPinsMin)/sizeof(ledPinsMin[0])
#define nBitsHr sizeof(ledPinsHr)/sizeof(ledPinsHr[0])

// -------------
void setup(void)
{
  for (byte i = 0; i < nBitsSec; i++) {
    pinMode(ledPinsSec[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsMin; i++) {
    pinMode(ledPinsMin[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsHr; i++) {
    pinMode(ledPinsHr[i], OUTPUT);
  }
}

// -------------

void loop(void)
{
  countS = (countS + 1);
  if (countS > 59)
  {
    countS = 0;
    countM = (countM + 1);
    if (countM > 59)
    {
      countM = 0;
      countH = (countH + 1);
      if (countH > 23)
      {
        countH = 0;
        countM = 0;
        countS = 0;
      }
    }
  }

  dispBinarySec(countS);
  dispBinaryMin(countM);
  dispBinaryHr(countH);

  delay(1000);   // 1000 Millisekunden = ca. 1 Sekunde Verzögerung
  //Aenderung für schnell oder langsam laufende Uhr hier, in Millisekunden.
}

// ----- Unterprogramm ---------------------------------------------------

void dispBinarySec(byte nSec)
{
  for (byte i = 0; i < nBitsSec; i++) {
    digitalWrite(ledPinsSec[i], nSec & 1);
    nSec /= 2;
  }
}

void dispBinaryMin(byte nMin)
{
  for (byte i = 0; i < nBitsMin; i++) {
    digitalWrite(ledPinsMin[i], nMin & 1);
    nMin /= 2;
  }
}

void dispBinaryHr(byte nHr)
{
  for (byte i = 0; i < nBitsHr; i++) {
    digitalWrite(ledPinsHr[i], nHr & 1);
    nHr /= 2;
  }
}
