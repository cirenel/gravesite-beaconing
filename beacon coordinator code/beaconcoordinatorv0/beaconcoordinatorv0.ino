#include <SoftwareSerial.h>

#define xbrx 3
#define xbtx 2
SoftwareSerial xbeeS(xbrx, xbtx);

#define potIn A3
int val = 0;

struct node{
  char name;
  float lat;
  float lon;
};

node nodes[3]; 

void setup() {
//  xbee.setSerial(xbeeS);
  xbeeS.begin(9600);
  Serial.begin(9600);  
}

void loop() {
  val = analogRead(potIn);
  boolean com = false;
  String input = "";
  while (xbeeS.available() > 0){
  Serial.print(xbeeS.available());
  byte in = xbeeS.read();
  input = input + (char)in;
    com = true;
  } 

  if(com){
    com = false;
    Serial.println(input);
    if(input.length() == 4) { 
//      char nodeName = input.charAt(0); //first char of new message is node name
    } else if(input.length() > 4) {
/*      strtok(); //look up how this works, splits on token 

      node n;
      n.name = id;
      n.lat = float(inLat);
      n.lon = float(inLon); */
    }
  } 

    Serial.println(val);
    //min possible is 0. max 1023. break into 4 parts: off or send A, B or C.
    if(val < 2){
      //nada. no write 
    } else if (val < 345){
      xbeeS.write('A');
      xbeeS.write('A');
      delay(500);      
    } else if (val < 690){
      xbeeS.write('B');
      xbeeS.write('B');
      delay(500);
    } else {
      xbeeS.write('C');
      xbeeS.write('C');      
      delay(500);
    }
  
  delay(500);
}
