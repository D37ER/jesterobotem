void wyswietl_panel_startowy3() {
    Serial.println("Co chcesz zrobic?");
    Serial.println("1. [S] Sprawdzaj automatycznie");
    Serial.println("2. [C] Zwieksz precyzje");
    Serial.println("3. [M] Ustaw na pozycje poczatkowa");
    Serial.println("4. [Y] Zmien tryb");
    Serial.println("5. [X] Zakoncz");
    Serial.println("Podaj znak wybranej opcji: ");
}

void aglorithm1(String odczytano){
        if (Serial.available() > 0) {
            odczytano = Serial.readStringUntil('\n');
            int odczyt = odczytano[0];
            switch(odczyt){
              case 83://S-start
              przesuwaj();
              ustaw_na_najlepsza();
              break;
              case 67://C-kontynuuj precyzje
              ruch=ruch/2;
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

void przesuwaj() {
    //-------------------------------------------
    for (int i = 0; i < ruch; i++) {
        if(ile_lewo<maks_obrot){
           lewo_o_krok();
           ile_lewo=(ile_lewo+1)%200;
        }
    }//0L->1L 0G
    for (int i = 0; i < ruch; i++) {
        if(ile_gora<maks_obrot){
           gora_o_krok();
           ile_gora=(ile_gora+1)%200;
        }
    }//1L 0G->1G
    delay(1000);
    pomiar();//1L 1G
    for (int i = 0; i < ruch; i++) {
        if(ile_gora>-maks_obrot){
           dol_o_krok();
           ile_gora=(ile_gora-1)%200;
        }
    }//1L 1G->0G
    delay(1000);
    pomiar();//1L 0G
    for (int i = 0; i < ruch; i++) {
        if(ile_gora>-maks_obrot){
           dol_o_krok();
           ile_gora=(ile_gora-1)%200;
        }
    }//1L 0G->-1G
    delay(1000);
    pomiar();//1L -1G
    //-------------------------------------------
    for (int i = 0; i < ruch; i++) {
        if(ile_lewo>-maks_obrot){
           prawo_o_krok();
           ile_lewo=(ile_lewo-1)%200;
        }
    }//1L->0L -1G
    delay(1000);
    pomiar();//0L -1G
    for (int i = 0; i < ruch; i++) {
        if(ile_gora<maks_obrot){
           gora_o_krok();
           ile_gora=(ile_gora+1)%200;
        }
    }//0L -1G->0G
    delay(1000);
    pomiar();//0L 0G
    for (int i = 0; i < ruch; i++) {
        if(ile_gora<maks_obrot){
           gora_o_krok();
           ile_gora=(ile_gora+1)%200;
        }
    }//0L 0G->1G
    delay(1000);
    pomiar();//0L 1G
    //-------------------------------------------
    for (int i = 0; i < ruch; i++) {
        if(ile_lewo>-maks_obrot){
           prawo_o_krok();
           ile_lewo=(ile_lewo-1)%200;
        }
    }//0L->-1L 1G
    delay(1000);
    pomiar();//-1L 1G
    for (int i = 0; i < ruch; i++) {
        if(ile_gora>-maks_obrot){
           dol_o_krok();
           ile_gora=(ile_gora-1)%200;
        }
    }//-1L 1G->0G
    delay(1000);
    pomiar();//-1L 0G
    for (int i = 0; i < ruch; i++) {
        if(ile_gora>-maks_obrot){
           dol_o_krok();
           ile_gora=(ile_gora-1)%200;
        }
    }//-1L 0G->-1G
    delay(1000);
    pomiar();//-1L -1G
    //-------------------------------------------
}
