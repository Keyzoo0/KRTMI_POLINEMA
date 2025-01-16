#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"


portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

hw_timer_t *Timer0_Encoder = NULL;

// encode motor
#define ENC1A 8
#define ENC1B 9
#define ENC2A 10
#define ENC2B 11
#define ENC3A 12
#define ENC3B 13
#define ENC4A 14
#define ENC4B 15

// encoder eksternal
#define ENCRA 16
#define ENCRB 17
#define ENCLA 18
#define ENCLB 21

int16_t countEncR;
int16_t countEncL;
int16_t countEnc[5];
int Venc[2];
int16_t rpm[5];
int16_t pulseL;
int16_t pulseR;
int16_t pulse[5];




void readENCL() {
  if (digitalRead(ENCLB) > 0) {
    countEncL++;
    pulseL++;
  } else {
    countEncL--;
    pulseL--;
  }
}

void readENCR() {
  if (digitalRead(ENCRB) > 0) {
    countEncR++;
    pulseR++;
  } else {
    countEncR--;
    pulseR--;
  }
}


void readENC1() {
  if (digitalRead(ENC1B) > 0) {
    countEnc[1]++;
    pulse[1]++;
  } else {
    countEnc[1]--;
    pulse[1]--;
  }
}


void readENC2() {
  if (digitalRead(ENC2B) > 0) {
    countEnc[2]++;
    pulse[2]++;
  } else {
    countEnc[2]--;
    pulse[2]--;
  }
}


void readENC3() {
  if (digitalRead(ENC3B) > 0) {
    countEnc[3]++;
    pulse[3]++;
  } else {  // while (!Serial) delay(10);  // wait for serial port to open!
  // if (!bno.begin()) {
  //   while (1)
  //     ;
  // }

    countEnc[3]--;
    pulse[3]--;
  }
}


void readENC4() {
  if (digitalRead(ENC4B) > 0) {
    countEnc[4]++;
    pulse[4]++;
  } else {
    countEnc[4]--;
    pulse[4]--;
  }
}

void readEnc (){
  readENCL();
  readENCR();
  readENC1();
  readENC2();
  readENC3();
  readENC4();
} 

void IRAM_ATTR TimerEncoder(){ // timer for calculate RPM
  portENTER_CRITICAL_ISR(&timerMux);
  Venc[1] = pulseL * 6000 / 104;
  Venc[0] = pulseR * 6000 / 104;
  rpm[1] = pulse[1] * 6000 / 104;
  rpm[2] = pulse[2] * 6000 / 104;
  rpm[3] = pulse[3] * 6000 / 104;
  rpm[4] = pulse[4] * 6000 / 104;

  pulseL = pulseR = 0;
  portEXIT_CRITICAL_ISR(&timerMux);
}


void initTimer(){
  
  Timer0_Encoder = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Encoder, &TimerEncoder, true);
  timerAlarmWrite(Timer0_Encoder, 10000, true);
  timerAlarmEnable(Timer0_Encoder);

  
}

void initEncoder() {
  
  pinMode(ENCRA, INPUT);
  pinMode(ENCRB, INPUT);
  pinMode(ENCLA, INPUT);
  pinMode(ENCLB, INPUT);
  pinMode(ENC1A, INPUT);
  pinMode(ENC1B, INPUT);
  pinMode(ENC2A, INPUT);
  pinMode(ENC2B, INPUT);
  pinMode(ENC3A, INPUT);
  pinMode(ENC3B, INPUT);
  pinMode(ENC4A, INPUT);
  pinMode(ENC4B, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ENCRA), readENCR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCLA), readENCL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1A), readENC1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC2A), readENC2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC3A), readENC3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC4A), readENC4, CHANGE);
  
}

void setupEncoder() {
  // put your setup code here, to run once:
   initTimer();
   initEncoder();
}

