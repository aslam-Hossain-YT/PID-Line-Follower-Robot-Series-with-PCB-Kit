//motorpins
#define right_motor_forward 2   //IN1(L298) || TB6612 -- AIN2
#define right_motor_backward 4  //IN2(L298) || TB6612 -- AIN1
#define left_motor_forward 5    //IN3(L298)  || TB6612 --- BIN1
#define left_motor_backward 6   //IN4(L298)  || TB6612 --- BIN2
//speed control pins (PWM)
#define right_motor_speed 3  //EnA (L298) //TB6612 --- PWMA
#define left_motor_speed 9   //EnB (L298) //TB6612 --- PWMB

//MUX PIN
#define S0 11
#define S1 10
#define S2 8
#define S3 7
#define SIG_PIN A3

//Sensor Variables
#define sensorNumber 8
int sensorADC[sensorNumber];
int sensorDigital[sensorNumber];
int bitWeight[sensorNumber] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int WeightValue[sensorNumber] = { 10, 20, 30, 40, 50, 60, 70, 80 };
int theshold = 500;
int sumOnSensor;
int sensorWight;
int bitSensor;

//PID Variables
float line_position;
float error;
float center_position = 45;
float derivative, previous_error;
int base_speed = 250;
int kp = 40;
int kd = 100;


//button
#define button1 A0
#define button2 12

//************************************SETUP***************************************
void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  pinMode(left_motor_speed, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
}


//************************************LOOP***************************************
void loop() {
  if (digitalRead(button1) == 0) {  //when button 1 is pressed
    while (1) {
      read_black_line();
    }
  }
  if (digitalRead(button2) == 0) {  //when button 2 is pressed
    while (1) {
      PID_Controller(base_speed, kp, kd);
    }
  }
}
