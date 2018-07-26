#include <Ultrasonic.h>


#define pino_trigger 4
#define pino_echo 5


Ultrasonic ultrasonic(pino_trigger, pino_echo);
#define Sensor_linha 6
bool linha;
int pinMotors[] = {8, 9, 10, 11}; 

void setup()
{
  Serial.begin(9600);
  pinMode(Sensor_linha, INPUT);
  for (int i = 0; i < sizeof(pinMotors); i++) {
    pinMode(pinMotors[i], OUTPUT);
  }
}

void loop()
{

  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  Serial.print(cmMsec);

  linha = digitalRead(Sensor_linha);
   
  if ( linha == True && cmMsec == 15.0){
      Motor(255,255);
      delay(1000);
  } else {
    for (int i = 10; i < 200; i++) {
      Motor(i,i+5);
      if (cmMsec == 15.0){
         Motor(255,255);
         delay(1000);
				}
      }
  }

}

void Motor(int left, int right) {
  digitalWrite(pinMotors[0], left > 0 ? LOW : (left != 0 ? HIGH : LOW));
  analogWrite(pinMotors[1], left);
  digitalWrite(pinMotors[2], right > 0 ? LOW : (right != 0 ? HIGH : LOW));
  analogWrite(pinMotors[3], right);
}

