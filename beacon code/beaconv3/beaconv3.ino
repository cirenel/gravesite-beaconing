//this is a test of XBee coms, GPS aquesition and moving the code to a Nanoa

//flora GPS connect to tx/rx post upload
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
SoftwareSerial GPSSerial (3, 5); 
Adafruit_GPS GPS(&GPSSerial);
float LatH = 0; 
float LonH = 0;
char LatDir; 
char LonDir;
float LatDeg = 0; 
float LonDeg = 0;

//import neopixel libraries, set up strip of 9 neopixels on 6
#include <Adafruit_NeoPixel.h>
#define LEDPIN 8
#define NUMPIXELS 9
#define DELAYVAL 500 // time in ms for pauses in lightwork // at this time delay value, we have ~4 min of light run time
Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

//XBee shield  
///#define xbwake 7 //need wire to jumper on shield 
#define xbrx 2
#define xbtx 4
SoftwareSerial xbee(xbrx, xbtx);


void setup() {
  Serial.begin(115200);
  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //update rate 
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPSSerial.println(PMTK_Q_RELEASE);
  xbee.begin(9600);
  xbee.println("yo. here.\n");
  strip.begin();
  Serial.println("sup.");
/*  colorOn(strip.Color(120,120,120));
  delay(1000);
    colorOn(strip.Color(0,0,0));*/
}

void loop() {
//doing this again, but why!? can only have one of these software serials being listened to at a time. if the last one was the xbee, need to switch 
  GPSSerial.listen();
  //  GPS.begin(9600); //?
  char c = GPS.read();

  if (GPS.newNMEAreceived()) {
    GPS.lastNMEA();
    if(!GPS.parse(GPS.lastNMEA())){ 
        return;
    }
  }

  if(GPS.fix){ //yay the gps has a signal 
    float curLatH = GPS.latitude; 
    float curLonH = GPS.longitude;

//    Serial.print(curLatH == LatH); Serial.print(" : "); Serial.println(curLonH == LonH);
      xbee.listen();      
    if(curLatH != LatH || curLonH != LonH){  //either first loop or device has been moved. update and send info to coord XBee
          colorOn(strip.Color(255,0,0));delay(1000);colorOn(strip.Color(0,0,0));
      LatH = GPS.latitude; 
      LonH = GPS.longitude;
      LatDir = GPS.lat; 
      LonDir = GPS.lon; 
      LatDeg = decimalDegrees(LatH, LatDir); 
      LonDeg = decimalDegrees(LonH, LonDir);
      //save directions and hour/min and degree
      //use hour/min for comparisons?
      Serial.println(LatH);
      Serial.println(LonH);
      Serial.println(LatDir);
      Serial.println(LonDir);
      Serial.println(LatDeg);
      Serial.println(LonDeg);
                      
      Serial.print("xbee begin");
      String msg = String(curLatH)+":"+String(curLonH)+"\n";
      xbee.print(msg); //dont need direction, if it is in xbee range it damn well better be in the same hemisphere... wont work on the equator or at the prime meredian 
    } else if(xbee.available() > 0) { //we have a fix and are stable. do we have incoming coms? if so, light up!
//       digitalWrite(xbwake, LOW);
//       delay(5);
        Serial.print("------------------>");
        //wave green, pause, wave white, pause 
        char rec = xbee.read();
        Serial.println(String(rec));
        for(short i = 0; i < 20; i++){
          colorWave(strip.Color(0, 150, 0));
          delay(1000);
          colorWave(strip.Color(150, 150, 150));
          delay(1000);
        }
        colorOn(strip.Color(0,0,0));  //turn off lights at the end 
        delay(300000); //prevent spam from coordiantor. do server/controller side later.  
       }
      //check this inputoutput 
//      pinMode(xbwake,INPUT);
//      digitalWrite(xbwake, HIGH);      
    GPSSerial.listen();
  }
  
  
}


void colorWave(uint32_t color){
 // strip.clear(); 
  for(int i=0; i<NUMPIXELS; i++) { 
    strip.setPixelColor(i, color);
    strip.show();   
    delay(DELAYVAL); 
  }
}

void colorOn(uint32_t color){
  strip.clear(); 
  for(int i=0; i<NUMPIXELS; i++) { 
    strip.setPixelColor(i, color);  
  }
  strip.show(); 
  delay(DELAYVAL); 
}

// Convert NMEA coordinate to decimal degrees
// from jacket code
float decimalDegrees(float nmeaCoord, char dir) {
  uint16_t wholeDegrees = 0.01*nmeaCoord;
  int modifier = 1;
 
  if (dir == 'W' || dir == 'S') {
    modifier = -1;
  }
  
  return (wholeDegrees + (nmeaCoord - 100.000*wholeDegrees)/60.000) * modifier;
}
