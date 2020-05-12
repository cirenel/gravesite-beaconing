//this is a test of XBee coms, GPS aquesition and moving the code to a Nano and adding sleep

//flora GPS connect to tx/rx post upload
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
SoftwareSerial GPSSerial (3, 5); 
Adafruit_GPS GPS(&GPSSerial);
float LatH = 0; 
float LonH = 0;
char LatDir = 'a'; 
char LonDir ='a';

//import neopixel libraries, set up strip of 9 neopixels on 6
#include <Adafruit_NeoPixel.h>
#define LEDPIN 8 //ugh these are all over. gj self. //7 is A //8 is C // 8 is B 
#define NUMPIXELS 9
#define DELAYVAL 500 // time in ms for pauses in lightwork // at this time delay value, we have ~4 min of light run time
Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

//XBee shield  
///#define xbwake 7 //need wire to jumper on shield 
#define xbrx 2
#define xbtx 4
SoftwareSerial xbee(xbrx, xbtx);

#define name 'B' //the beacon XBee identifier 

void setup() {
  Serial.begin(9600);
  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //update rate 
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPSSerial.println(PMTK_Q_RELEASE);
  xbee.begin(9600);
  xbee.println((char)name);
  strip.begin();
//  Serial.println("sup.");

  indicatorLight(strip.Color(255,120,120));
  indicatorLight(strip.Color(255,120,120));
  
    
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
    float curLatDir = GPS.lat;
    float curLonDir = GPS.lon;
//    Serial.print(curLatH == LatH); Serial.print(" : "); Serial.println(curLonH == LonH);
      xbee.listen();      
    if(curLatH != LatH || curLonH != LonH || curLonDir != LonDir || curLatDir != LatDir){  //either first loop or device has been moved. update and send info to coord XBee
      //red light == GPS changeover
//      colorOn(strip.Color(255,0,0));delay(1000);colorOn(strip.Color(0,0,0));
      indicatorLight(strip.Color(0,100,255)); //visual indicator "i have gps"
      LatH = curLatH; 
      LonH = curLonH;
      LatDir = curLatDir; 
      LonDir = curLonDir; 
/*      Serial.println(LatH);
      Serial.println(LonH);
      Serial.println(LatDir);
      Serial.println(LonDir);
      Serial.println(LatDeg);
      Serial.println(LonDeg);
                      
      Serial.print("xbee begin");*/
      String msg = String(name)+":"+String(curLatH)+":"+String(curLonH)+"\n";
      xbee.println(msg); //dont need direction, if it is in xbee range it damn well better be in the same hemisphere... wont work on the equator or at the prime meredian 
    } else if(xbee.available() > 0) { //we have a fix and are stable. do we have incoming coms? if so, light up!
//        Serial.print("------------------>");
        //wave green, pause, wave white, pause 
        boolean run = false; 
        while( xbee.available() > 0) {
          byte rec = xbee.read();
//          Serial.println((char)rec);
          if(rec == (byte)name) {
            run = true;
          }
        }
        if(run) {
          run = false; 
          for(short i = 0; i < 20; i++){
            colorWave(strip.Color(0, 150, 0));
            delay(1000);
            colorWave(strip.Color(150, 150, 150));
            delay(1000);
          }
          colorOn(strip.Color(0,0,0));  //turn off lights at the end 
          //delay(300000); //prevent spam from coordiantor. do server/controller side later.  
          }
        }

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

void indicatorLight(uint32_t color){
  strip.clear(); 
  strip.setPixelColor(NUMPIXELS/2, color);  
  strip.show(); 
  delay(DELAYVAL); 
  strip.clear(); 
  strip.setPixelColor(NUMPIXELS/2,0);  
  strip.show(); 
  delay(DELAYVAL);
}

void colorOn(uint32_t color){
  strip.clear(); 
  for(int i=0; i<NUMPIXELS; i++) { 
    strip.setPixelColor(i, color);  
  }
  strip.show(); 
  delay(DELAYVAL); 
}
