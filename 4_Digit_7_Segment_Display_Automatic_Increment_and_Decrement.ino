/*************************************************************************************
How the program works: There are 3 buttons: Increment, Decrement, and Pause/reset.
Pressing the increment button begins an auto incrementation with a delay. Pressing
the decrement button turns off auto incrementation and begins an auto decrementation.
Pressing the pause/reset button pauses the auto incrementation/decrementation.
Holding the pause/reset button for a set amount of time completely resets the counter.
*************************************************************************************/

int aPin = 2;
int bPin = 3;
int cPin = 4;
int dPin = 5;
int ePin = 6;
int fPin = 7;
int gPin = 8;
int c1Pin = 9;
int c2Pin = 10;
int c3Pin = 11;
int c4Pin = 12;
int bt_up = A0;
int bt_down = A1;
int bt_reset = A2;
int buzzer = 13;
int Counter = 0;

unsigned long bt_reset_pressed = 0;  // Doesn't HAVE to be a long, but because it stores time, it can hold a huge number of POSITIVE INTEGERS (about 50 days worth of time)
unsigned long bt_up_pressed = 0;
unsigned long bt_down_pressed = 0;
bool isIncrementing = false;
bool isDecrementing = false;

int IncDecConst = 250;  // Number of milliseconds between increment/decrement. Default is 0.5 seconds
int holdConst = 1000;   // Number of milliseconds to hold increment/decrement buttons to begin auto increment/decrement. Default is 1 second
int resetConst = 3000;  // Number of milliseconds to hold reset button to actually reset. Default is 2 seconds

void setup() {
  pinMode(bt_up, INPUT_PULLUP);
  pinMode(bt_down, INPUT_PULLUP);
  pinMode(bt_reset, INPUT_PULLUP);

  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(fPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(c1Pin, OUTPUT);
  pinMode(c2Pin, OUTPUT);
  pinMode(c3Pin, OUTPUT);
  pinMode(c4Pin, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(c1Pin, LOW);  // Turns all digits on
  digitalWrite(c2Pin, LOW);
  digitalWrite(c3Pin, LOW);
  digitalWrite(c4Pin, LOW);
}

void loop() {
  if (digitalRead(bt_up) == LOW) {  // if incremnt button is pressed
    digitalWrite(buzzer, HIGH);  // buzzer makes sound
    // Add some delay between when button is pressed and we switch to increment
    if((millis() - bt_up_pressed) < holdConst) {
      Counter++;
      delay(20);
      isDecrementing = false;
      if(Counter > 9999) {        // if counter is too big, wrap to zero
        Counter = 0;
      }
    }
    else {
      isIncrementing = true;
      isDecrementing = false;
    }
    bt_up_pressed = millis();
  }

  if(digitalRead(bt_down) == LOW) {  // if decrement button is pressed
    digitalWrite(buzzer, HIGH);
    // Add some delay between when button is pressed and we switch to decrement
    if((millis() - bt_down_pressed) < holdConst) {
      Counter--;
      delay(20);
      isIncrementing = false;
      if(Counter < 0) {  // Wrap to 9999 if counter is too small
        Counter = 9999;
      }
    }
    else {
      isIncrementing = false;
      isDecrementing = true;
    }
    bt_down_pressed = millis();    
  }

  if(digitalRead(bt_reset) == LOW) {                // When reset button is pressed
    digitalWrite(buzzer, HIGH);                      // Buzzer makes sound
    // Add some delay between when button is pressed and we switch to decrement
    if((millis() - bt_reset_pressed) > resetConst) {  // If reset button is held for more than 2 seconds. Is checked by millis() function
      Counter = 0;
    }  // Note: millis() counts the total number of milliseconds, and due to code later, another variable, bt_reset_pressed, gets set to it
    else {
      isIncrementing = false;  // Pause incrementing
      isDecrementing = false;  // Pause decrementing
    }
  }

  if(isIncrementing && ((millis() - bt_up_pressed) > IncDecConst)) {  // If incrementing and [IncDecConst] milleseconds has passed
    Counter++;
    if(Counter > 9999) {
      Counter = 0;  // Wrap around to 0 if counter exceeds 9999
    }
    bt_up_pressed = millis();  // Update the time of last button press
  }

  if(isDecrementing && ((millis() - bt_down_pressed) > IncDecConst)) {  // If decrementing and [IncDecConst] milliseconds has passed
    Counter--;
    if(Counter < 0) {  // Wraps counter around to 9999
      Counter = 9999;
    }
    bt_down_pressed = millis();  // Update the time of last button press
  }

  showNumber((Counter / 1000) % 10);  // Thousands digit
  digitalWrite(c1Pin, LOW);
  delay(4);  // Multiplex by quickly switching digit from on at certain number, determined by showNumber(int num)
  digitalWrite(c1Pin, HIGH);

  showNumber((Counter / 100) % 10);  // Hundreds digit
  digitalWrite(c2Pin, LOW);
  delay(4);  // Creates illusion of numbers not blinking and appearing on
  digitalWrite(c2Pin, HIGH);

  showNumber((Counter / 10) % 10);  // Tens digit
  digitalWrite(c3Pin, LOW);
  delay(4);  // Smaller numbers have faster update time, but ruin the buzzer sound
  digitalWrite(c3Pin, HIGH);

  showNumber(Counter % 10);  // Ones digit
  digitalWrite(c4Pin, LOW);
  delay(4);  // 4 milliseconds is optimal for maximum buzzer volume and multiplexing
  digitalWrite(c4Pin, HIGH);

  digitalWrite(buzzer, LOW);  // Turns buzzer off in case if it was switched on and never turned off earlier
}


void showNumber(int x) {  // Switch that calls any of the number methods based off an integer x
  switch (x) {
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
    default:
      zero();
      break;
  }
}

void one() {
  digitalWrite(aPin, LOW);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, LOW);
  digitalWrite(ePin, LOW);
  digitalWrite(fPin, LOW);
  digitalWrite(gPin, LOW);
}

void two() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, LOW);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(fPin, LOW);
  digitalWrite(gPin, HIGH);
}

void three() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, LOW);
  digitalWrite(fPin, LOW);
  digitalWrite(gPin, HIGH);
}

void four() {
  digitalWrite(aPin, LOW);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, LOW);
  digitalWrite(ePin, LOW);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
}

void five() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, LOW);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, LOW);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
}

void six() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, LOW);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
}

void seven() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, LOW);
  digitalWrite(ePin, LOW);
  digitalWrite(fPin, LOW);
  digitalWrite(gPin, LOW);
}

void eight() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
}

void nine() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, LOW);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
}

void zero() {
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, LOW);
}