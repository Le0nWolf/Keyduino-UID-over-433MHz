

/*
The goal of this sketch is to send the UID from a NFC Tag over 433MHz to for example your Raspberry with KeyDuino.
The Raspberry can then check e.g. the UID and for example open a door.
Author: Le0nX3
Compatible with KeyDuino 5.1
*/

#include <KeyDuino.h>
#include <RCSwitch.h>


RCSwitch mySwitch = RCSwitch();
KeyDuino keyDuino;

uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t uidLength;


void setup(void) {
  Serial.begin(115200);
  keyDuino.begin();
  mySwitch.enableTransmit(10);  // Der Sender wird an Pin 10 angeschlossen
  Serial.println("KeyDuino is ready, please scan a tag.");

}



void loop(void) {
  
 uint8_t success;
 String readID;
 String BinaryUID;
 char UidArray[8];
 char ZeroOneArray[32];
 
  //Ausgabe des UID Arrays 
 /* for (int a =0; a <= sizeof(UidArray) - 1; a++) {
    Serial.println(UidArray[a]);
  }*/

 
 success = keyDuino.readTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
 
 if (success){
   Serial.print("Tag found: ");
   keyDuino.buzz(100);
   readID = keyDuino.convertUintToString(uid, uidLength);
   readID.toCharArray(UidArray, sizeof(UidArray) + 1 ); //UID als char Array
   
   BinaryUID = convertCharToBinary(UidArray) ; // char Array wird in Binärstring umgewandelt
   BinaryUID.toCharArray(ZeroOneArray, sizeof(ZeroOneArray) + 1 ); //Binärstring wird in char Array umgewandelt
   
   Serial.print(readID); //BinäreUID wird ausgegeben
   Serial.println("   Binary: " + BinaryUID); //BinäreUID wird ausgegeben
   
   mySwitch.send(ZeroOneArray); // Der 433mhz Sender versendet die Binäre UID
   
 }
}



String convertCharToBinary(char *ch) {
  String returnType;
  String BinaryString;
  char HexArray[8] = {*ch};
  
  while (*ch) { 
    
    switch(*ch) {
      case '0':
        returnType = "0000";
        break;
      case  '1' :
        returnType = "0001";
        break;
      case  '2':
        returnType = "0010";
        break;
      case  '3':
        returnType = "0011";
        break;
      case  '4' :
        returnType = "0100";
        break;
      case  '5':
        returnType = "0101";
        break;
      case  '6':
        returnType = "0110";
      break;
      case  '7':
        returnType = "0111";
        break;
      case  '8':
        returnType = "1000";
        break;
      case  '9':
        returnType = "1001";
        break;
      case  'a':
      case  'A':      
        returnType = "1010";
        break;
      case  'b':
      case  'B':
        returnType = "1011";
        break;
      case  'c':
      case  'C':
        returnType = "1100";
        break;
      case  'd':
      case  'D':
        returnType = "1101";
        break;
      case  'e':
      case  'E':
        returnType = "1110";
        break;
      case  'f':
      case  'F' :
        returnType = "1111";
        break;
   }
  ++ch;
  BinaryString = BinaryString + returnType;
  }
  return BinaryString;
}
