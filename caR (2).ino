#include <SoftwareSerial.h>
//#include <ArduinoRobot.h>
#include <NewPing.h>
String voice;
const int mode = 2;//robot or remote mode pin
const int motor1Pin = 10;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 11;    // H-bridge leg 2 (pin 7, 2A)
const int motor3Pin = 6;    // H-bridge leg 1 (pin 10, 3A)
const int motor4Pin = 7;    // H-bridge leg 2 (pin 15, 4A)
const int jetmotor = 8;
const int enablePin = 9;    // H-bridge enable pin
char ch = 'S';
char prevCh='A';
boolean modestatus = true;
int modevalue = 0;
//unsigned long timer0=2000;
//unsigned long timer1=0;

#define TRIGGER_PIN1  14
#define ECHO_PIN1     15
#define TRIGGER_PIN2  16
#define ECHO_PIN2     17
#define MAX_DISTANCE 200

NewPing DistanceSensor1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing DistanceSensor2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);

SoftwareSerial Bluetooth (19, 18);//RX,TX

void forward(){
            digitalWrite(motor1Pin, HIGH);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);
            
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            
}

void autoforward(){
            //digitalWrite(motor1Pin, HIGH);   // set leg 1 of the H-bridge low
            analogWrite (motor1Pin, 150);
            analogWrite (motor2Pin, 0);  // set leg 2 of the H-bridge high
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
}
void forwardright(){
            digitalWrite(motor1Pin, HIGH);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, HIGH);
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
}
void forwardleft(){
            digitalWrite(motor1Pin, HIGH);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high
            digitalWrite(motor3Pin, HIGH);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
}

void backward(){
            digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);
            
            digitalWrite(12, LOW);
            digitalWrite(13, HIGH);
            
}
void autobackward(){
            //digitalWrite(motor1Pin, HIGH);   // set leg 1 of the H-bridge low
            analogWrite (motor1Pin, 0);
            analogWrite (motor2Pin, 100);  // set leg 2 of the H-bridge high
            digitalWrite(12, LOW);
            digitalWrite(12, HIGH);
}

void backwardleft(){
            digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, HIGH);
            digitalWrite(12, LOW);
            digitalWrite(13, HIGH);
            
}
void backwardright(){
            digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
            digitalWrite(motor3Pin, HIGH);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
            digitalWrite(12, LOW);
            digitalWrite(13, HIGH);
            
}

void left(){
            digitalWrite(motor3Pin, HIGH);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
         //   delay(250);
            digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high
             
}
void autoleft(){
            digitalWrite(motor3Pin, HIGH);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
            delay(500);
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
             
}

void right(){
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, HIGH);  // set leg 2 of the H-bridge high
           // delay(250);
            digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high
            
}
void autoright(){
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, HIGH);  // set leg 2 of the H-bridge high
            delay(500);
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
            
}

void carstop(){
            digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high
            digitalWrite(motor3Pin, LOW);   // set leg 1 of the H-bridge low
            digitalWrite(motor4Pin, LOW);  // set leg 2 of the H-bridge high
            digitalWrite(12, HIGH);
            digitalWrite(13, HIGH);  
      
}

/*void automode(){
  
        
    if (Bluetooth.available() >0)
   {
     char ch1 = Bluetooth.read();
         
     if(ch1=='x')
        {
         modestatus = true; //remote mode stays
        }
        
        else
        {
        unsigned int cm1 = DistanceSensor1.ping_cm();
        
        delay(20);
    
        unsigned int cm2 = DistanceSensor2.ping_cm();      
                  
        if (cm1<60 && cm2<60)    
        {
          carstop();
          delay (300);
          
          backward();
          right();
          delay(500);
                    
       
          carstop();
          delay(200);
               
        }
         else if (cm1>60 && cm2<60)
        {
          autoforward();
          autoright();
        }
        else if (cm1<60 && cm2>60)
        {
          autoforward();
          autoleft();
        }
         else if (cm1>60 && cm2>60){
        
          autoforward();
        }
        }
   } 
              
  else {
         carstop();        
 
  }
}*/
void automode(){
        
        unsigned int cm1 = DistanceSensor1.ping_cm();
        
        delay(20);
    
        unsigned int cm2 = DistanceSensor2.ping_cm();
        if (cm1<80 && cm2<80)    
        {
          //carstop();
          //delay (200);
          //for (int i= 0 ; i<200 ; i++){
          //tone(5, 500);
          backwardright();
          
          delay(800);
          //}
          carstop();
          //noTone(5); 
          //delay(200);
        }
        else if (cm1>80 && cm2<80)
        {
          autoforward();
          autoright();
        }
        else if (cm1<80 && cm2>80)
        {
          autoforward();
          autoleft();
        }
        else if (cm1>80 && cm2>80)
        autoforward();
        
        if (digitalRead(mode)==LOW)
        carstop();
        /*if (Bluetooth.available() ) {
      
        char ch = Bluetooth.read();
        if (ch == 'x')
        {
         modestatus = true;//remote mode 
        }        
}*/
}

       
        
             
void remotemode(){
        if (Bluetooth.available()>0 ) {
        prevCh = ch;
        ch = Bluetooth.read();
        
        if(ch!=prevCh){
         
    
        if (ch=='F'){ forward();}
       
        if (ch=='G') {forwardleft();}
        
        if(ch== 'I'){ forwardright();}
                
        if (ch== 'B'){ backward();}
         
        if (ch=='H') {backwardright();}
        
        if (ch=='J'){ backwardleft();}
        if(ch== 'L'){ left();}
        
        if(ch=='R'){ right();}
        
        if (ch=='S'){carstop();}
              
        if(ch=='X'){
        //modestatus =false;
        digitalWrite(jetmotor, LOW);
        }
        if(ch=='x'){
        //modestatus =false;
        digitalWrite(jetmotor, HIGH);
        }
        if(ch=='W'){
        //modestatus =false;
        digitalWrite(5, HIGH);
        }
        if(ch=='w'){
        //modestatus =false;
        digitalWrite(5, LOW);
        }
        }
        
}
        //else
        //carstop();
}
void setup()
{
  
 
    // set all the other pins you're using as outputs/input:
    pinMode(mode, INPUT);
    pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    pinMode(motor3Pin, OUTPUT);
    pinMode(motor4Pin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(jetmotor, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    
 
    // set enablePin high so that motor can turn on:
    digitalWrite(enablePin, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(jetmotor, HIGH);
    Bluetooth.begin(9600);
}

void loop()
{
 if (digitalRead(mode)==HIGH){ automode();}
 
 if (digitalRead(mode)==LOW){ remotemode();}
 
}
