// constants won't change. Used here to
// set pin numbers:
const int stepPin = 2;      // the number of the step pin
const int dirPin = 3;         // the number of the direction pin
const int stepPin2 = 8;
const int dirPin2 = 9;
const int ledPin = 13;      // the number of the LED pin
const int czujnikPin = 0;
const int liczba_pomiarow = 30;
const int maks_obrot = 50; //bezpieczne
const int16_t ile_pomiarow = 10;

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int directionState = LOW;               // default direction is ....
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 200;           // interval at which to blink (milliseconds)
int16_t timesOneDirection = 0;
int16_t tryb_pracy;
int16_t ile_lewo = 0;
int16_t ile_gora = 0;
int16_t najlepsza_pozycja_lewo = 0;
int16_t najlepsza_pozycja_gora = 0;
int16_t najlepsza_wartosc = 0;
int16_t ruch = 30;
int16_t ruch2 = 2 * maks_obrot / ile_pomiarow;
int16_t pomiary[ile_pomiarow][ile_pomiarow];


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

  if (tryb_pracy == 1) {//automatyczny Marty
    aglorithm1(odczytano);
  }
  else if (tryb_pracy == 1) { //manualny
    manual(odczytano);
  }
  else if (tryb_pracy == 3) {
    brute_force(odczytano);
  }
  else if (tryb_pracy == 4) {
    binary(odczytano);
  }
  else if (tryb_pracy == 5) {
    greedy(odczytano);
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
