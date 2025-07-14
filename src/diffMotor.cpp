#include "diffMotor.h"
#include <Arduino.h>

DiffMotors diffMotors;

void DiffMotors::init(int leftMotorPin, int leftPWMChannel, int leftDirPin, int rightMotorPin, int rightPWMChannel, int rightDirPin, int resolution, double frequency) {
  this->leftDirPin = leftDirPin;
  this->leftMotorPin = leftMotorPin;
  this->rightDirPin = rightDirPin;
  this->rightMotorPin = rightMotorPin;

  // Inicialización de pines y canales PWM de motores
  pinMode(leftDirPin, OUTPUT);
  ledcSetup(leftPWMChannel, frequency, resolution);
  ledcAttachPin(leftMotorPin, leftPWMChannel);
  ledcWrite(leftPWMChannel, 0);

  pinMode(rightDirPin, OUTPUT);
  ledcSetup(rightPWMChannel, frequency, resolution);
  ledcAttachPin(rightMotorPin, rightPWMChannel);
  ledcWrite(rightPWMChannel, 0);

  // Inicialización del temporizador de setPWM
  runTimer = xTimerCreate("DiffMotorsTimer", pdMS_TO_TICKS(1000), pdFALSE, nullptr, diffMotorsTimerCallback);
}

void DiffMotors::setPWM(int leftPWM, int rightPWM, int duration){
  xTimerStop(runTimer, 0);

  ledcWrite(leftPWMChannel, abs(leftPWM));
  ledcWrite(leftDirPin, leftPWM > 0 ? HIGH : LOW);

  ledcWrite(rightPWMChannel, abs(rightPWM));
  ledcWrite(rightDirPin, rightPWM > 0 ? HIGH : LOW);

  if(duration>0){
    xTimerChangePeriod(runTimer, pdMS_TO_TICKS(duration), 0);
    xTimerStart(runTimer, 0);
  }
}

void DiffMotors::jsonCommand(const JsonDocument& doc) {
  if (doc.containsKey("leftPWM") && doc.containsKey("rightPWM")) {
    if(doc.containsKey("duration")) {
      setPWM(doc["leftPWM"], doc["rightPWM"], doc["duration"]);
    } else {
      // Si no se especifica duración, usar el valor por defecto
      setPWM(doc["leftPWM"], doc["rightPWM"]);
    }
  }
}

void diffMotorsTimerCallback(TimerHandle_t){
  // Tiempo agotado, detener los motores
  diffMotors.stop();
}
