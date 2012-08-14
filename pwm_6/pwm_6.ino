/*
  PWM6 - play with six PWM leds.
  Zellyn Hunter - 2012.
  Public domain.
 */

// Pins
byte pins[] = {3, 5, 6, 9, 10, 11};
int NUM_PINS = (sizeof pins) / (sizeof pins[0]);

void setup() {
  for (int i=0; i < NUM_PINS; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void countBinary() {
  for (int i=0; i<64; i++) {
    int pos = 1;
    for (int j=0; j<NUM_PINS; j++) {
      analogWrite(pins[j], ((i & pos) > 0) * 64);
      pos *= 2;
    }
    delay(1000);
  }
}

int dir = -1;
int pos = 1;
const int FACTOR = 10;

void sweeper() {
  pos += dir;
  if (pos==0 || pos==((NUM_PINS-1)*FACTOR)) {
    dir *= -1;
  }
  for (int j = 0; j<NUM_PINS; j++) {
    int raw_dist = j*FACTOR - pos;
    int dist = abs(raw_dist);
    int raw_value = max(0, FACTOR-dist);
    int value = map(raw_value, 0, FACTOR, 0, 255);
    analogWrite(pins[j], value);
  }
}

void loop() {
  sweeper();
  delay(30);
}
