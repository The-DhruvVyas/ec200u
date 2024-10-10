// created by : Dhruv Vyas 
// used to send and read the at response of ec200u lte modem 
#define TINY_GSM_MODEM_BG96
#include <HardwareSerial.h>

#define MODEM_RST 5  // Example pin for modem reset
#define MODEM_PWR 4  // Example pin for modem power

// Initialize hardware serial port for the modem
HardwareSerial modemSerial(2);
#define SerialAT modemSerial // serial port for gsm modem on teensy4.0

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);           // start serial for output
   Serial1.begin(115200, SERIAL_8N1, 16, 17);           // start serial for ESP
  // Power on and reset the modem (if applicable)
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_PWR, OUTPUT);

  // Reset the modem
  digitalWrite(MODEM_RST, HIGH);
  delay(1000);
  digitalWrite(MODEM_RST, LOW);

  // Power on the modem
  digitalWrite(MODEM_PWR, HIGH);
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
sendData("AT+QCSQ\r\n",10,true);
sendData("AT+QNWINFO\r\n",10,true);
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial1.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial1.read(); // read the next character.
        response+=c;
        delay(100);
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}