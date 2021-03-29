// constants won't change. Used here to 
 // set pin numbers:
const int stepPin = 2;      // the number of the step pin
const int dirPin = 3;         // the number of the direction pin
const int stepPin2 = 8;
const int dirPin2 = 9;
const int ledPin = 13;      // the number of the LED pin
const int czujnikPin = 0;
const int liczba_pomiarow = 30;
const int maks_obrot=50;

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int directionState = LOW;               // default direction is ....
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 200;           // interval at which to blink (milliseconds)
int timesOneDirection = 0;
int tryb_pracy;
int ile_lewo = 0;
int ile_gora = 0;
int najlepsza_pozycja_lewo = 0;
int najlepsza_pozycja_gora = 0;
int najlepsza_wartosc = 0;
int ruch = 30;

void setup() {
    // set the digital pin as output:
    pinMode(ledPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(dirPin2, OUTPUT);
    digitalWrite(stepPin2, LOW);
    digitalWrite(dirPin2, LOW);
    wyswietl_panel_startowy1();
}

void loop()
{
    // here is where you'd put code that needs to be running all the time.

    // check to see if it's time to blink the LED; that is, if the 
    // difference between the current time and last time you blinked 
    // the LED is bigger than the interval at which you want to 
    // blink the LED.

    String odczytano;
    
    if (tryb_pracy == 2) {//manualny
        if (Serial.available() > 0) {
            odczytano = Serial.readStringUntil('\n');
            int odczyt = odczytano[0];
            switch (odczyt) {
            case 68://D
                prawo_o_krok();
                ile_lewo=(ile_lewo-1)%200;
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
            case 88://X
                ustaw_na_pocztek();
                delay(1000);
                exit(0);
                break;
            default:
                Serial.println("Zly wybor, wybierz jeszcze raz");
            }
        }
    }
    else {//automatyczny

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
              case 88://X
              ustaw_na_pocztek();
              delay(10);
              exit(0);
              break;
              default:
              Serial.println("Zly wybor, wybierz jeszcze raz");
            }
            
        }
        
    }
    //swiecenie diody
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
        // save the last time you blinked the LED 
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW)
            ledState = HIGH;
        else
            ledState = LOW;
        // set the LED with the ledState of the variable:
        digitalWrite(ledPin, ledState);
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


void wyswietl_panel_startowy2() {
    Serial.println("Co chcesz zrobic?");
    Serial.println("1. [A] Przesun w lewo o krok");
    Serial.println("2. [D] Przesun w prawo o krok");
    Serial.println("3. [W] Przesun w gore o krok");
    Serial.println("4. [S] Przesun w dol o krok");
    Serial.println("5. [P] Dokonaj pomiaru");
    Serial.println("6. [B] Ustaw na najlepsza pozycje (z tych zmierzonych)");
    Serial.println("7. [M] Ustaw na pozycje poczatkowa");
    Serial.println("8. [X] Zakoncz");
    Serial.println("Podaj znak wybranej opcji: ");
}

void wyswietl_panel_startowy3() {
    Serial.println("Co chcesz zrobic?");
    Serial.println("1. [S] Sprawdzaj automatycznie");
    Serial.println("2. [C] Zwieksz precyzje");
    Serial.println("3. [M] Ustaw na pozycje poczatkowa");
    Serial.println("4. [X] Zakoncz");
    Serial.println("Podaj znak wybranej opcji: ");
}
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
