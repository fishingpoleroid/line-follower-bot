#define SENSOR_FAR_LEFT   2
#define SENSOR_LEFT       3
#define SENSOR_CENTER     4
#define SENSOR_RIGHT      7
#define SENSOR_FAR_RIGHT  8

#define MOTOR_L_IN_1  10
#define MOTOR_L_IN_2  11
#define MOTOR_R_IN_1 12
#define MOTOR_R_IN_2 13

#define MOTOR_L_ENA 5
#define MOTOR_R_ENA 6

int baseSpeed = 120; 
int mediumTurnSpeed = 150;
int hardTurnSpeed = 180;

int softOffset = 30;
int medOffset = 50;
int hardOffset = 80;

void setup() {
  pinMode(MOTOR_L_IN_1, OUTPUT);
  pinMode(MOTOR_L_IN_2, OUTPUT);
  pinMode(MOTOR_R_IN_1, OUTPUT);
  pinMode(MOTOR_R_IN_2, OUTPUT);

  pinMode(SENSOR_FAR_LEFT, INPUT);
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_CENTER, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);
  pinMode(SENSOR_FAR_RIGHT, INPUT);
}

void goForward() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);

  analogWrite(MOTOR_L_ENA, baseSpeed);
  analogWrite(MOTOR_R_ENA, baseSpeed);
}

void softLeft() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);

  analogWrite(MOTOR_L_ENA, baseSpeed - softOffset);
  analogWrite(MOTOR_R_ENA, baseSpeed);
}

void softRight() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);

  analogWrite(MOTOR_L_ENA, baseSpeed);
  analogWrite(MOTOR_R_ENA, baseSpeed - softOffset);
}

void mediumLeft() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);

  analogWrite(MOTOR_L_ENA, mediumTurnSpeed - medOffset);
  analogWrite(MOTOR_R_ENA, mediumTurnSpeed);
}

void mediumRight() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);

  analogWrite(MOTOR_L_ENA, mediumTurnSpeed);
  analogWrite(MOTOR_R_ENA, mediumTurnSpeed - medOffset);
}

void hardLeft() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);

  analogWrite(MOTOR_L_ENA, hardTurnSpeed - hardOffset);
  analogWrite(MOTOR_R_ENA, hardTurnSpeed);
}

void hardRight() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);

  analogWrite(MOTOR_L_ENA, hardTurnSpeed);
  analogWrite(MOTOR_R_ENA, hardTurnSpeed - hardOffset);
}

void stop() {
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, HIGH);
  digitalWrite(MOTOR_R_IN_1, HIGH);
  digitalWrite(MOTOR_R_IN_2, HIGH);
}

void loop() {
  bool sFL = digitalRead(SENSOR_FAR_LEFT);
  bool sL  = digitalRead(SENSOR_LEFT);
  bool sC  = digitalRead(SENSOR_CENTER);
  bool sR  = digitalRead(SENSOR_RIGHT);
  bool sFR = digitalRead(SENSOR_FAR_RIGHT);

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
