#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define xbrx 3
#define xbtx 2
SoftwareSerial xbeeS(xbrx, xbtx);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define potIn A3
int val = 0;

struct node {
  char name;
  float lat;
  float lon;
};

node nodes[3];

void setup() {
  xbeeS.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  val = analogRead(potIn);
  boolean com = false;
  String input = "";
//  Serial.println(xbeeS.available());
  while (xbeeS.available() > 0) {
    byte in = xbeeS.read();
    input = input + (char)in;
    com = true;
    delay(5);
  }

  Serial.println(input);
  if (com) {
    com = false;
    lcd.clear(); lcd.print(input); lcd.display(); delay(5000);
    /*    if(input.length() == 4) {
      //      char nodeName = input.charAt(0); //first char of new message is node name
        } else if(input.length() > 4) {
          strtok(); //look up how this works, splits on token

          node n;
          n.name = id;
          n.lat = float(inLat);
          n.lon = float(inLon);
        }*/
  } else if (val < 2) {   //min possible is 0. max 1023. break into 4 parts: off or send A, B or C.
    //nada. no write
    lcd.clear(); lcd.print("no value");
  } else if (val < 345) {
    xbeeS.write('A');
    xbeeS.write('A');
    lcd.clear(); lcd.print("A");
    delay(500);
  } else if (val < 690) {
    xbeeS.write('B');
    xbeeS.write('B');
    lcd.clear(); lcd.print("B");
    delay(500);
  } else {
    xbeeS.write('C');
    xbeeS.write('C');
    lcd.clear(); lcd.print("C");
    delay(500);
  }

  lcd.display();
  delay(1000);
}
