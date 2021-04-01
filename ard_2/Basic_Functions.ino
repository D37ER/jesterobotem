void wyswietl_panel_startowy1() {
    Serial.begin(9600);
    Serial.println("Zaczynamy zabawe!");
    Serial.println("Wybierz tryb dzialania");
    Serial.println("1. Tryb automatyczny");
    Serial.println("2. Tryb manualny");
    Serial.println("Podaj numer wybranej opcji: ");

    String odczytano1;
    int odczyt1=0;
    while (odczyt1!=2 && odczyt1!=1) {
          odczytano1 = Serial.readStringUntil('\n');
          int odczyt1 = odczytano1[0]-48;
          if(odczyt1==2){
            Serial.println("Wybrano tryb manualny");
            tryb_pracy=2;
            wyswietl_panel_startowy2();
            break;
          }
          if(odczyt1==1){
            Serial.println("Wybrano tryb automatyczny");
            tryb_pracy = 1;
            wyswietl_panel_startowy3();
            break;
          }
          delay(100);
      }
    
}

void ustaw_na_najlepsza() {
    while (najlepsza_pozycja_lewo > ile_lewo) {
        lewo_o_krok();
        ile_lewo=(ile_lewo+1)%200;
    }
    Serial.println("Ustawiono lewo");
    while (najlepsza_pozycja_lewo < ile_lewo) {
        prawo_o_krok();
        ile_lewo=(ile_lewo-1)%200;
    }
    Serial.println("Ustawiono prawo");
    while (najlepsza_pozycja_gora > ile_gora) {
        gora_o_krok();
        ile_gora=(ile_gora+1)%200;
    }
    Serial.println("Ustawiono gora");
    while (najlepsza_pozycja_gora < ile_gora) {
        dol_o_krok();
        ile_gora=(ile_gora-1)%200;
    }
    Serial.println("Ustawiono dol");

}

void ustaw_na_pocztek() {
    while (ile_lewo < 0) {
        lewo_o_krok();
        ile_lewo=(ile_lewo+1)%200;
    }
    Serial.println("Ustawiono lewo");
    while (ile_lewo > 0) {
        prawo_o_krok();
        ile_lewo=(ile_lewo-1)%200;
    }
    Serial.println("Ustawiono prawo");
    while (ile_gora< 0) {
        gora_o_krok();
        ile_gora=(ile_gora+1)%200;
    }
    Serial.println("Ustawiono gora");
    while (ile_gora > 0) {
        dol_o_krok();
        ile_gora=(ile_gora-1)%200;
    }
    Serial.println("Ustawiono dol");

}
void pomiar() {
    int wartosc_z_czujnika = 0;
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
