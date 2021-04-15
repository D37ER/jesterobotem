void lewo_o_krok() {
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, HIGH);
  digitalWrite(stepPin, HIGH);
  delay(100);
  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);
}

void prawo_o_krok() {
  digitalWrite(stepPin, HIGH);
  digitalWrite(dirPin, LOW);
  delay(100);
  digitalWrite(stepPin, LOW);
}

void gora_o_krok() {
  digitalWrite(stepPin2, LOW);
  digitalWrite(dirPin2, HIGH);
  digitalWrite(stepPin2, HIGH);
  delay(100);
  digitalWrite(dirPin2, LOW);
  digitalWrite(stepPin2, LOW);
}

void dol_o_krok() {
  digitalWrite(dirPin2, LOW);
  digitalWrite(stepPin2, HIGH);
  delay(100);
  digitalWrite(stepPin2, LOW);
}
