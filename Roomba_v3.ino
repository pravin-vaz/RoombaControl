#include <BluetoothSerial.h>
#include <Roomba.h>
#include <SimpleTimer.h>


BluetoothSerial SerialBT;
Roomba roomba(&Serial, Roomba::Baud115200);

int chargingState = 100;
int batteryVoltage = 0;
String infoToApp;
uint8_t tempBuf[10];

void roombaInfo() {
  roomba.start();
  roomba.getSensors(21, tempBuf, 1);
  chargingState = tempBuf[0];
  delay(50);
  
  roomba.getSensors(22, tempBuf, 5);
  batteryVoltage = tempBuf[1];
  delay(50);
  
  infoToApp = (String)chargingState + "," + (String)batteryVoltage;
  SerialBT.println(infoToApp);
  

}

void setup() {
  SerialBT.begin("ESP32_Roomba"); //identify roomba
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);

  Serial.write(129);
  //delay(50);
  Serial.write(11);
  delay(50);
  Serial.print("Roomba ready");

  
  
}

char c;
void loop() 
{
   if (SerialBT.available()) 
   {
    c = SerialBT.read();
    if (c == '1') {
      roomba.dock();
      
    }
    if (c == '2') {
      roomba.safeMode();
      
    }
    if (c == '3') {
      roomba.spot();

    }
    if (c == '4') {
      
    }
    if (c == '5'){
      roomba.fullMode();
    }
    if (c=='w'){
      roomba.drive(200, 0);
    }
    if (c=='s'){
      roomba.drive(-200, 0);
    }
    if (c=='a'){
       roomba.drive(100, 0x0001);
    }
    if (c=='d'){
      roomba.drive(100,0xFFFF);
    } 
    if (c == 'I'){
      roombaInfo();
    }
    SerialBT.flush();
   } 
}
