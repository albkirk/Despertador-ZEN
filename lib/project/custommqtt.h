// Function to insert customized MQTT Configuration actions
char validData[10];

void  mqtt_custom(String reqparam, String reqvalue, JsonObject& data) {
  if ( reqparam == "Level") {SHADES = byte(long(data["value"]));}
  if ( reqparam == "Color") {
      strcpy(validData, data["value"]);
      if (validData[0] == '#') strcpy(Color, data["value"]);
  };
  if ( reqparam == "InitColor") {
      strcpy(config.InitColor, data["value"]);
      strcpy(Color, data["value"]);
      storage_write();
  };
  if ( reqparam == "Switch") {
      if (bool(data["value"]) == true) strcpy(Color, config.InitColor);
      else strcpy(Color, "#00000000");              // Color BLACK but, can't use the name as color is declared after mqtt
  }

}
