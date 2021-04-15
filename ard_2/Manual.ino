void wyswietl_panel_startowy2() {
  Serial.println("Co chcesz zrobic?");
  Serial.println("1. [A] Przesun w lewo o krok");
  Serial.println("2. [D] Przesun w prawo o krok");
  Serial.println("3. [W] Przesun w gore o krok");
  Serial.println("4. [S] Przesun w dol o krok");
  Serial.println("5. [P] Dokonaj pomiaru");
  Serial.println("6. [B] Ustaw na najlepsza pozycje (z tych zmierzonych)");
  Serial.println("7. [M] Ustaw na pozycje poczatkowa");
  Serial.println("8. [Y] Zmien tryb");
  Serial.println("9. [X] Zakoncz");
  Serial.println("Podaj znak wybranej opcji: ");
}

void manual(String odczytano) {
  if (Serial.available() > 0) {
    odczytano = Serial.readStringUntil('\n');
    int odczyt = odczytano[0];
    switch (odczyt) {
      case 68://D
        prawo_o_krok();
        ile_lewo = (ile_lewo - 1) % 200;
        break;
      case 65://A
        lewo_o_krok();
        ile_lewo = (ile_lewo + 1) % 200;
        break;
      case 87://W
        gora_o_krok();
        ile_gora = (ile_gora + 1) % 200;
        break;
      case 83://S
        dol_o_krok();
        ile_gora = (ile_gora - 1) % 200;
        break;
      case 80://P
        pomiar();
        break;
      case 66://B
        ustaw_na_najlepsza();
        break;
      case 77://M
        ustaw_na_pocztek();
        break;
      case 89://Y
        wyswietl_panel_startowy1();
        break;
      case 88://X
        ustaw_na_pocztek();
        digitalWrite(dirPin, HIGH);
        digitalWrite(dirPin2, HIGH);
        delay(10);
        exit(0);
        break;
      default:
        Serial.println("Zly wybor, wybierz jeszcze raz");
    }
  }
}
