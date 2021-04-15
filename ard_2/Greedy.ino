void wyswietl_panel_startowy6() {
  Serial.println("Co chcesz zrobic?");
  Serial.println("1. [S] Sprawdzaj sposobem zachlannym");
  Serial.println("2. [M] Ustaw na pozycje poczatkowa");
  Serial.println("3. [Y] Zmien tryb");
  Serial.println("4. [X] Zakoncz");
  Serial.println("Podaj znak wybranej opcji: ");
}

void greedy(String odczytano) {
  if (Serial.available() > 0) {
    odczytano = Serial.readStringUntil('\n');
    int16_t odczyt = odczytano[0];
    switch (odczyt) {
      case 83://S-start
        pomiar_greedy();
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

void pomiar_greedy() {
  int16_t naj_lewo, naj_gora;
  delay(1000);
  pomiar();
  while (true) {
    if (ile_lewo < maks_obrot) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
    delay(1000);
    pomiar();

    if (ile_gora < maks_obrot) {
      gora_o_krok();
      ile_gora = (ile_gora + 1) % 200;
    }
    delay(1000);
    pomiar();

    if (ile_lewo > -maks_obrot) {
      prawo_o_krok();
      ile_lewo = (ile_lewo - 1) % 200;
    }
    delay(1000);
    pomiar();

    if (ile_lewo > -maks_obrot) {
      prawo_o_krok();
      ile_lewo = (ile_lewo - 1) % 200;
    }
    delay(1000);
    pomiar();

    if (ile_gora > -maks_obrot) {
      dol_o_krok();
      ile_gora = (ile_gora - 1) % 200;
    }
    delay(1000);
    pomiar();

    if (ile_gora > -maks_obrot) {
      dol_o_krok();
      ile_gora = (ile_gora - 1) % 200;
    }
    delay(1000);
    pomiar();

    if (ile_lewo < maks_obrot) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
    delay(1000);
    pomiar();

    if (ile_lewo < maks_obrot) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
    delay(1000);
    pomiar();

    if (naj_lewo == najlepsza_pozycja_lewo && naj_gora == najlepsza_pozycja_gora) {
      break;
    } else {
      ustaw_na_najlepsza();
      naj_lewo = najlepsza_pozycja_lewo;
      naj_gora = najlepsza_pozycja_gora;
    }
  }

}
