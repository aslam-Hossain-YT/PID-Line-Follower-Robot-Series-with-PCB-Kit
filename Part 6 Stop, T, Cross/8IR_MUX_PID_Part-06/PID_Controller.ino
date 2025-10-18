void PID_Controller(int base_speed, int p, int d) {
  read_black_line();

  if (sumOnSensor <= 2) line_position = sensorWight / sumOnSensor;
  error = center_position - line_position;

  switch (bitSensor) {
    //left side detection
    case 0b11111000: direction = "left"; break;
    case 0b11110000: direction = "left"; break;
    case 0b11111100: direction = "left"; break;
    //right side detection
    case 0b00011111: direction = "right"; break;
    case 0b00001111: direction = "right"; break;
    case 0b00111111: direction = "right"; break;
  }

  //turn execution when all the sensor on the white surface.
  if (bitSensor == 0) {
    error = 0;
    if (direction != "straight") {  //if the direction is either left or right
      digitalWrite(led, HIGH);      //turning on led as indicator when left or right turn is detected.
      delay(delay_before_turn);

      if (direction == "right") {
        //right turn logic
        turnRight(turnSpeed, turnSpeed);
      } else {
        //left turn logic
        turnLeft(turnSpeed, turnSpeed);
      }
      digitalWrite(led, LOW);  //after execution of turns the led will off
      hard_stop(); //after executing turns the robot will stop. this is only for turn test
    }
  } else if (bitSensor == 255) {
    //stop, T intersection, Cross intersection.
    digitalWrite(led, HIGH);    //led on when all black
    distance(5);               //move 10cm forward.
    read_black_line();          //then read sensor value
    while (bitSensor == 255) {  //if sensor value still on black line. that means its stop point
      stop();                   //then robot stop
      read_black_line();        //update sensor if it's changing or not.
    }
    if (bitSensor == 0) {
      direction = "right";  //turn for T intersection.
    } else {
      if (bitSensor > 0 && bitSensor < 255) {
        direction = "straight";  //for Cross intersection
      }
    }
  }

  /*
  //bitsensor data in binary
  for (int i = 7; i >= 0; i--) {  //display bitsensor data in binary
    Serial.print(String(bitRead(bitSensor, i)));
  }

  Serial.print("   Direction: " + String(direction));
  Serial.println();
*/
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
