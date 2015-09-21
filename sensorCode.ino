/*********************************************************************************
Graphical Data Visualization of an Analog Sensor
*********************************************************************************/
#define DEBUG true                          
int g_sensorPin = A0;

/*********************************************************************************
Function Name     : setup
Description       : Initialize the Serial Communication with baud 9600, connect 
                    to the esp8266 with BAUD 115200 and initialize the sensor 
                    as INPUT.
Parameters        : void
Return            : void
*********************************************************************************/

void setup() {
  //Begin the Serial Communication Between the ESP8266 and AVR Chip with Baud 115200
  Serial4.begin(115200);
  //Begin the Serial Communication for Debugging with Serial Terminal
  Serial.begin(9600);
  //Setting the Analog Pin as a Sensor Input Pin
  pinMode(g_sensorPin,INPUT);
  espCommand("AT",500,DEBUG);
  espCommand("AT+RST",2000,DEBUG);
}

/*********************************************************************************
Function Name     : loop
Description       : Connect to the ThingSpeak API with TCP/IP Connection 
                    and post the sensor status to the graph
Parameters        : void
Return            : void
*********************************************************************************/

void loop() {
  char l_buffer[6] = "";
  String l_url = "GET /update?key=PR7KOM7IO91IP6GQ&field1=";
  int l_sensorValue = analogRead(g_sensorPin);
  l_url += String(l_sensorValue);
  l_url += "\r\n\r\n";
  espCommand("AT+CIPMUX=0",500,DEBUG);
  espCommand("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80",2000,DEBUG);
  if(Serial4.find("Error")) return;
  else{
    String l_cmd = "AT+CIPSEND=";
    l_cmd += l_url.length();
    espCommand(l_cmd,500,DEBUG);
    espCommand(l_url,3000,DEBUG);
    espCommand("AT+CIPCLOSE",3000,DEBUG);
  }
  delay(10000);
  espCommand("AT+RST",2000,DEBUG);
}

/*********************************************************************************
Function Name     : espCommand
Description       : Command the ESP8266 with AT Commands and receive the response
                    sent from the ESP8266 Module
Parameters        : p_command, p_timeout, p_debug
        p_command : AT Command for Requesting the ESP8266
        p_timeout : Timeout for the each Command
        p_debug   : if debug is True Serial Print the response obtained from 
                    the sensor
Return            : void
*********************************************************************************/
String espCommand(String p_command, const int p_timeout, boolean p_debug)
{
  String l_response = "";
  Serial4.println(p_command); 
  long int l_time = millis();
  while( (l_time+p_timeout) > millis())
  {
    while(Serial4.available())
    {
      char l_buffer = Serial4.read();
      l_response+=l_buffer;
    }
  }
  if(p_debug)
  {
    Serial.print(l_response);
  }
  return l_response;
}

//End of the Code
