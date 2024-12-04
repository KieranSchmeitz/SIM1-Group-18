const int speedPotPin =  A0;
const int turnPotPin =  A1;



int speedPot;
int turnPot;

int rightspeed; 
int leftspeed;
float turncoficient;
//define
  //ajustebles  (change theese to fine tune)
    
    //const int threshold

  //pins

    #define L298N_ena     7     //PMW pin       
    #define L298N_in1     32      
    #define L298N_in2     34      
    #define L298N_enb     8     //PMW pin
    #define L298N_in3     33      
    #define L298N_in4     35      

  //anything else

    typedef enum {OFF, dirFORWARD, dirREVERSE} DCMOTOR_CMD_TYPE;    //possible motor modes
    typedef enum {motorLEFT, motorRIGHT} DCMOTOR_SELECT;      //defining motor names

//global variables

  

void setup() {
  //pin INPUT/OUTPUT
    

    pinMode(speedPotPin, INPUT);
    pinMode(turnPotPin, INPUT);

    pinMode(L298N_in1, OUTPUT);
    pinMode(L298N_in2, OUTPUT);
    pinMode(L298N_in3, OUTPUT);
    pinMode(L298N_in4, OUTPUT);
    pinMode(L298N_ena, OUTPUT);
    pinMode(L298N_enb, OUTPUT);
  
  //anything else
    DCmotor(OFF, motorLEFT, 0);     //turns off motors at start
    DCmotor(OFF, motorRIGHT, 0);

    Serial.begin(9600);
  
}

void loop() {

  speedPot = analogRead(speedPotPin);


  turn();



    DCmotor(dirFORWARD,motorRIGHT,rightspeed);
    DCmotor(dirFORWARD,motorLEFT,leftspeed);

  Serial.print("sped : ");
  Serial.print(speedPot);
  Serial.print("  |  trn : ");
  Serial.print(turnPot);
  Serial.print("  |  coef : ");
  Serial.print(turncoficient);
  Serial.print("  |  rsped : ");
  Serial.print(rightspeed);
  Serial.print("  |  lsped : ");
  Serial.print(leftspeed);
  Serial.println();

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

  // Convert drive_level 1023 to range 0..255
  PWMsignal = drive_level/4;
  // Execute motor commands (direction and speed)
  Serial.print(" | ");
  Serial.print(PWMsignal);
  Serial.print(" | ");
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


void turn(){
  turnPot = analogRead(turnPotPin);
  turncoficient = turnPot/512.0;

  if (turncoficient < 1){
    leftspeed = speedPot*turncoficient;
    rightspeed = speedPot;
  }else{
    turncoficient = 2 - turncoficient;
    leftspeed = speedPot;
    rightspeed = speedPot*turncoficient;
  }

}
