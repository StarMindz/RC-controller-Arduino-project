#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>


int joy1x =A0;
int joy1y =A1;
int joy2x =A2;
int joy2y =A3;
int pot1 =A4;
int pot2 =A5;

RF24 radio(5,6);                       //nrf object 
const byte address[6] = "00001";       //Address

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



void setup() {
  // Initialize the radio communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  pinMode(joy1x, INPUT);
  pinMode(joy1y, INPUT);
  pinMode(joy2x, INPUT);
  pinMode(joy2y, INPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);

  data.joystick1_x = 127;
  data.joystick1_y = 127;
  data.joystick2_x = 127;
  data.joystick2_y = 127;
  data.channel5=127;
  data.channel6=127;
  
  
}

void loop()
{
  // Read all input and scale down from 0 to 1023 to byte value of 0 to 255
  data.joystick1_x = map(analogRead(joy1x) ,0,1023,0,255);
  data.joystick1_y = map(analogRead(joy1y) ,0,1023,0,255);
  data.joystick2_x = map(analogRead(joy2x) ,0,1023,0,255);
  data.joystick2_y = map(analogRead(joy2y) ,0,1023,0,255);
  data.channel5 = map(analogRead(pot1) ,0,1023,0,255);
  data.channel6 = map(analogRead(pot2) ,0,1023,0,255);

  //Send whole Data from structure to reciever
  radio.write(&data, sizeof(Structure));
}
