// for pin declaration
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;

// for ir sensor values
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 0;

//for ir binary values
int v1 = 0;
int v2 = 0;
int v3 = 0;
int v4 = 0;
int v5 = 0;
int v6 = 0;

// sensor calc init
int threshold = 500;
int sdata = 0;

// initialize motor pins
int lme=11, lmf=12, lmb=13;
int rme=10, rmf=9, rmb=8; 

// pwm levels
int fast = 150;
int med = 100;
int slow = 75;
int off = 0;

// declare functions
void TCRTSensorRead();
void motorRun(int a , int b);
void SonarSensorRead();
void irCheck();

//CONTROL BOARD
int BotRunning = 1;
int IRPower = 1;
int IRCheck = 1;
int motorPower = 1;
int state = 0; //0 for lfr w/ arm, 1 for auto clean (WIP), 2 for manual clean via BT (WIP)

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.println("Initializing systems...");

  //ir array for lfr
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);

// motor pin outs
  pinMode(lme, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rme, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);

  Serial.println("LFR is Ready!");
}

void loop() {
  while (BotRunning == 1) {
    while (state==0) { //lfr-mode

      if (IRPower == 1) {
        TCRTSensorRead();
      }

      //ircheck
      if (IRCheck = 1) {
        irCheck();
        }

      if (motorPower == 1) {
        //WHITE
        if(sdata==0b000000)
        {
          Serial.println("Stop-No Line");
//          delay(2000);
          motorRun(off,off);
        }    

        //FORWARD
        if(sdata==0b001100)
        {
          Serial.println("Forward-Line");
          motorRun(fast,fast);
        }   

        //RIGHT
        if(sdata==0b000110 || sdata==0b000100)
        {
          Serial.println("Low Right-Line");
          motorRun(fast,med);
        }  
        if(sdata==0b000010)
        {
          Serial.println("Med Right-Line");
          motorRun(fast,off);
        }    
        if(sdata==0b000011)
        {
          Serial.println("High Right-Line");
          motorRun(HIGH, off);
        }    
        if(sdata==0b000001)
        {
          Serial.println("Extreme Right-Line");
          motorRun(255, -100);
        }   

        //LEFT
        if(sdata==0b011000 || sdata==0b001000)
        {
          Serial.println("Low Left-Line");
          motorRun(med,fast);
        }    
        if(sdata==0b010000)
        {
          Serial.println("Med Left-Line");
          motorRun(off,fast);
        }    
        if(sdata==0b110000)
        {
          Serial.println("High Left-Line");
          motorRun(off,255);
        }
        if(sdata==0b100000)
        {
          Serial.println("Extreme Left-Line");
          motorRun(-100, 255);
        }   

        //BLACK
        if (sdata == 0b111111) {
          Serial.println("Stop End - Black");
          motorRun(off,off);
        }
        
      }
  }

}
}
