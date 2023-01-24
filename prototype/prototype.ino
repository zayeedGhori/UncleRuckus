#define FWD 9
#define BCK 10
#define PB 4
#define SW 3
#define TRIG 13
#define ECHO 12
#define pm pinMode
#define aw analogWrite
#define dw digitalWrite
#define dr digitalRead
#define dms delayMicroseconds

int spd, distance;
long duration;
bool pressed;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pm(FWD, OUTPUT);
  pm(BCK, OUTPUT);
  pm(PB, INPUT/*_PULLUP*/);
  pm(TRIG, OUTPUT);
  pm(ECHO, INPUT);
  spd = 0;
  pressed = false;
}

void rdButton() {
  if (!pressed && dr(PB)) {
    pressed = true;
    spd = (spd + 1) % 11;
  } else if (!dr(PB)) {
    pressed = false;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  dw(TRIG, LOW);
  dms(2);
  dw(TRIG, HIGH);
  dms(10);
  duration = pulseIn(ECHO, HIGH);
//  Serial.println(duration);
  distance = min((int) (duration * 0.034/2), 350);
  Serial.println(distance);
  // rdButton();
  // Map distance to 0-255 range for pwm
  spd = map(distance,0,350,0,255);
  aw(FWD,spd /* dr(SW) */);
//  Serial.println(spd);
  //delay(1000);
  //analogWrite(FWD, 255);
}
