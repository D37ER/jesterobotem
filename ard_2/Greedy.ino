void wyswietl_panel_startowy6() {
  Serial.println("Co chcesz zrobic?");
  Serial.println("1. [S] Sprawdzaj sposobem zachlannym w wersji podstawowej.");
  Serial.println("2. [D] Sprawdzaj sposobem zachlannym w wersji zaawanspwanej.");
  Serial.println("3. [M] Ustaw na pozycje poczatkowa.");
  Serial.println("4. [Z] Zapomnij o najlepszym pomiarze.");
  Serial.println("5. [Y] Zmien tryb.");
  Serial.println("6. [X] Zakoncz.");
  Serial.println("Podaj znak wybranej opcji: ");
}

void greedy(String odczytano) {
  if (Serial.available() > 0) {
    odczytano = Serial.readStringUntil('\n');
    int16_t odczyt = odczytano[0];
    switch (odczyt) {
      case 83://S-start
        pomiar_greedy_podstawowy();
        break;
      case 68://D
        pomiar_greedy_zaawansowany();
        break;
      case 77://M
        ustaw_na_pocztek();
        break;
      case 89://Y
        wyswietl_panel_startowy1();
        break;
      case 90://Z
        zapomnij_najlepszy_pomiar();
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

void pomiar_greedy_podstawowy() {
  int16_t naj_pomiar, ilosc_krokow = 20; //do zapamietywania poprzedniej najlepszej wartosci
  const int8_t prog_zmiany_wartosci = 5;
  delay(1000);
  pomiar();
  naj_pomiar = 0;
  while (true) {
    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_lewo < maks_obrot_poziom) {
        lewo_o_krok();
        ile_lewo = (ile_lewo + 1) % 200;

      }
    }
    delay(1000);
    pomiar();

    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_gora < maks_obrot_pion) {
        gora_o_krok();
        ile_gora = (ile_gora + 1) % 200;
      }
    }
    delay(1000);
    pomiar();

    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_lewo > -maks_obrot_poziom) {
        prawo_o_krok();
        ile_lewo = (ile_lewo - 1) % 200;
      }
    }
    delay(1000);
    pomiar();

    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_lewo > -maks_obrot_poziom) {
        prawo_o_krok();
        ile_lewo = (ile_lewo - 1) % 200;
      }
    }
    delay(1000);
    pomiar();
    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_gora > -maks_obrot_pion) {
        dol_o_krok();
        ile_gora = (ile_gora - 1) % 200;
      }
    }
    delay(1000);
    pomiar();
    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_gora > -maks_obrot_pion) {
        dol_o_krok();
        ile_gora = (ile_gora - 1) % 200;
      }
    }
    delay(1000);
    pomiar();

    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_lewo < maks_obrot_poziom) {
        lewo_o_krok();
        ile_lewo = (ile_lewo + 1) % 200;
      }
    }
    delay(1000);
    pomiar();

    for (int i = 0; i < ilosc_krokow; i++) {
      if (ile_lewo < maks_obrot_poziom) {
        lewo_o_krok();
        ile_lewo = (ile_lewo + 1) % 200;
      }
    }
    delay(1000);
    pomiar();

    if (naj_pomiar >= najlepsza_wartosc - prog_zmiany_wartosci) {
      break;
    } else {
      ustaw_na_najlepsza();
      naj_pomiar = najlepsza_wartosc;
      ilosc_krokow = ilosc_krokow / 2;
    }
  }

}
void pomiar_greedy_zaawansowany() {
  int16_t naj_pomiar, x, y, w, ilosc_krokow = 20;
  const int8_t prog_zmiany_wartosci = 5;
  delay(1000);
  pomiar();
  szukaj_wokol(ilosc_krokow);

  while (true) {
    x = ile_lewo;
    y = ile_gora;
    naj_pomiar = najlepsza_wartosc;
    ustaw_na_najlepsza();

    if (ile_lewo > x && ile_gora == y) {
      while (true) {
        if (ile_lewo < maks_obrot_poziom) {
          lewo_o_krok();
          ile_lewo = (ile_lewo + 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    else if (ile_lewo > x && ile_gora > y) {
      while (true) {
        if (ile_lewo < maks_obrot_poziom) {
          lewo_o_krok();
          ile_lewo = (ile_lewo + 1) % 200;
        }
        if (ile_gora < maks_obrot_pion) {
          gora_o_krok();
          ile_gora = (ile_gora + 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    else if (ile_lewo == x && ile_gora > y) {
      while (true) {
        if (ile_gora < maks_obrot_pion) {
          gora_o_krok();
          ile_gora = (ile_gora + 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    else if (ile_lewo < x && ile_gora > y) {
      while (true) {
        if (ile_lewo > -maks_obrot_poziom) {
          prawo_o_krok();
          ile_lewo = (ile_lewo - 1) % 200;
        }
        if (ile_gora < maks_obrot_pion) {
          gora_o_krok();
          ile_gora = (ile_gora + 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    else if (ile_lewo < x && ile_gora == y) {
      while (true) {
        if (ile_lewo > -maks_obrot_poziom) {
          prawo_o_krok();
          ile_lewo = (ile_lewo - 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    else if (ile_lewo < x && ile_gora < y) {
      while (true) {
        if (ile_lewo > -maks_obrot_poziom) {
          prawo_o_krok();
          ile_lewo = (ile_lewo - 1) % 200;
        }
        if (ile_gora > -maks_obrot_pion) {
          dol_o_krok();
          ile_gora = (ile_gora - 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    else if (ile_lewo == x && ile_gora < y) {
      while (true) {
        if (ile_gora > -maks_obrot_pion) {
          dol_o_krok();
          ile_gora = (ile_gora - 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    else  if (ile_lewo > x && ile_gora < y) {
      while (true) {
        if (ile_lewo < maks_obrot_poziom) {
          lewo_o_krok();
          ile_lewo = (ile_lewo + 1) % 200;
        }
        if (ile_gora > -maks_obrot_pion) {
          dol_o_krok();
          ile_gora = (ile_gora - 1) % 200;
        }
        delay(1000);
        w = pomiar_z_wartoscia();
        if (w < najlepsza_wartosc) {
          break;
        }
      }
    }
    szukaj_wokol(ilosc_krokow);
    if (naj_pomiar >= najlepsza_wartosc - prog_zmiany_wartosci) {
      break;
    }
    ilosc_krokow = ilosc_krokow / 2;
  }
}

void szukaj_wokol(int ilosc_krokow) {
  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_lewo < maks_obrot_poziom) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_gora < maks_obrot_pion) {
      gora_o_krok();
      ile_gora = (ile_gora + 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_lewo > -maks_obrot_poziom) {
      prawo_o_krok();
      ile_lewo = (ile_lewo - 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_lewo > -maks_obrot_poziom) {
      prawo_o_krok();
      ile_lewo = (ile_lewo - 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_gora > -maks_obrot_pion) {
      dol_o_krok();
      ile_gora = (ile_gora - 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_gora > -maks_obrot_pion) {
      dol_o_krok();
      ile_gora = (ile_gora - 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_lewo < maks_obrot_poziom) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_lewo < maks_obrot_poziom) {
      lewo_o_krok();
      ile_lewo = (ile_lewo + 1) % 200;
    }
  }
  delay(1000);
  pomiar();

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_lewo > -maks_obrot_poziom) {
      prawo_o_krok();
      ile_lewo = (ile_lewo - 1) % 200;
    }
  }

  for (int i = 0; i < ilosc_krokow; i++) {
    if (ile_gora < maks_obrot_pion) {
      gora_o_krok();
      ile_gora = (ile_gora + 1) % 200;
    }
  }
}
