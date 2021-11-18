#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(10,19);  // create an RF24 object or a radio connection
const byte address[6] ="00001";
unsigned long lastRecievedTime = 0;
unsigned long currentTime=0;

//Structure to hold the input values of the controller. The max size of this can be 32 bytes(the NRF24L01 limit)
struct Structure
  {
    byte joystick1_x;
    byte joystick1_y;
  //byte joystick1_button;
    byte joystick2_x;
    byte joystick2_y;
  //byte joystick2_button;
    byte channel5;
    byte channel6;  
  };

Structure data;  // create a variable "data" using the above structure

void ResetData()
{
  data.joystick1_x = 127;
  data.joystick1_y = 127;
  data.joystick2_x = 127;
  data.joystick2_y = 127;
  data.channel5=127;
  data.channel6=127;
}

void setup() 
{
   // Initialize the radio communication
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();  //this sets the arduino module as a reciever
  ResetData();

}

void loop() 
{
  if (radio.available())
  {
    radio.read(&data, sizeof(Structure));   //reads the whole data and stores it in the data structure "Structure"
    lastRecievedTime =millis();     //when the data has been recieved
    
  }

  //Next we check for connection between the modules
  currentTime =millis();
  if (currentTime - lastRecievedTime > 1000)
  {
    // Note if the difference is more than 1 seconds , it means connection has been lost since we already recieved the last data
    ResetData(); // we reset data to prevent unfavourable conditions that may occur when connection is lost. By doing so we rest the datain the structure to default value
  }

}
