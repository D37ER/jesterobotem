 // constants won't change. Used here to 
 // set pin numbers:
const int stepPin = 2;      // the number of the step pin
const int dirPin = 3;         // the number of the direction pin
const int stepPin2 = 8;
const int dirPin2 = 9;
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int directionState = LOW;               // default direction is ....
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 200;           // interval at which to blink (milliseconds)
int timesOneDirection = 0;

void setup() {
    // set the digital pin as output:
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(dirPin2, OUTPUT);
    digitalWrite(stepPin2, LOW);
    digitalWrite(dirPin2, LOW);
    wyswietl_panel_startowy();
}

void loop()
{
    // here is where you'd put code that needs to be running all the time.

    // check to see if it's time to blink the LED; that is, if the 
    // difference between the current time and last time you blinked 
    // the LED is bigger than the interval at which you want to 
    // blink the LED.
    
    String odczytano;
    
    if(Serial.available()>0){
          odczytano = Serial.readStringUntil('\n');
          int odczyt=odczytano[0];
          switch (odczyt) {
          case 68://D
              prawo_o_krok();
              break;
          case 65://A
              lewo_o_krok();
              break;
          case 87://W
              gora_o_krok();
              break;
          case 83://S
              dol_o_krok();
              break;
          case 80://P
              pomiar();
              break;
          case 66://B
              Serial.println("Opcja w wykonaniu");
              //ustaw_na_najlepsza();
              break;
          case 88://X
              delay(1000);
              exit(0);
              break;
          default:
              Serial.println("Zly wybor, wybierz jeszcze raz");
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
void pomiar() {
    int wartosc_z_czujnika;
    //gdzie jest podpiety czujnik (ADC)
    wartosc_z_czujnika = analogRead(7);
    Serial.println(wartosc_z_czujnika);
    //powinny byc wartosci 0-1023
    delay(100);
}

void wyswietl_panel_startowy() {
    Serial.println("Zaczynamy zabawe!");
    Serial.println("Co chcesz zrobic?");
    Serial.println("1. [A] Przesun w lewo o krok");
    Serial.println("2. [D] Przesun w prawo o krok");
    Serial.println("3. [W] Przesun w gore o krok");
    Serial.println("4. [S] Przesun w dol o krok");
    Serial.println("5. [P] Dokonaj pomiaru");
    Serial.println("6. [B] Ustaw na najlepsza pozycje (z tych zmierzonych)");
    Serial.println("7. [X] Zakoncz");
    Serial.println("Podaj znak wybranej opcji: ");
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
