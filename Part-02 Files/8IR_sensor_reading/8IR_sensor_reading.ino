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


//button
#define button1 A0
#define button2 12

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(button1) == 0) {
    while (1) {
      read_black_line();
    }
  }
}
