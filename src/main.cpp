#include <Arduino.h>

#include <TMC2209.h>

// Cet exemple ne fonctionnera pas sur les cartes Arduino sans ports HardwareSerial,
// comme l'Uno, le Nano et le Mini.
//
// Voir cette référence pour plus de détails :
// https://www.arduino.cc/reference/en/language/functions/communication/serial/
//
// Pour faire fonctionner cette bibliothèque avec ces cartes, référez-vous à cet exemple de bibliothèque :
// exemples/UnidirectionnelCommunication/SoftwareSerial

HardwareSerial &serial_stream = Serial3;

const uint8_t STEP_PIN = 2;
const uint8_t DIRECTION_PIN = 3;
const uint32_t STEP_COUNT = 51200;
const uint16_t HALF_STEP_DURATION_MICROSECONDS = 10;
const uint16_t STOP_DURATION = 1000;
// les valeurs actuelles peuvent devoir être réduites pour éviter une surchauffe en fonction de
// tension spécifique du moteur et de l'alimentation
const uint8_t RUN_CURRENT_PERCENT = 100;

// Instantiate TMC2209
TMC2209 stepper_driver;

void setup()
{
  stepper_driver.setup(serial_stream);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIRECTION_PIN, OUTPUT);

  stepper_driver.setRunCurrent(RUN_CURRENT_PERCENT);
  stepper_driver.enableCoolStep();
  stepper_driver.enable();
}

void loop()
{
  // Une étape nécessite deux itérations dans la boucle for
  for (uint32_t i = 0; i < STEP_COUNT * 2; ++i)
  {
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    delayMicroseconds(HALF_STEP_DURATION_MICROSECONDS);
  }
  digitalWrite(DIRECTION_PIN, !digitalRead(DIRECTION_PIN));
  delay(STOP_DURATION);
}
