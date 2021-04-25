void wyswietl_panel_startowy4() {
  Serial.println("Co chcesz zrobic?");
  Serial.println("1. [N] Tryb zapamietywania tylko najlepszego polozenia.");
  Serial.println("2. [W] Tryb zapamietywania wszystkich polozen.");
  Serial.println("3. [M] Ustaw na pozycje poczatkowa.");
  Serial.println("4. [Z] Zapomnij o najlepszym pomiarze.");
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
      case 77://M-pozycja pocz
        ustaw_na_pocztek();
        break;
      case 90://Z
        zapomnij_najlepszy_pomiar();
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
  for (int i = 0; i < maks_obrot_poziom; i++) {
    if (ile_lewo < maks_obrot_poziom) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
  }//0L->1L 0G
  bool po_lewej = true;
  for (int i = 0; i < maks_obrot_pion; i++) {
    if (ile_gora < maks_obrot_pion) {
      gora_o_krok();
      ile_gora = (ile_gora + 1) % 200;
    }
  }//1L 0G->1G
  delay(1000);
  pomiar();
  for (int i = 0; i < ile_pomiarow; i++) {
    if (po_lewej) {
      while (ile_lewo > -maks_obrot_poziom) {
        for (int j = 0; j < ruch2_poziom; j++) {
          if (ile_lewo > -maks_obrot_poziom) {
            prawo_o_krok();
            ile_lewo = (ile_lewo - 1) % 200;
          }
        }
        delay(1000);
        pomiar();
      }
      po_lewej = false;
    }
    else {
      while (ile_lewo < maks_obrot_poziom) {
        for (int j = 0; j < ruch2_poziom; j++) {
          if (ile_lewo < maks_obrot_poziom) {
            lewo_o_krok();
            ile_lewo = (ile_lewo + 1) % 200;
          }
        }
        delay(1000);
        pomiar();
      }
      po_lewej = true;
    }
    if (ile_gora > -maks_obrot_pion) {
      for (int j = 0; j < ruch2_pion; j++) {
        if (ile_gora > -maks_obrot_pion) {
          dol_o_krok();
          ile_gora = (ile_gora - 1) % 200;
        }
      }
      delay(1000);
      pomiar();
    }
  }
  ustaw_na_najlepsza();
}

void wszystkie_pomiary_BF() {
  Serial.println("Rozpoczynam robienie oraz zapis pomiarow");
  int y = 0;
  for (int i = 0; i < maks_obrot_poziom; i++) {
    if (ile_lewo < maks_obrot_poziom) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
  }//0L->1L 0G
  bool po_lewej = true;
  for (int i = 0; i < maks_obrot_pion; i++) {
    if (ile_gora < maks_obrot_pion) {
      gora_o_krok();
      ile_gora = (ile_gora + 1) % 200;
    }
  }//1L 0G->1G
  delay(1000);
  pomiar_mapa(0, 0);
  for (int i = 0; i < ile_pomiarow; i++) {
    if (po_lewej) {
      while (ile_lewo > -maks_obrot_poziom) {
        for (int j = 0; j < ruch2_poziom; j++) {
          if (ile_lewo > -maks_obrot_poziom) {
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
      while (ile_lewo < maks_obrot_poziom) {
        for (int j = 0; j < ruch2_poziom; j++) {
          if (ile_lewo < maks_obrot_poziom) {
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

    if (ile_gora > -maks_obrot_pion) {
      for (int j = 0; j < ruch2_pion; j++) {
        if (ile_gora > -maks_obrot_pion) {
          dol_o_krok();
          ile_gora = (ile_gora - 1) % 200;
        }
      }
      delay(1000);
      pomiar_mapa(i + 1, y);
    }
  }
  Serial.println("Wyswietlanie mapy.");
  wyswietl_mape();
  najlepszy_pomiar_w_mapie();
  ustaw_na_najlepsza();
}
