#include <Servo.h>

const int echoPin1 = 8;
const int trigPin1 = 9;
const int echoPin2 = 6;
const int trigPin2 = 7;
const int echoPin3 = 4;
const int trigPin3 = 5;

Servo manipulator;
int defaultPosition = 0;
int echoPins[] = {echoPin1,echoPin2,echoPin3};
int trigPins[] = {trigPin1,trigPin2,trigPin3};
int angles[] = {0,60,120};

void setup() {
  manipulator.attach(3);
   for (int i = 0; i < 3; ++i)
  {
    init(echoPins[i], trigPins[i]);
  }
  Serial.begin(115200);
}

void init(int echoPin, int trigPin) {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
}

void loop() {
  manipulator.write(getPosition());
  delay(500);
}

int getPosition() {
  float minimum = getPulse(echoPins[0], trigPins[0]);
  float pulseSensors[3];
   for (int i = 0; i < 3; ++i)
  {
    pulseSensors[i] = getPulse(echoPins[i], trigPins[i]);
    minimum = min(minimum, pulseSensors[i]);
  }
  for (int i = 0; i < 3; ++i)
  {
     if (minimum == pulseSensors[i]) {
    return angles[i];
  }
  }
  return 0;
}

float getPulse(int echoPin, int trigPin) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration;
}
