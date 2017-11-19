#include<Wire.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 3, 4, 5, 6);

const byte hall_sensor = 8;
const byte led_pin = 13;
unsigned int count = 0;
boolean new_state;
boolean prev_state = 1;
int circumF = 189; //circumfrence of wheel
unsigned int Speed = 0;
unsigned int maxspeed = 0;
unsigned long prevsec = 0;
unsigned long currentsec = 0;



void setup() {
  // put your setup code here, to run once:

  Wire.begin();

  pinMode(hall_sensor, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("TeamAudacious3.0");
  lcd.setCursor(0, 1);
  lcd.print("speed:");
}

void loop() {
  // put your main code here, to run repeatedly:
  prevsec = currentsec;
  count = 0;
  while (currentsec - prevsec <= 2000)
  {
    prev_state = new_state;
    delay(1);
    new_state = digitalRead(hall_sensor);
    if (prev_state == 1 && new_state == 0)
    {
      ++count;
      digitalWrite(led_pin, HIGH);
    }
    else
      digitalWrite(led_pin, LOW);

    currentsec = millis();
  }
  Serial.println("Count:");
  Serial.println(count);

  Speed = count * circumF * 18 / 1000.0;
  Serial.println("Speed:");
  Serial.println(Speed);
  lcd.setCursor(6, 1);
  lcd.print(Speed);
  //lcd.print(" Km/h");
  if (Speed > maxspeed)
    maxspeed = Speed;
  lcd.print(" Max:");
  lcd.print(maxspeed);
  Wire.beginTransmission(9);
  Wire.write(Speed); //speed
  Wire.write(maxspeed); //maxspeed
  //Wire.write(1); //firesensor
  //Wire.write(1); //fluied
  Wire.endTransmission();
}
