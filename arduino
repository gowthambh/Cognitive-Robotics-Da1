#include <DHT.h>

#define DHTPIN 2         
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);

#define MQ2_PIN A0       
#define TRIG_PIN 9       
#define ECHO_PIN 10      

#define LEFT_MOTOR_FORWARD 3
#define LEFT_MOTOR_BACKWARD 4
#define RIGHT_MOTOR_FORWARD 5
#define RIGHT_MOTOR_BACKWARD 6

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(MQ2_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}

long readUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

void loop() {
  float temperature = dht.readTemperature();
  int gasLevel = analogRead(MQ2_PIN);
  long distance = readUltrasonicDistance();

  // Send data to Raspberry Pi
  Serial.print("TEMP:");
  Serial.print(temperature);
  Serial.print(",GAS:");
  Serial.print(gasLevel);
  Serial.print(",DIST:");
  Serial.println(distance);

  if (distance > 20) {
    moveForward();
  } else {
    stopMotors();
    delay(500);
  }

  delay(1000);
}
