#ifndef JSONCOMMAND_H
#define JSONCOMMAND_H

#include <ArduinoJson.h>

/**
 * @brief Interfaz para comandos JSON
 * 
 * Usa estos parámetros:
 * - leftPWM: PWM del motor izquierdo
 * - rightPWM: PWM del motor derecho
 * - duration: (opcional) duración en milisegundos para la cual se debe mantener el PWM
 */
class JsonCommand {
public:
  virtual void jsonCommand(const JsonDocument&) = 0;
  virtual ~JsonCommand(){};
};


#endif // JSONCOMMAND_H