/*
SkipBo - Buzzer

* Audio Out - pin 9
* SD card attached to SPI bus as follows:
* MISO - pin 12
* MOSI - pin 11
* SCK - pin 13
* CS - pin 4 
*/

#include "SD.h" //Lib to read SD card
#include "TMRpcm.h" //Lib to play auido
#include "SPI.h" //SPI lib for SD card

#define SD_ChipSelectPin 4 //Chip select is pin number 4
TMRpcm music; //Lib object is named "music"

// Settings for Arcade-Button
int buttonPin = 7;
int button_state;
int current_music_state = 0;
int past_music_state = 0;

void setup(){
Serial.begin(9600);
music.speakerPin = 9; // Audio out on pin 9
SD.begin(SD_ChipSelectPin); // Start SD Card
music.setVolume(5); // 0 to 7. Set volume level
music.quality(1); //  Set 1 for 2x oversampling Set 0 for normal
pinMode(buttonPin,INPUT);
}

void loop(){

button_state = digitalRead(buttonPin); // if not pressed, current is flowing, so normally 1

// when button is pressed change current music state based on past music state 
if (button_state == 0){
  if (past_music_state == 0){
    current_music_state = 1;
  }
   else {
    current_music_state = 0;
  }
  
  // avoid bouncing
  delay(400);
}

if (current_music_state == 1 && !music.isPlaying()){
  music.play("toto.wav");
  }
  
else if (current_music_state == 0 && music.isPlaying()){
  music.stopPlayback();
  }

past_music_state = current_music_state;
  
}
