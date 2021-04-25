void wyswietl_panel_startowy5() {
  Serial.println("Co chcesz zrobic?");
  Serial.println("1. [S] Sprawdzaj sposobem binarnym");
  Serial.println("2. [M] Ustaw na pozycje poczatkowa");
  Serial.println("3. [Z] Zapomnij o najlepszym pomiarze.");
  Serial.println("4. [Y] Zmien tryb");
  Serial.println("5. [X] Zakoncz");
  Serial.println("Podaj znak wybranej opcji: ");
}

void binary(String odczytano) {
  if (Serial.available() > 0) {
    odczytano = Serial.readStringUntil('\n');
    int16_t odczyt = odczytano[0];
    switch (odczyt) {
      case 83://S-start
        pomiary_bin();
        break;
      case 77://M
        ustaw_na_pocztek();
        break;
      case 90://Z
        zapomnij_najlepszy_pomiar();
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

void pomiary_bin() {
  int16_t x1, x2, n = 1;
  for (int i = 0; i < maks_obrot_poziom / n; i++) {
    lewo_o_krok();
    ile_lewo = (ile_lewo + 1) % 200;
  }
  x1 = ile_lewo;
  delay(1000);
  pomiar();
  for (int i = 0; i < 2 * maks_obrot_poziom / n; i++) {
    prawo_o_krok();
    ile_lewo = (ile_lewo - 1) % 200;
  }
  x2 = ile_lewo;
  delay(1000);
  pomiar();
  for (int i = 0; i < maks_obrot_poziom / n; i++) {
    lewo_o_krok();
    ile_lewo = (ile_lewo + 1) % 200;
  }
  for (int j = 0; j < 10; j++) {
    n = 2 * n;
    if (x1 == najlepsza_pozycja_lewo) {
      x2 = ile_lewo;
      delay(1000);
      pomiar();
      for (int i = 0; i < maks_obrot_poziom / n; i++) {
        lewo_o_krok();
        ile_lewo = (ile_lewo + 1) % 200;
      }
    } else {
      x1 = ile_lewo;
      delay(1000);
      pomiar();
      for (int i = 0; i < maks_obrot_poziom / n; i++) {
        prawo_o_krok();
        ile_lewo = (ile_lewo - 1) % 200;
      }
    }
  }


  n = 1;
  for (int i = 0; i < maks_obrot_pion / n; i++) {
    gora_o_krok();
    ile_gora = (ile_gora + 1) % 200;
  }
  x1 = ile_gora;
  delay(1000);
  pomiar();
  for (int i = 0; i < 2 * maks_obrot_pion / n; i++) {
    dol_o_krok();
    ile_gora = (ile_gora - 1) % 200;
  }
  x2 = ile_gora;
  delay(1000);
  pomiar();
  for (int i = 0; i < maks_obrot_pion / n; i++) {
    gora_o_krok();
    ile_gora = (ile_gora + 1) % 200;
  }
  for (int j = 0; j < 10; j++) {
    n = 2 * n;
    if (x1 == najlepsza_pozycja_gora) {
      x2 = ile_gora;
      delay(1000);
      pomiar();
      for (int i = 0; i < maks_obrot_pion / n; i++) {
        gora_o_krok();
        ile_gora = (ile_gora + 1) % 200;
      }
    } else {
      x1 = ile_gora;
      delay(1000);
      pomiar();
      for (int i = 0; i < maks_obrot_pion / n; i++) {
        dol_o_krok();
        ile_gora = (ile_gora - 1) % 200;
      }
    }
  }
  delay(1000);
  pomiar();
  ustaw_na_najlepsza();
}
