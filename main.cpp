#define MOTOR_L_IN_1     13
#define MOTOR_L_IN_2     12
#define MOTOR_R_IN_1     11
#define MOTOR_R_IN_2     10

#define MOTOR_L_ENA      5
#define MOTOR_R_ENA      6

#define SENSOR_FAR_LEFT  2
#define SENSOR_LEFT      3
#define SENSOR_CENTER    4
#define SENSOR_RIGHT     7
#define SENSOR_FAR_RIGHT 8

double error = 0;
double previousError = 0;
double integral = 0;
double derivative = 0;
double Kp = 0.05;
double Ki = 0.0001;
double Kd = 0.1;
double PIDvalue = 0;

int baseSpeed = 150;
int sensors[5];

void setup() {
  pinMode(MOTOR_L_IN_1, OUTPUT);
  pinMode(MOTOR_L_IN_2, OUTPUT);
  pinMode(MOTOR_R_IN_1, OUTPUT);
  pinMode(MOTOR_R_IN_2, OUTPUT);
  pinMode(MOTOR_L_ENA, OUTPUT);
  pinMode(MOTOR_R_ENA, OUTPUT);

  pinMode(SENSOR_FAR_LEFT, INPUT);
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_CENTER, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);
  pinMode(SENSOR_FAR_RIGHT, INPUT);
  
  digitalWrite(MOTOR_L_IN_1, HIGH);
  digitalWrite(MOTOR_L_IN_2, LOW);
  digitalWrite(MOTOR_R_IN_1, HIGH);
  digitalWrite(MOTOR_R_IN_2, LOW);
}

void loop() {
  calculateError();
  calculatePID();
  adjustMotors();
}

void calculateError() {
  sensors[0] = digitalRead(SENSOR_FAR_LEFT);
  sensors[1] = digitalRead(SENSOR_LEFT);
  sensors[2] = digitalRead(SENSOR_CENTER);
  sensors[3] = digitalRead(SENSOR_RIGHT);
  sensors[4] = digitalRead(SENSOR_FAR_RIGHT);
  
  long weightedSum = (long)sensors[0] * 0
    + (long)sensors[1] * 1000
    + (long)sensors[2] * 2000
    + (long)sensors[3] * 3000
    + (long)sensors[4] * 4000;
  
  int sum = sensors[0] + sensors[1] + sensors[2] + sensors[3] + sensors[4];
  
  long weightedAverage = weightedSum / sum;
  
  if (sum == 0) {
    error = previousError;
  } else {
    error = weightedAverage - 2000;
  }
}

void calculatePID() {
  integral += error;
  derivative = error - previousError;
  
  double P = Kp * error;
  double I = Ki * integral;
  double D = Kd * derivative;
  
  PIDvalue = P + I + D;
  previousError = error;
}

void adjustMotors() {
  int leftSpeed = constrain(baseSpeed + PIDvalue, 0, 255);
  int rightSpeed = constrain(baseSpeed - PIDvalue, 0, 255);
  
  analogWrite(MOTOR_L_ENA, leftSpeed);
  analogWrite(MOTOR_R_ENA, rightSpeed);
}
