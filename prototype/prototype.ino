#define FWD 9
#define BCK 10
#define PB 4
#define SW 3
#define pm pinMode
#define aw analogWrite
#define dr digitalRead

int spd;
bool pressed;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pm(FWD, OUTPUT);
  pm(BCK, OUTPUT);
  pm(PB, INPUT/*_PULLUP*/);
  // pm(SW, INPUT);
  spd = 0;
  pressed = false;
}

void rdButton() {
  //Serial.print(spd);
  //Serial.print(" ");
  //Serial.print(!dr(PB));
  //Serial.print(" ");
  //Serial.println(pressed);
  if (!pressed && dr(PB)) {
    pressed = true;
    spd = (spd + 1) % 6;
  } else if (!dr(PB)) {
    pressed = false;
  }
//  Serial.print(spd);
//  Serial.print(" ");
//  Serial.print(!dr(PB));
//  Serial.print(" ");
//  Serial.println(pressed);
}

void loop() {
  // put your main code here, to run repeatedly:
  rdButton();
  aw(FWD, 51 * spd /* dr(SW) */);
  //aw(BCK, 51 * spd * !dr(SW));
  Serial.println(51 * spd);
  //delay(1000);
  //analogWrite(FWD, 255);
}
