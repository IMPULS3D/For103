#include <Adafruit_CircuitPlayground.h>

volatile int duration = 2000;
volatile int score = 0; 

volatile bool gameState = false;

const byte leftPin = 4;
const byte rightPin = 5;


const byte leftbuttonPin = CircuitPlayground.leftButton();
const byte rightbuttonPin = CircuitPlayground.rightButton();


float midi[127];
int A_four = 440;



int songWin[9][2] = {
    {69, 100},  // song[0][0]], song[0][1]]
    {68, 100},  // song[1][0]], song[1][1]]
    {69, 100},  // song[2][0]], song[2][1]]
    {68, 100},  // song[3][0]], song[3][1]]
    {69, 100},  // song[4][0]], song[4][1]]
    {64, 100},  // song[5][0]], song[5][1]]
    {67, 100},  // song[5][0]], song[5][1]]
    {65, 100},  // song[5][0]], song[5][1]]
    {62, 400},  // song[5][0]], song[5][1]]
  };

int songLose[9][2] = {
    {69, 100},  // song[0][0]], song[0][1]]
    {68, 100},  // song[1][0]], song[1][1]]
    {67, 100},  // song[2][0]], song[2][1]]
    {66, 100},  // song[3][0]], song[3][1]]
    {65, 100},  // song[4][0]], song[4][1]]
    {64, 100},  // song[5][0]], song[5][1]]
    {63, 100},  // song[5][0]], song[5][1]]
    {62, 100},  // song[5][0]], song[5][1]]
    {61, 100},  // song[5][0]], song[5][1]]
  };

int songScore[4][2] = {
    {60, 100},  // song[0][0]], song[0][1]]
    {60, 100},  // song[1][0]], song[1][1]]
    {60, 100},  // song[2][0]], song[2][1]]
    {65, 400},  // song[3][0]], song[3][1]]

  };



const byte offPin = 7;

const byte switchPin = CircuitPlayground.slideSwitch();


volatile bool switchFlag = 0;
volatile bool rightbuttonFlag = 0;
volatile bool leftbuttonFlag = 0;

volatile int slideState = 0;






void setup() {
 CircuitPlayground.begin();


  generateMIDI();

  CircuitPlayground.leftButton();  
  CircuitPlayground.rightButton();

  pinMode(rightbuttonPin, INPUT_PULLDOWN);
  pinMode(leftbuttonPin, INPUT_PULLDOWN);

  CircuitPlayground.slideSwitch();

  pinMode(switchPin, INPUT_PULLUP);


 attachInterrupt(digitalPinToInterrupt(offPin), gameOn, CHANGE);


  attachInterrupt(digitalPinToInterrupt(rightPin), rightScore, HIGH);
  attachInterrupt(digitalPinToInterrupt(leftPin), leftScore, HIGH);

}









void loop() {

 if (switchFlag){
   
  slideState = digitalRead(7);

}



  if (slideState == 1) { //IF SWITCH IS ON
gameState = true;



  } else{

gameState = false;

  }


  if (gameState == 1) { //IF SWITCH IS ON



//WIN CONDITION is duration = 100
        if (duration == 100){

CircuitPlayground.clearPixels();

//PLAY songWin SONG
for(int i = 0; i < sizeof(songWin) / sizeof(songWin[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[songWin[i][0]], songWin[i][1]);
    Serial.println(midi[songWin[i][0]]);
    delay(1);
  }

slideState == 0;

gameState = false;

} else{ // WHAT HAPPENS WHEN GAME IS ON

 int randomColor = random(1,3);

 if (randomColor == 1){ //IF 1 THEN RED PRESS RIGHT BUTTON
   
    for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, 255 , 0 , 0 );
    }
delay(duration);
CircuitPlayground.clearPixels();


if (rightbuttonFlag == 1){ //SCORE CONDITION
CircuitPlayground.clearPixels();

//PLAY songScore SONG
for(int i = 0; i < sizeof(songScore) / sizeof(songScore[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[songScore[i][0]], songScore[i][1]);
    Serial.println(midi[songScore[i][0]]);
    delay(1);
  }

duration = duration - 50;
score = score + 1;
randomColor = 2;

rightbuttonFlag = 0;

} else if (leftbuttonFlag == 1){ //LOSE CONDITION
CircuitPlayground.clearPixels();

//PLAY songLose SONG
for(int i = 0; i < sizeof(songLose) / sizeof(songLose[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[songLose[i][0]], songLose[i][1]);
    Serial.println(midi[songLose[i][0]]);
    delay(1);
  }
  CircuitPlayground.playTone(midi[60],100);
  CircuitPlayground.playTone(midi[60+score],100);
  CircuitPlayground.playTone(midi[60],100);
  CircuitPlayground.playTone(midi[60+score],100);
  CircuitPlayground.playTone(midi[60],100);
  CircuitPlayground.playTone(midi[60+score],100);


 duration = 2000;
 score = 0; 


slideState == 0;

gameState = false;


leftbuttonFlag = 0;
}



   
 } else if (randomColor == 2){ //IF 2 THEN BLUE PRESS LEFT BUTTON

    for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, 0 , 255 , 255 );
    }
delay(duration);
CircuitPlayground.clearPixels();



if (leftbuttonFlag == 1){ // SCORE CONDITION
CircuitPlayground.clearPixels();

//PLAY songScore SONG
for(int i = 0; i < sizeof(songScore) / sizeof(songScore[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[songScore[i][0]], songScore[i][1]);
    Serial.println(midi[songScore[i][0]]);
    delay(1);
  }
duration = duration - 50;
score = score + 1;
randomColor = 0;

leftbuttonFlag = 0;

} else if(rightbuttonFlag == 1){ // LOSE CONDITION
CircuitPlayground.clearPixels();
  

//PLAY songLose SONG
for(int i = 0; i < sizeof(songLose) / sizeof(songLose[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[songLose[i][0]], songLose[i][1]);
    Serial.println(midi[songLose[i][0]]);
    delay(1);
  }
    CircuitPlayground.playTone(midi[60],100);
  CircuitPlayground.playTone(midi[60+score],100);
  CircuitPlayground.playTone(midi[60],100);
  CircuitPlayground.playTone(midi[60+score],100);
  CircuitPlayground.playTone(midi[60],100);
  CircuitPlayground.playTone(midi[60+score],100);

 duration = 2000;
 score = 0; 


slideState == 0;

gameState = false;

  rightbuttonFlag = 0;
}





 }


}



  } else{
CircuitPlayground.clearPixels();


  }





}


void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}

void gameOn () {

  switchFlag = 1;

 duration = 2000;
 score = 0; 





}


void leftScore() {

  leftbuttonFlag = 1;

}

void rightScore() {

  rightbuttonFlag = 1;

}



