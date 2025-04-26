char command;

#define LEFT_MOTOR_FORWARD 3
#define LEFT_MOTOR_BACKWARD 4
#define RIGHT_MOTOR_FORWARD 5
#define RIGHT_MOTOR_BACKWARD 6

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    if (command == 'F') {
      digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
      digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    }
    else if (command == 'B') {
      digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
      digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    }
    else if (command == 'L') {
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    }
    else if (command == 'R') {
      digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    }
    else if (command == 'S') {
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    }
  }
}
