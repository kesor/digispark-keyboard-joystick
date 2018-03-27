#include <DigiKeyboard.h>

#define TOLERANCE 10
#define MAX_Y 1023
#define MID_Y 557
#define MIN_Y 16
#define MAX_X 1023
#define MID_X 540
#define MIN_X 16
#define PIN_S_D 0
#define PIN_X_A 0
#define PIN_X_D 5 // NOTE: cheap Chinese DigiSpark clones lack the RSTDSBL fuse bit, and P5 is the reset pin (active low: gnd == reset)
#define PIN_Y_A 1
#define PIN_Y_D 2

unsigned int yy = MID_Y;
unsigned int xx = MID_X;
unsigned int sw = 1;

void setup() {
  pinMode(PIN_S_D, INPUT_PULLUP); // switch
  pinMode(PIN_Y_D, INPUT_PULLUP); // y axis
  pinMode(PIN_X_D, INPUT_PULLUP); // x axis
}

void readYY() {
  yy = analogRead(PIN_Y_A); // read P2 potentiometer
}

void readXX() {
  xx = analogRead(PIN_X_A); // read P4 potentiometer
}

void readSW() {
  sw = digitalRead(PIN_S_D); // read P0 switch
}

void printYY() {
  DigiKeyboard.print("Y: ");
  DigiKeyboard.println(yy);
}

void printXX() {
  DigiKeyboard.print("X: ");
  DigiKeyboard.println(xx);
}

void printSW() {
  DigiKeyboard.println("Clicky click!");
  readXX();
  printXX();
  readYY();
  printYY();
}

void loop() {
  readSW();
  if (!sw) {
    printSW();
  }

  readYY();
  if ((yy > MID_Y + TOLERANCE || yy < MID_Y - TOLERANCE) && yy != MID_Y) {
    printYY();
  }
  readXX();
  if ((xx > MID_X + TOLERANCE || xx < MID_X - TOLERANCE) && xx != MID_X) {
    printXX();
  }
  DigiKeyboard.update();
}


