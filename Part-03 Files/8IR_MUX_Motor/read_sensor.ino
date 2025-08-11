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
    bitSensor += sensorDigital[i] * bitWeight[i];

    Serial.print(String(bitRead(bitSensor, i)));
  }
  Serial.print("  " + String(bitSensor));
  //Serial.print("  " + String(sumOnSensor) + "  " + String(sensorWight) + "  " + String(bitSensor));
  Serial.println();
}


void selectChannel(int channel) {
  digitalWrite(S0, bitRead(channel, 0));
  digitalWrite(S1, bitRead(channel, 1));
  digitalWrite(S2, bitRead(channel, 2));
  digitalWrite(S3, bitRead(channel, 3));
}