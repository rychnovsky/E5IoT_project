int counter = 0;

void setup() {
    setupDisplay();
}

void loop() {
    showNumber(counter);
    counter++;
    delay(1000);
    if(counter == 105) {
      counter = 0;
    }
}

// DISPLAY FUNCTIONS

/**
* Setup display pins
*/
void setupDisplay() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

/**
* Show number on the display
* If the number has more digits than display, show error
* @param int number - Number to be shown
*/
void showNumber(int number) {
    resetDisplay();
    if(number >= 0 && number < 100) {
        int first = number % 10;
        int second = number / 10;
        firstDigit(first);
        secondDigit(second);
    } else {
       showError();
    }
}

/**
* Show minus minus
*/
void showError() {
    resetDisplay();
    digitalWrite(D7,HIGH);
    digitalWrite(D3,HIGH);
}

/**
* Switch off display
*/
void resetDisplay(){
    digitalWrite(A0,LOW);
    digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
    digitalWrite(D0,LOW);
    digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(A3,LOW);
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
}

/**
* Mapping of integer to first segment display
*/
void firstDigit(int number) {
    switch(number) {
        case 0:
          digitalWrite(A5,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(D2,HIGH);
          digitalWrite(D1,HIGH);
          digitalWrite(D0,HIGH);
          break;
        case 1:
          digitalWrite(A3,HIGH);
          digitalWrite(D2,HIGH);
          break;
        case 2:
          digitalWrite(D3,HIGH);
          digitalWrite(D1,HIGH);
          digitalWrite(D2,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A5,HIGH);
          break;
        case 3:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(D1,HIGH);
          digitalWrite(D2,HIGH);
          digitalWrite(A4,HIGH);
          break;
        case 4:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(D2,HIGH);
          digitalWrite(D0,HIGH);
          break;
        case 5:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(D1,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(D0,HIGH);
          break;
        case 6:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(D1,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(D0,HIGH);
          digitalWrite(A5,HIGH);
          break;
        case 7:
          digitalWrite(A3,HIGH);
          digitalWrite(D2,HIGH);
          digitalWrite(D1,HIGH);
          break;
        case 8:
          digitalWrite(D3,HIGH);
          digitalWrite(D0,HIGH);
          digitalWrite(D1,HIGH);
          digitalWrite(D2,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A5,HIGH);
          break;
        case 9:
          digitalWrite(D3,HIGH);
          digitalWrite(D0,HIGH);
          digitalWrite(D1,HIGH);
          digitalWrite(D2,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A4,HIGH);
          break;
    }
}

/**
* Mapping of integer to second segment display
*/
void secondDigit(int number) {
    switch(number) {
        case 0:
            digitalWrite(A0,HIGH);
            digitalWrite(A1,HIGH);
            digitalWrite(A2,HIGH);
            digitalWrite(D4,HIGH);
            digitalWrite(D5,HIGH);
            digitalWrite(D6,HIGH);
            break;
        case 1:
            digitalWrite(A2,HIGH);
            digitalWrite(D4,HIGH);
            break;
        case 2:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(A1,HIGH);//D
            digitalWrite(A0,HIGH);//E
            break;
        case 3:
            digitalWrite(D7,HIGH);//G
            digitalWrite(A2,HIGH);//C
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(A1,HIGH);//D
            break;
        case 4:
            digitalWrite(D7,HIGH);//G
            digitalWrite(A2,HIGH);//C
            digitalWrite(D4,HIGH);//B
            digitalWrite(D6,HIGH);//F
            break;
        case 5:
            digitalWrite(D7,HIGH);//G
            digitalWrite(A2,HIGH);//C
            digitalWrite(D5,HIGH);//A
            digitalWrite(A1,HIGH);//D
            digitalWrite(D6,HIGH);//F
            break;
        case 6:
            digitalWrite(D7,HIGH);//G
            digitalWrite(A2,HIGH);//C
            digitalWrite(D5,HIGH);//A
            digitalWrite(A1,HIGH);//D
            digitalWrite(D6,HIGH);//F
            digitalWrite(A0,HIGH);//E
            break;
        case 7:
            digitalWrite(A2,HIGH);//C
            digitalWrite(D4,HIGH);//B
            digitalWrite(D5,HIGH);//A
            break;
        case 8:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D6,HIGH);//F
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(A2,HIGH);//C
            digitalWrite(A1,HIGH);//D
            digitalWrite(A0,HIGH);//E
            break;
        case 9:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D6,HIGH);//F
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(A2,HIGH);//C
            digitalWrite(A1,HIGH);//D
            break;
    }
}
