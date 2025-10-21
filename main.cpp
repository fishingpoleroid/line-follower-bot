#define SENSOR_FAR_LEFT   2
#define SENSOR_LEFT       3
#define SENSOR_CENTER     4
#define SENSOR_RIGHT      7
#define SENSOR_FAR_RIGHT  8

#define MOTOR_LEFT_IN1  5
#define MOTOR_LEFT_IN2  6
#define MOTOR_RIGHT_IN1 9
#define MOTOR_RIGHT_IN2 10


int baseSpeed = 12; 
int mediumTurnSpeed = 15;
int hardTurnSpeed = 18;

int offset = 3;

void setup() {
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_RIGHT_IN1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN2, OUTPUT);

  pinMode(SENSOR_FAR_LEFT, INPUT);
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_CENTER, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);
  pinMode(SENSOR_FAR_RIGHT, INPUT);

  Serial.begin(9600);
}


void goForward() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  analogWrite(MOTOR_LEFT_IN2, baseSpeed);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  analogWrite(MOTOR_RIGHT_IN1, baseSpeed);
}

void softLeft() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  analogWrite(MOTOR_LEFT_IN2, baseSpeed - offset);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  analogWrite(MOTOR_RIGHT_IN1, baseSpeed);
}

void softRight() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  analogWrite(MOTOR_LEFT_IN2, baseSpeed);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  analogWrite(MOTOR_RIGHT_IN1, baseSpeed - offset);
}

void mediumLeft() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  analogWrite(MOTOR_LEFT_IN2, mediumTurnSpeed - offset);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  analogWrite(MOTOR_RIGHT_IN1, mediumTurnSpeed);
}

void mediumRight() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  analogWrite(MOTOR_LEFT_IN2, mediumTurnSpeed);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  analogWrite(MOTOR_RIGHT_IN1, mediumTurnSpeed - offset);
}

void hardLeft() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  analogWrite(MOTOR_LEFT_IN2, hardTurnSpeed - offset);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  analogWrite(MOTOR_RIGHT_IN1, hardTurnSpeed);
}

void hardRight() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  analogWrite(MOTOR_LEFT_IN2, hardTurnSpeed);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  analogWrite(MOTOR_RIGHT_IN1, hardTurnSpeed - offset);
}

void stop() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
}

void loop() {
  bool sFL = digitalRead(SENSOR_FAR_LEFT);
  bool sL  = digitalRead(SENSOR_LEFT);
  bool sC  = digitalRead(SENSOR_CENTER);
  bool sR  = digitalRead(SENSOR_RIGHT);
  bool sFR = digitalRead(SENSOR_FAR_RIGHT);
  
  Serial.print(sFL);
  Serial.print(sL);
  Serial.print(sC);
  Serial.print(sR);
  Serial.print(sFR);
  Serial.println(" ");


  if (!sFL && !sL && sC && !sR && !sFR) {
    goForward();
  }
  else if (!sFL && sL && sC && !sR && !sFR) {
    softLeft();
  }
  else if (!sFL && !sL && sC && sR && !sFR) {
    softRight();
  }
  else if (!sFL && sL && !sC && !sR && !sFR) {
    mediumLeft();
  }
  else if (!sFL && !sL && !sC && sR && !sFR) {
    mediumRight();
  }
  else if (sFL) {
    hardLeft();
  }
  else if (sFR) {
    hardRight();
  }
  else if (!sFL && !sL && !sC && !sR && !sFR) {
    stop();
  }
}
