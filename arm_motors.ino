#include <IRremote.h>
#include <string.h>

int IN1pin = 4;
int IN2pin = 3;
int ENApin = 2;


int IN1pin2 = 12;
int IN2pin2 = 11;
int ENApin2 = 13;

int receiver_pin = 7;

int potpin = A0;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(receiver_pin);

  pinMode(IN1pin, OUTPUT);
  pinMode(IN2pin, OUTPUT);
  pinMode(ENApin, OUTPUT);
  pinMode(IN1pin2, OUTPUT);
  pinMode(IN2pin2, OUTPUT);
  pinMode(ENApin2, OUTPUT);

}
int motor_power = 0;
int value = 0;

void move(char area[], int dir){
    int pin = 0;
    Serial.println(area);
    
    if (strcmp(area,"front")){
      Serial.println(motor_power);
      motor_power = 1;
      write_direction(IN1pin2, IN2pin2, dir);
      analogWrite(ENApin2, 130);
      
    } else if (strcmp(area,"rear")){
      motor_power = -1;
      write_direction(IN1pin, IN2pin, dir);
      analogWrite(ENApin, 130);
    }

  }

void write_direction(int pin1, int pin2, int dir){
  if (dir > 0){
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
      } else {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
      }
}

void loop() {
  int sensor_value = analogRead(potpin);
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    value = IrReceiver.decodedIRData.command;
    
    
    switch (value){
      case int(22): 
        move("rear",1);
        break;
      case int(12): 
        move("rear",-1);
        break;
      case int(24):
        move("front",1);
        break;
      case int(28):
        move("front",-1);
        break;
      default:
        analogWrite(ENApin, 0);
        analogWrite(ENApin2, 0);
        break;
    }
    } else {
      analogWrite(ENApin, 0);
      analogWrite(ENApin2, 0);
    }

  


    delay(20);

  }
  

