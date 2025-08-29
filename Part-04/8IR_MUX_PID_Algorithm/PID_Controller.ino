void PID_Controller(int base_speed, int p, int d) {
  read_black_line();

  if (sumOnSensor > 0) line_position = sensorWight / sumOnSensor;
  error = center_position - line_position;

  derivative = error - previous_error;

  int right_motor_correction = base_speed + (error * p + derivative * d);
  int left_motor_correction = base_speed - (error * p + derivative * d);

  previous_error = error;


  /*
  for (int i = 7; i >= 0; i--) {  //display bitsensor data
    Serial.print(String(bitRead(bitSensor, i)));
  }

  Serial.print("  Wright: " + String(sensorWight));
  Serial.print("  Error: " + String(error));
  Serial.print("  Correction Speed: " + String(left_motor_correction) + ", " + String(right_motor_correction));
  Serial.println();
  */

  motor(left_motor_correction, right_motor_correction);
}



void side_calibration() {
  read_black_line();  //take sensor reading

  for (int i = 7; i >= 0; i--) {  //display bitsensor data
    Serial.print(String(bitRead(bitSensor, i)));
  }

  if (bitSensor == 0b10000000) {
    Serial.print("  Side: Left");
  } else if (bitSensor == 0b00000001) {
    Serial.print("  Side: Right");
  } else {
    Serial.print("  Side: NULL");
  }

  Serial.println();
}