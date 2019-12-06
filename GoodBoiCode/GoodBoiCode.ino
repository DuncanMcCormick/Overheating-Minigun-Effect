/*  Overheating Minigun Effect
 *  By: Duncan McCormick
 *  for: Building Interactive Gadjets
 *  Date: 12/6/2019
 *  Basecode from: https://howtomechatronics.com/tutorials/arduino/how-to-track-orientation-with-arduino-and-adxl345-accelerometer/
 *  Basecode by: Dejan
 */
  
#include <Wire.h>                                     //  includes the Wire.h libary
int ADXL345 = 0x53;                                  

  
int ledPin = 11;                                      //  Sets the ledPin to pin 11
int brightBoi = 0;                                    //  Sets the brightness level to 0

void setup()                                          //  SETUP!!!!!  
{
  pinMode(ledPin, OUTPUT);                            //  Sets the ledPin to OUTPUT not sure if its needed because Im using analog(SIDE NOTE: I think ill keep this in if brightness isnt working for the cosplay so that when brightness equals 255 it sets the led to HIGH. I found when its set to HIGH its brighter.)
  Serial.begin(9600);                                 //  Begins serial comunications
  Wire.begin();                                  
  Wire.beginTransmission(ADXL345);                    //  Talks to the ADLX345
  Wire.write(0x2D);                                
  Wire.write(8);                                      //  If I change this stuff it doesnt work so im not touching it
  Wire.endTransmission();                           
}

void loop(){
  float Yeets = YeetMeter();                          //  Summons the YeetMeter function and gives its Yeets value to Yeets
  Yeets = abs(Yeets);                                 //  Sets Yeets to the absolute value so I don't have to deal with negative ranges
  Serial.print("Yeet= ");                             //  Prints Yeets=
  Serial.println(Yeets);                              //  Prints what Yeets= is and ends the line

  if(Yeets > 1.00 && brightBoi <= 254){               //  If the Xvalue which is set to Yeets is greater than 1 and the brightness is less than 254 is will run the following
      brightBoi= brightBoi+1;                         //  it takes the Brightness and adds one to it.
   }                                                  //  The reason it wont run when brightness is greater than 254 is to stop it from going over and than resetting the brightness.

  if(Yeets <= 1.00 && brightBoi >= 1){                //  Basically the opposite of the above
      brightBoi = brightBoi-1;                        //  instead of increassing the brightness it decreases
      delay(100);                                     //  I'm still ocasionally messing around with this because I want it to fade out slower without looking wrong this fades out to fast imo
    }

analogWrite(ledPin, brightBoi);                       //  makes the light light up equal to the value of brightBoi
delay(100);                                           //  waits before running the code again
}

float YeetMeter()                                     //  I put YeetMeter into a function at the start of the project because I thought I would need to call it multiple times. I didnt though
{
  float Yeetmeter;                                    //  Creates Yeetmeter as a float value
  float Yeets;                                        //  Makes Yeets
  Wire.beginTransmission(ADXL345);                    //  Begins transmission to the ADXL345 accelerometer chip, not to much is modified from the example code.
  Wire.write(0x32);                                   //  
  Wire.endTransmission(false);                        //  
  Wire.requestFrom(ADXL345, 2, true);                 //  I only need the X axis so I dont need the two
  Yeetmeter = ( Wire.read()| Wire.read() << 8);       //  
  Yeetmeter = Yeetmeter/256;                          //  divides Yeetmeter by 256 to make a smaller value. listed in the ADLX345.pdf I linked are the other values 
  Yeets = Yeetmeter;                                  //  gives thE Yeetmeter's value to Yeets
  Yeets;                                              //  Yeet
  return Yeets;                                       //  Returns the Yeets value
}
