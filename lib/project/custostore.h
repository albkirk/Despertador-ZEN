// -- Variables --



// Function to insert customized STORAGE actions
void custo_JSON_TO_STRUCT() {
  config.Volume                 = root["Volume"];
  config.Alarm_State            = root["Alarm_State"];
  //config.AlarmDateTime          = root["AlarmDateTime"];
}

void custo_STRUCT_TO_JSON() {
  root["Volume"]                = config.Volume;
  root["Alarm_State"]           = config.Alarm_State;
  //root["AlarmDateTime"]         = config.AlarmDateTime;
}
