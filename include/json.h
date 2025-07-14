#ifndef JSON_H
#define JSON_H

// Se requiere instalar ArduinoJson
#include <ArduinoJson.h>

// Tamaño del buffer JSON
#ifndef JSON_BUFFER_SIZE
#define JSON_BUFFER_SIZE 256
#endif

// Tipos de medios de comunicación, debería ser declarado en los medios de comunicación y no acá
enum class MediaType {
  ANY,
  MEDIA_TYPE_USB,
  MEDIA_TYPE_WIFI,
  MEDIA_TYPE_BLE,
  MEDIA_TYPE_MQTT
};

/*
  Los comandos deben ser registrados en jsonCommands:

  jsonCommands["comando"] = miFuncion;
  jsonCommands["comando"] = [](const JsonDocument& doc){código};

  Las funciones correspondientes deben ser void(const JsonDocument&).
 */
std::map<String, std::function<void(const JsonDocument&)>> jsonCommands;

/*
  Manejo de mensajes JSON
  Se cuelga de los medios de comunicación, que le pasan su payload como string.
  Se espera un objeto JSON con un campo "cmd" que indica el comando a ejecutar.
  Los comandos válidos son los declarados en jsonCommands.
  Si el comando no es reconocido retorna silenciosamente.
*/
void onJsonMessageReceived(const char* jsonStr, enum class MediaType mediaType = MediaType::ANY);

void sendJsonMessage(const JsonDocument&, enum class MediaType mediaType = MediaType::ANY);
#endif // JSON_H