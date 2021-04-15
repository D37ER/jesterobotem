void wyswietl_panel_startowy1() {
  Serial.begin(9600);
  Serial.println("Zaczynamy zabawe!");
  Serial.println("Wybierz tryb dzialania");
  Serial.println("1. Tryb automatyczny");
  Serial.println("2. Tryb manualny");
  Serial.println("3. Brute Force.");
  Serial.println("4. Wyszukiwanie binarne.");
  Serial.println("5. Wyszukiwanie zachlanne.");
  Serial.println("Podaj numer wybranej opcji: ");

  String odczytano1;
  int16_t odczyt1 = 0;
  while (odczyt1 != 2 && odczyt1 != 1) {
    odczytano1 = Serial.readStringUntil('\n');
    int16_t odczyt1 = odczytano1[0] - 48;
    if (odczyt1 == 1) {
      Serial.println("Wybrano tryb automatyczny");
      tryb_pracy = 1;
      wyswietl_panel_startowy3();
      break;
    }
    if (odczyt1 == 2) {
      Serial.println("Wybrano tryb manualny");
      tryb_pracy = 2;
      wyswietl_panel_startowy2();
      break;
    }
    if (odczyt1 == 3) {
      Serial.println("Wybrano brute force");
      tryb_pracy = 3;
      wyswietl_panel_startowy4();
      break;
    }
    if (odczyt1 == 4) {
      Serial.println("Wybrano wyszukiwanie binarne");
      tryb_pracy = 4;
      wyswietl_panel_startowy5();
      break;
    }
    if (odczyt1 == 5) {
      Serial.println("Wybrano wyszukiwanie zachlanne");
      tryb_pracy = 5;
      wyswietl_panel_startowy6();
      break;
    }
    delay(100);
  }

}

void ustaw_na_najlepsza() {
  while (najlepsza_pozycja_lewo > ile_lewo) {
    lewo_o_krok();
    ile_lewo = (ile_lewo + 1) % 200;
  }
  Serial.println("Ustawiono lewo");
  while (najlepsza_pozycja_lewo < ile_lewo) {
    prawo_o_krok();
    ile_lewo = (ile_lewo - 1) % 200;
  }
  Serial.println("Ustawiono prawo");
  while (najlepsza_pozycja_gora > ile_gora) {
    gora_o_krok();
    ile_gora = (ile_gora + 1) % 200;
  }
  Serial.println("Ustawiono gora");
  while (najlepsza_pozycja_gora < ile_gora) {
    dol_o_krok();
    ile_gora = (ile_gora - 1) % 200;
  }
  Serial.println("Ustawiono dol");

}

void ustaw_na_pocztek() {
  while (ile_lewo < 0) {
    lewo_o_krok();
    ile_lewo = (ile_lewo + 1) % 200;
  }
  Serial.println("Ustawiono lewo");
  while (ile_lewo > 0) {
    prawo_o_krok();
    ile_lewo = (ile_lewo - 1) % 200;
  }
  Serial.println("Ustawiono prawo");
  while (ile_gora < 0) {
    gora_o_krok();
    ile_gora = (ile_gora + 1) % 200;
  }
  Serial.println("Ustawiono gora");
  while (ile_gora > 0) {
    dol_o_krok();
    ile_gora = (ile_gora - 1) % 200;
  }
  Serial.println("Ustawiono dol");

}
void pomiar() {
  int16_t wartosc_z_czujnika = 0;
  for (int a = 0; a < liczba_pomiarow; a++) {
    wartosc_z_czujnika += analogRead(0);
  }
  wartosc_z_czujnika = wartosc_z_czujnika / liczba_pomiarow;
  Serial.println(wartosc_z_czujnika);
  //powinny byc wartosci 0-1023
  if (najlepsza_wartosc < wartosc_z_czujnika) {
    najlepsza_wartosc = wartosc_z_czujnika;
    najlepsza_pozycja_lewo = ile_lewo;
    najlepsza_pozycja_gora = ile_gora;
  }
  delay(100);
}

void pomiar_mapa(int dol, int prawo) {
  int wartosc_z_czujnika = 0;
  for (int a = 0; a < liczba_pomiarow; a++) {
    wartosc_z_czujnika += analogRead(0);
  }
  wartosc_z_czujnika = wartosc_z_czujnika / liczba_pomiarow;
  pomiary[dol][prawo] = wartosc_z_czujnika;
}

void wyswietl_mape() {
  for (int i = 0; i < ile_pomiarow; i++) {
    for (int j = 0; j < ile_pomiarow; j++) {
      Serial.print(pomiary[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void najlepszy_pomiar_w_mapie() {
  int najlepsza_wartosc = 0;
  int naj_prawo, naj_dol;
  for (int i = 0; i < ile_pomiarow; i++) {
    for (int j = 0; j < ile_pomiarow; j++) {
      if (najlepsza_wartosc < pomiary[i][j]) {
        najlepsza_wartosc = pomiary[i][j];
        naj_dol = i;
        naj_prawo = j;
      }
    }
  }
  najlepsza_pozycja_lewo = (ruch2 * naj_prawo - maks_obrot) * (-1);
  najlepsza_pozycja_gora = (ruch2 * naj_dol - maks_obrot) * (-1);
  delay(100);
}
