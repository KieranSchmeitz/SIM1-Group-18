/*
missing turn detection from sensor values
missing turn instuctuin
missing execution of turn instruction
missing symbol detection (pause, end symbol)
missing symbol instruction
missing execution of symbol instruction

*/

//temp
int pinUndefind;
int temp;
//libraries
  

//define    j++;
  }
  if(numofSensor % 2 == 1){
    middleSide[(numofSensor/2)+1] = sensorValeues[(numofSensor/2)+1];    //if is middle exists middle is middle in center of middle middleing middle sets to middle good
  }
}


  //ajustebles  (change theese to fine tune)
    
    const int baseSpeed = 33;      //in percentage (%)
    const int sensorThreshold;      //the darker the tape the lower the threshold needs to be (0-1023)

  //pins
    const int sensorPinArray[] = {pinUndefind,pinUndefind};     //order os sensor pins should be the same as the locaton of the sensors in reality (left to right)

    #define L298N_ena     pinUndefind     //PMW pin       
    #define L298N_in1     pinUndefind     
    #define L298N_in2     pinUndefind     
    #define L298N_enb     pinUndefind     //PMW pin
    #define L298N_in3     pinUndefind      
    #define L298N_in4     pinUndefind      

  //anything else

    typedef enum {OFF, dirFORWARD, dirREVERSE} DCMOTOR_CMD_TYPE;    //possible motor modes
    typedef enum {motorLEFT, motorRIGHT} DCMOTOR_SELECT;      //defining motor names

//global variables

  const int numofSensor = (sizeof(sensorPinArray)/sizeof(*sensorPinArray));     //calculates how many sensors are there

  bool sensorValeues[numofSensor];
  int leftSide[(numofSensor/2)];
  int rightSide[(numofSensor/2)];
  int middleSide[1];

void setup() {
  //pin INPUT/OUTPUT
    for(int i=0; i < numofSensor ;i++){     //set sensor pins as INPUT    
      pinMode(sensorPinArray[i], INPUT);
    }

    pinMode(L298N_in1, OUTPUT);
    pinMode(L298N_in2, OUTPUT);
    pinMode(L298N_in3, OUTPUT);
    pinMode(L298N_in4, OUTPUT);
    pinMode(L298N_ena, OUTPUT);
    pinMode(L298N_enb, OUTPUT);
  
  //anything else
    DCmotor(OFF, motorLEFT, 0);     //turns off motors at start
    DCmotor(OFF, motorRIGHT, 0);
  
    void splitSides();
}

void loop() {
  
  readSensors();
  splitSides();

  if(temp == 0){
  //biggest turn

  }else if(temp == 0){
  //big turn

  }else if(temp == 0){
  //medium turn

  }else if(temp == 0){
  //small turn

  }else if(temp == 0){
  //line correction turn
  
  }else{
    //strait line
    DCmotor(dirFORWARD,motorRIGHT,baseSpeed);
    DCmotor(dirFORWARD,motorLEFT,baseSpeed);
  }
}

//H-bridge controll function    (only works for two or less motors)
void DCmotor(const DCMOTOR_CMD_TYPE cmd, const DCMOTOR_SELECT sel, const int drive_level) {
  int PWMsignal;
  int pinC1, pinC2, pinEN;

  // Based on motor selection, we use different pins to control the motor
  if (sel == motorRIGHT) {
    pinC1 = L298N_in1;
    pinC2 = L298N_in2;
    pinEN = L298N_ena;
  } else {
    pinC1 = L298N_in3;
    pinC2 = L298N_in4;
    pinEN = L298N_enb;
  }

  // Convert drive_level(%) 0..100 to range 0..255
  PWMsignal = map(drive_level, 0, 100, 0, 255);

  // Execute motor commands (direction and speed)
  switch (cmd) {
    case dirFORWARD:
      digitalWrite(pinC1, HIGH);
      digitalWrite(pinC2, LOW);
      analogWrite(pinEN, PWMsignal);
      break;
    case dirREVERSE:
      digitalWrite(pinC1, LOW);
      digitalWrite(pinC2, HIGH);
      analogWrite(pinEN, PWMsignal);
      break;
    case OFF:
      digitalWrite(pinC1, HIGH);
      digitalWrite(pinC2, HIGH);
      analogWrite(pinEN, 0); // Stop motor
      break;
  }
}

void readSensors(){     //reads the pins on sensorPinArray[] and writes down the results to sensorValeues[] 

  for(int i = 0; i < numofSensor; i++){
    if(sensorPinArray[i] >= PIN_A0);{     //checks if selected pin is analog
        if(analogRead(sensorPinArray[i])<=sensorThreshold){     //pin is analog   |   does it surpasses threshold
          sensorValeues[i] = 1;    
        }else{
          sensorValeues[i] = 0;
        }
    }else{
      sensorValeues[i] = digitalRead(sensorPinArray[i]);      //pin is digital    
    }
  }
}

// devides sensor valeues into left and right side array, where the most outer sensor is at posision 0
void splitSides(){
  
  for(int i = 0; i < numofSensor/2; i++){     //left side (reads left to right)
    leftSide[i] = sensorValeues[i];
  }
  int j = 0;
  for(int i = numofSensor; i < numofSensor/2; i--){     //right side (reads right to left)
    rightSide[j] = sensorValeues[i];
