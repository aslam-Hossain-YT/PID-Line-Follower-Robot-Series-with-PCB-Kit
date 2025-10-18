void read_black_line() {
  sumOnSensor = 0;
  sensorWight = 0;
  bitSensor = 0;

  for (int i = 0; i < sensorNumber; i++) {
    selectChannel(i);
    delayMicroseconds(20);
    sensorADC[i] = analogRead(SIG_PIN);
    //map analog value
    if (sensorADC[i] < 200) {
      sensorADC[i] = 0;
    } else if (sensorADC[i] > 300) {
      sensorADC[i] = 1000;
    }
    //analog to digital
    if (sensorADC[i] > theshold) {
      sensorDigital[i] = 1;
    } else {
      sensorDigital[i] = 0;
    }

    sumOnSensor += sensorDigital[i];
    sensorWight += sensorDigital[i] * WeightValue[i];
    bitSensor += sensorDigital[i] * bitWeight[7 - i];
  }
}

void selectChannel(int channel) {
  digitalWrite(S0, bitRead(channel, 0));
  digitalWrite(S1, bitRead(channel, 1));
  digitalWrite(S2, bitRead(channel, 2));
  digitalWrite(S3, bitRead(channel, 3));
}


void side_calibration() {
  read_black_line();  //take sensor reading

  Serial.print("Bit Sensor in Decimal: " + String(bitSensor));
  Serial.print(" | Bit Sensor in Binary: ");

  for (int i = 7; i >= 0; i--) {  //display bitsensor data in binary
    Serial.print(String(bitRead(bitSensor, i)));
  }
  /*
  if (bitSensor == 0b10000000) {
    Serial.print("  Side: Left");
  } else if (bitSensor == 0b00000001) {
    Serial.print("  Side: Right");
  } else {
    Serial.print("  Side: NULL");
  }
*/
  Serial.println();
}

void sensor_value_check() {
  for (int i = 0; i < sensorNumber; i++) {
    selectChannel(i);
    delayMicroseconds(20);
    sensorADC[i] = analogRead(SIG_PIN);
    //map analog value
    Serial.print(String(sensorADC[i]) + "  ");
  }
  for (int i = 0; i < sensorNumber; i++) {
    //analog to digital
    if (sensorADC[i] > theshold) {
      sensorDigital[i] = 1;
    } else {
      sensorDigital[i] = 0;
    }
    Serial.print("  " + String(sensorDigital[i]));
  }
  Serial.println();
}