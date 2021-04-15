void wyswietl_panel_startowy4() {
  Serial.println("Co chcesz zrobic?");
  Serial.println("1. [N] Tryb zapamietywania tylko najlepszego polozenia.");
  Serial.println("2. [W] Tryb zapamietywania wszystkich polozen.");
  Serial.println("3. [P] Wyswietl pomiary z wszystkich polozen.");
  Serial.println("4. [M] Ustaw na pozycje poczatkowa.");
  Serial.println("5. [Y] Wroc do glownego menu.");
  Serial.println("6. [X] Zakoncz.");
  Serial.println("Podaj znak wybranej opcji: ");
}

void brute_force(String odczytano) {
  if (Serial.available() > 0) {
    odczytano = Serial.readStringUntil('\n');
    int odczyt = odczytano[0];
    switch (odczyt) {
      case 78://N-najlepsze polozenie
        najlepszy_pomiar_BF();
        break;
      case 87://W-wszystkie polozenia
        wszystkie_pomiary_BF();
        break;
      case 80://P-wyswietlanie polozen
        wyswietl_mape();
        break;
      case 77://M-pozycja pocz
        ustaw_na_pocztek();
        break;
      case 89://Y-menu glowne
        wyswietl_panel_startowy1();
        break;
      case 88://X-zakoncz
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

void najlepszy_pomiar_BF() {
  for (int i = 0; i < maks_obrot; i++) {
    if (ile_lewo < maks_obrot) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
  }//0L->1L 0G
  bool po_lewej = true;
  for (int i = 0; i < maks_obrot; i++) {
    if (ile_gora < maks_obrot) {
      gora_o_krok();
      ile_gora = (ile_gora + 1) % 200;
    }
  }//1L 0G->1G
  delay(1000);
  pomiar();
  for (int i = 0; i < ile_pomiarow; i++) {
    if (po_lewej) {
      while (ile_lewo > -maks_obrot) {
        for (int j = 0; j < ruch2; j++) {
          prawo_o_krok();
          ile_lewo = (ile_lewo - 1) % 200;
        }
        delay(1000);
        pomiar();
      }
      po_lewej = false;
    }
    else {
      while (ile_lewo < maks_obrot) {
        for (int j = 0; j < ruch2; j++) {
          lewo_o_krok();
          ile_lewo = (ile_lewo + 1) % 200;
        }
        delay(1000);
        pomiar();
      }
      po_lewej = true;
    }
    if (ile_gora > -maks_obrot) {
      for (int j = 0; j < ruch2; j++) {
        dol_o_krok();
        ile_gora = (ile_gora - 1) % 200;
      }
    }
  }
  ustaw_na_najlepsza();
}

void wszystkie_pomiary_BF() {
  int y = 0;
  for (int i = 0; i < maks_obrot; i++) {
    if (ile_lewo < maks_obrot) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
  }//0L->1L 0G
  bool po_lewej = true;
  for (int i = 0; i < maks_obrot; i++) {
    if (ile_gora < maks_obrot) {
      gora_o_krok();
      ile_gora = (ile_gora + 1) % 200;
    }
  }//1L 0G->1G
  delay(1000);
  pomiar_mapa(0, 0);
  for (int i = 0; i < ile_pomiarow; i++) {
    if (po_lewej) {
      while (ile_lewo > -maks_obrot) {
        for (int j = 0; j < ruch2; j++) {
          if (ile_lewo > -maks_obrot) {
            prawo_o_krok();
            ile_lewo = (ile_lewo - 1) % 200;
          }
        }
        y++;
        delay(1000);
        pomiar_mapa(i, y);
      }
      po_lewej = false;
    }
    else {
      while (ile_lewo < maks_obrot) {
        for (int j = 0; j < ruch2; j++) {
          if (ile_lewo < maks_obrot) {
            lewo_o_krok();
            ile_lewo = (ile_lewo + 1) % 200;
          }
        }
        y--;
        delay(1000);
        pomiar_mapa(i, y);
      }
      po_lewej = true;
    }


    for (int j = 0; j < ruch2; j++) {
      if (ile_gora > -maks_obrot) {
        dol_o_krok();
        ile_gora = (ile_gora - 1) % 200;
      }
    }
  }
  najlepszy_pomiar_w_mapie();
  ustaw_na_najlepsza();
}
