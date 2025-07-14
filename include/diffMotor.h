#ifndef DIFF_MOTOR_H
#define DIFF_MOTOR_H

#include <freertos/timers.h>

class DiffMotors{
public:
  
  /**
   * @brief Constructor por defecto para declarar el objeto como variable global.
   */
  DiffMotors() = default;

  /**
   * @brief Inicializa los pines y canales PWM de los motores diferenciales.
   * @param leftMotorPin Pin del motor izquierdo.
   * @param leftPWMChannel Canal PWM del motor izquierdo.
   * @param leftDirPin Pin de dirección del motor izquierdo.
   * @param rightMotorPin Pin del motor derecho.
   * @param rightPWMChannel Canal PWM del motor derecho.
   * @param rightDirPin Pin de dirección del motor derecho.
   * @param resolution Resolución del PWM (por defecto 8 bits).
   * @param frequency Frecuencia del PWM (por defecto 100 Hz).
   */
  void init(int leftMotorPin, int leftPWMChannel, int leftDirPin, int rightMotorPin, int rightPWMChannel, int rightDirPin, int resolution=8, double frequency=100);
  #ifdef LeftMotorPin
  
  /**
   *  Si los pines están definidos, se proporciona init sin argumentos que usa los pines predefinidos
   */
  void init(int resolution=8, double frequency=100) {
      init(LeftMotorPin, LeftMotorPWMChannel, LeftMotorDirPin, RightMotorPin, RightMotorPWMChannel, RightMotorDirPin, resolution, frequency);
  };
  #endif

  /**
   * @brief Establece el PWM de los motores.
   * 
   * @param leftPWM Valor del PWM para el motor izquierdo.
   * @param rightPWM Valor del PWM para el motor derecho.
   * @param duration Duración en milisegundos para la cual se debe mantener el PWM. Si es 0, se mantiene indefinidamente.
   */
  void setPWM(int leftPWM, int rightPWM, int duration=0);

  /**
   * @brief Detiene los motores estableciendo el PWM a 0.
   */
  void stop() {
      setPWM(0, 0);
  }

  /** Handle para el temporizador de la función setPWM */
  TimerHandle_t runTimer = nullptr;

  /** Pines y canales PWM de los motores */
  int leftMotorPin, leftPWMChannel, leftDirPin, rightMotorPin, rightPWMChannel, rightDirPin;
};

extern DiffMotors diffMotors;



#endif // DIFF_MOTOR_H