#include "json.h"
#include <map>

void onJsonMessageReceived(const char* jsonStr, enum class MediaType mediaType) {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;

  DeserializationError error = deserializeJson(doc, jsonStr);
  if (error) return;

  const char* cmd = doc["cmd"];
  if (!cmd) return;

  auto dispatch = jsonCommands[cmd];
  if (!dispatch) return;
  dispatch(doc, mediaType);
}

void sendJsonMessage(const JsonDocument& doc, enum class MediaType mediaType) {
  String jsonString;
  serializeJson(doc, jsonString);
  // Aquí se debería enviar el jsonString
  // TODO
}