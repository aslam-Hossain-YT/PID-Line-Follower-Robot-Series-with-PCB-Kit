void turnRight(int L, int R) {
  while (sensorDigital[4] != 1) {  //loop will break when sensor number 4 detects line.
    motor(L, -R);                  //right motor backward and left motor forward.
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