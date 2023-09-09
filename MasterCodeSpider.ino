
#include "HCPCA9685.h"
#include <IRremote.h>
#define IR_RECEIVE_PIN 6
#define red_led 4
#define green_led 2

#define IR_Power 69 // IR button codes deciphered
#define IR_VolUp 70
#define IR_FuncStop 71
#define IR_ArrowLeft 68
#define IR_Pause 64
#define IR_ArrowRight 67
#define IR_VolumeDown 21
#define IR_ArrowUp 9
#define IR_0 22
#define IR_EQ 25
#define StRept 13
#define IR_1 12
#define IR_2 24
#define IR_3 94
#define IR_4 8
#define IR_5 28
#define IR_6 90
#define IR_7 66
#define IR_8 82
#define IR_9 74

int serPos0 = 210; //default servo positions
int serPos1 = 220;
int serPos2 = 280;
int serPos3 = 200;
int serPos4 = 180;
int serPos5 = 120;
int serPos6 = 200;
int serPos7 = 160;
int serPos8 = 90;
int serPos9 = 200;
int serPos10 = 200;
int serPos11 = 300;

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address
   is 0x40 */
#define  I2CAdd 0x40


/* Create an instance of the library */
HCPCA9685 HCPCA9685(I2CAdd);


void setup() 
{
  /* Initialise the library and set it to 'servo mode' */ 
  HCPCA9685.Init(SERVO_MODE);

  Serial.begin(9600); // IR code
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  /* Wake the device up */
  HCPCA9685.Sleep(false);
  // servo(servo#, angle /2)
  default_stand();
}

//
//servo 0: decrease is counterclockwise and increase is clockwise for servo 0  (leg goes in when decrease)
//servo 1: increase is counterclockwise and decrease is clockwise (leg goes up when decrease)
//servo 2: clockwise is decrease and counterclockwise is increase (leg goes forward when decrease)

//servo 3: counterclockwise is decrease and increase is clockwise (decrease means it moves outwards)
//servo 4: clockwise is decrease and counterclockwise is increase (leg moves inwards when decreases)
//servo 5: clockwise is decrease and counterclockwise is increase (leg moves forward when decreases)

//servo 6: counterclockwise is decrease and increase is clockwise (decrease means it moves outwards)
//servo 7: clockwise when decrease and counterclockwise when increase (decrease means it moves inward)
//servo 8: clockwise when decrease and counterclockwise when increase (decrease means it moves backward)

//servo 9: counterclockwise is decrease and increase is clockwise (decrease means it moves inwards)
//servo 10: clockwise when decrease and counterclockwise when increase (decrease means it moves upward)
//servo 11: clockwise when decrease and counterclockwise when increase (decrease means it moves backward)

void loop() 
{
  digitalWrite(red_led, LOW); 
  digitalWrite(green_led, LOW);

 if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    switch (command) {
      case IR_Pause: { //reset standing position
        Serial.println("Pressed on Pause");
        digitalWrite(green_led, HIGH);
        delay(100);
        default_stand();
        break;
      case IR_1: { //stand
        Serial.println("Pressed on button 1");
        digitalWrite(green_led, HIGH);
        delay(100);
        stand();
        
        delay(100);
        break;
      }
      case IR_2: {//sit
        Serial.println("Pressed on button 2");
        digitalWrite(green_led, HIGH);
        delay(100);
        sit();
        delay(100);
        break;
      }
      case IR_3: {
        Serial.println("Pressed on button 3");
        digitalWrite(green_led, HIGH);
        wave();
        delay(100);

        break;
      }
      case IR_4: {
        Serial.println("Pressed on button 4");
        digitalWrite(green_led, HIGH);
        lift_leg_1();
        delay(100);

        break;
      }
      case IR_5:{
        Serial.println("Pressed on button 5");
        digitalWrite(green_led, HIGH);
        lift_leg_2();
        delay(100);

        break;
      }
      case IR_6:{
        Serial.println("Pressed on button 6");
        digitalWrite(green_led, HIGH);
        lift_leg_3();
        delay(100);

        break;
      }
      case IR_7:{
        Serial.println("Pressed on button 7");
        digitalWrite(green_led, HIGH);
        lift_leg_4();
        delay(100);

        break;
      }
      case IR_8:{
        Serial.println("Pressed on button 8");
        digitalWrite(green_led, HIGH);
        walk_init();
        delay(100);

        break;
      }
      case IR_9:{
        Serial.println("Pressed on button 9");
        digitalWrite(green_led, HIGH);
        walk();
        delay(100);

        break;
      }
      

      }
      default: {
        Serial.println("Button not recognized");
        digitalWrite(red_led, HIGH);
        delay(1000);
      }
    }
  }
}

void default_stand() {
  serPos0 = 220; //default servo positions
 serPos1 = 220;
 serPos2 = 280;
 serPos3 = 180;
 serPos4 = 180;
  serPos5 = 120;
  serPos6 = 180;
  serPos7 = 160;
  serPos8 = 90;
  serPos9 = 220;
  serPos10 = 200;
  serPos11 = 300;
  HCPCA9685.Servo(0, serPos0);//default position //claw
  HCPCA9685.Servo(1, serPos1);//default //tibia
  HCPCA9685.Servo(2, serPos2);//default //coxa

  HCPCA9685.Servo(3, serPos3);//default //claw
  HCPCA9685.Servo(4, serPos4);//default //tibia
  HCPCA9685.Servo(5, serPos5);//default //coxa

  HCPCA9685.Servo(6, serPos6);//default //claw
  HCPCA9685.Servo(7, serPos7);//default //tibia
  HCPCA9685.Servo(8, serPos8);//default //coxa

  HCPCA9685.Servo(9, serPos9);//default //claw
  HCPCA9685.Servo(10, serPos10);//default //tibia
  HCPCA9685.Servo(11, serPos11);//default //coxa

  

}

void stand() {

  for (int claw = 0; claw < 50; claw ++){
    serPos0 --;
    serPos3 ++;
    serPos6 ++;
    serPos9 --;

      serPos1 ++;
      serPos4 --;
      serPos7 --;
      serPos10 ++;

        HCPCA9685.Servo(1, serPos1);//tibia 130 to 220
        HCPCA9685.Servo(4, serPos4);//tibia 270 to 180
        HCPCA9685.Servo(7, serPos7);//tibia 250 to 160
        HCPCA9685.Servo(10, serPos10);//tibia 110 to 200
    
    HCPCA9685.Servo(0, serPos0);//claw 230 to 200
    HCPCA9685.Servo(3, serPos3);//claw 170 to 200
    HCPCA9685.Servo(6, serPos6);//claw 170 to 200
    HCPCA9685.Servo(9, serPos9);//claw 230 to 200 

    delay(10);
  
}
}

void sit(){
      serPos0 = 230;
      serPos1 = 130;
      serPos3 = 170;
      serPos4 = 270;
      serPos6 = 170;
      serPos7 = 250;
      serPos9 = 230;
      serPos10 = 110;

        HCPCA9685.Servo(0, serPos0);//claw 
        HCPCA9685.Servo(1, serPos1);//tibia 
        
        HCPCA9685.Servo(3, serPos3);//claw 
        HCPCA9685.Servo(4, serPos4);//tibia 
        
        HCPCA9685.Servo(6, serPos6);//claw 
        HCPCA9685.Servo(7, serPos7);//tibia 
        
        HCPCA9685.Servo(9, serPos9);//claw  
        HCPCA9685.Servo(10, serPos10);//tibia 
  
}

void wave(){

        serPos2 = 190;
        HCPCA9685.Servo(2, serPos2);//coxa
        serPos1 = 250;
        HCPCA9685.Servo(5, serPos5);//coxa


        delay(1000);

        for (int i = 0; i < 5; i++){
          serPos3 = 100;
          serPos4 = 360;
          HCPCA9685.Servo(3, serPos3);//claw 
          HCPCA9685.Servo(4, serPos4);//tibia 

          delay(400);

          serPos3 = 230;
          serPos4 = 270;
          HCPCA9685.Servo(3, serPos3);//claw 
          HCPCA9685.Servo(4, serPos4);//tibia 
          delay(400);

        } 

        serPos2 = 280;
        serPos3 = 200;
        serPos4 = 180;
        HCPCA9685.Servo(2, serPos2);//coxa
        HCPCA9685.Servo(3, serPos3);//coxa
        HCPCA9685.Servo(4, serPos4);//coxa



}

void lift_leg_1()
{

  serPos0 = 220; //default servo positions
 serPos1 = 220;
 serPos2 = 280;
  
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(1, serPos1);
    serPos1--;
    delay(10);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(0, serPos0);
    serPos0++;
    delay(10);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(2, serPos2);
    serPos2++; 
    delay(10);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(0, serPos0);
    serPos0--;
    delay(10);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(1, serPos1);
    serPos1++;
    delay(10);    
  }
}

void lift_leg_2()
{

  serPos3 = 200;
 serPos4 = 180;
  serPos5 = 120;
  
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(4, serPos4);
    serPos4++;
    delay(10);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(5, serPos5);
    serPos5++; 
    delay(10);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(4, serPos4);
    serPos4--;
    delay(10);
  }
}

void lift_leg_3()
{

  serPos6 = 200;
  serPos7 = 160;
  serPos8 = 90;
  
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(7, serPos7);
    serPos7++;
    delay(9);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(8, serPos8);
    serPos8--; 
    delay(9);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(7, serPos7);
    serPos7--;
    delay(9);
  }
}


void lift_leg_4()
{

  serPos9 = 200;
  serPos10 = 200;
  serPos11 = 300;
  
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(10, serPos10);
    serPos10--;
    delay(9);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(11, serPos11);
    serPos11--; 
    delay(9);
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(10, serPos10);
    serPos10++;
    delay(9);
  }
}


void walk_init()
{
  serPos0 = 200; //default servo positions
 serPos1 = 220;
 serPos2 = 320;
 serPos3 = 200;
 serPos4 = 180;
  serPos5 = 120;
  serPos6 = 200;
  serPos7 = 160;
  serPos8 = 180;
  serPos9 = 200;
  serPos10 = 200;
  serPos11 = 200;

  HCPCA9685.Servo(0, serPos0);
  HCPCA9685.Servo(1, serPos1);
  HCPCA9685.Servo(2, serPos2);
  HCPCA9685.Servo(3, serPos3);
  HCPCA9685.Servo(4, serPos4);
  HCPCA9685.Servo(5, serPos5);
  HCPCA9685.Servo(6, serPos6);
  HCPCA9685.Servo(7, serPos7);
  HCPCA9685.Servo(8, serPos8);
  HCPCA9685.Servo(9, serPos9);
  HCPCA9685.Servo(10, serPos10);
  HCPCA9685.Servo(11, serPos11);
  
}

void walk()
{
  serPos0 = 200; //default servo positions
 serPos1 = 220;
 serPos2 = 320;
 serPos3 = 200;
 serPos4 = 180;
  serPos5 = 120;
  serPos6 = 200;
  serPos7 = 160;
  serPos8 = 180;
  serPos9 = 200;
  serPos10 = 200;
  serPos11 = 200;

  //Lift leg 3 and move forward
  for(int i = 0; i < 80; i++)
  {
    HCPCA9685.Servo(7, serPos7);
    serPos7++;
  }
  for(int i = 0; i < 80; i++)
  {
    HCPCA9685.Servo(8, serPos8);
    serPos8--;
  }
  for(int i = 0; i < 60; i++)
  {
    HCPCA9685.Servo(6, serPos6);
    serPos6--;
  }
  
}




