void turnRight(int L, int R) {
  while (sensorDigital[4] != 1) {  //loop will break when sensor number 4 detects line.
    motor(L, -R);                  //right motor forward and left motor backward.
    read_black_line();             //observing continous change of sensor value.
    direction = "straight";        //set the direction value to default
  }
}

void turnLeft(int L, int R) {
  while (sensorDigital[4] != 1) {  //loop will break when sensor number 4 detects line.
    motor(-L, R);                  //right motor forward and left motor backward.
    read_black_line();             //observing continous change of sensor value.
    direction = "straight";        //set the direction value to default
  }
}

void hard_stop() {
  while (1) motor(0, 0);
}
void stop() {
  motor(0, 0);
}

void distance_calibration(uint16_t test_time) {
  unsigned long startTime = millis();
  while (millis() - startTime < test_time) {
    motor(base_speed, base_speed);  //forward movement
  }
  motor(0, 0);  //stop after completing the measured distance.
}

void distance(uint16_t dist) {
  int time_per_cm = test_time / measured_distance;
  unsigned long moveTime = dist * time_per_cm;
  unsigned long startTime = millis();

  while (millis() - startTime < moveTime) {
    motor(base_speed, base_speed);  //forward movement
  }
}
