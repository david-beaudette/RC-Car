#include "PPMReader.h"

// RC receiver channels
#define RC_CH_1 0
#define RC_CH_2 1
#define RC_CH_3 2
#define RC_CH_4 3
#define RC_VRA 4
#define RC_VRB 5
#define RC_SWA 6
#define RC_SWD 7

// Pins associated to each motor signal
#define ML_FWD 6
#define ML_REV 9
#define MR_FWD 10
#define MR_REV 11


PPMReader ppmReader(2, 0, false);

void setup()
{
  Serial.begin(115200);
  Serial.println("Ready to race.");
  
  ppmReader.start();
  
  pinMode(ML_FWD, OUTPUT); // left forward
  pinMode(ML_REV, OUTPUT); // left reverse
  pinMode(MR_FWD, OUTPUT); // right forward
  pinMode(MR_REV, OUTPUT); // right reverse
}

void loop()
{

  uint8_t ch_num = 0;
  int ppm_ch[8];
  while(ppmReader.get(ch_num) != 0){  
    // Print out the servo values
    // Serial.print(ppmReader.get(count));
    // Serial.print("  ");
    ppm_ch[ch_num] = ppmReader.get(ch_num);
    ch_num++;
  }
  // Serial.println("");

  // Set motor PWM 
  byte lf, lr, rf, rr;

  lf = constrain(map(ppm_ch[RC_CH_3], 1500, 2000, 0, 255), 0, 255);
  lr = constrain(map(ppm_ch[RC_CH_3], 1000, 1500, 255, 0), 0, 255);
  rf = constrain(map(ppm_ch[RC_CH_4], 1500, 2000, 0, 255), 0, 255);
  rr = constrain(map(ppm_ch[RC_CH_4], 1000, 1500, 255, 0), 0, 255);

  analogWrite(ML_FWD, lf);
  analogWrite(ML_REV, lr);
  analogWrite(MR_FWD, rf);
  analogWrite(MR_REV, rr);
}
