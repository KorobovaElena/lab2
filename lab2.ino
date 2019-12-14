#include <Servo.h>

const int servoPin = 10;
const int sensorPin = A0;
const float voltsPerMeasurement = 5.0/1024.0;
const int delta = 5;
const int servoMin = 0;
const int servoMax = 90;

Servo servo;

int sweetDist;

bool servoIncreasing = true;

void setup() {
  Serial.begin(115200);
  sweetDist = 10;
  servo.attach(servoPin);
  servo.write(servoMin);
  delay(500); 
}

void loop() {
  float dist = getDist();
  Serial.println('Текущая дистанция = ' + dist);
  if (dist <= sweetDist + delta)
    servo.write(servoMax);
  else
    servo.write(servoMin);
}

float getDist(){
  float volts = readAnalog() * voltsPerMeasurement;
  return pow(14.7737/volts, 1.2134); // for small IR sensor (SHARP 2Y0A21)
}

float readAnalog()
{
  int sum = 0;
  int maxV = -5000;
  int minV = 5000;
  int n = 15;
  for (int i = 0; i < n; i++)
  {
    int cur = analogRead(sensorPin);
    if (cur > maxV)
    {
      maxV = cur;
    }
    if (cur < minV)
    {
      minV = cur;
    }
    sum += cur;
    delay(6);
  }
  return (sum - maxV - minV) / (float)(n - 2);
}
