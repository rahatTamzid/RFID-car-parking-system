

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define SS_PIN 53
#define RST_PIN 5
#define IR_SENSOR_ENTRY_PIN 2
#define IR_SENSOR_1_PIN 3
#define IR_SENSOR_2_PIN 4
#define IR_SENSOR_3_PIN 6
#define IR_SENSOR_4_PIN 7
#define IR_SENSOR_5_PIN 8
#define P1_RED 22
#define P2_RED 24
#define P3_RED 32
#define P4_RED 28
#define P5_RED 30


#define P1_GREEN 23
#define P2_GREEN 25
#define P3_GREEN 33
#define P4_GREEN 29
#define P5_GREEN 31


Servo EntryServo;






#define card1 "6F 1B DB 28"
#define card2 "8F 02 E5 29"
#define tag1 "81 62 8B 79"
#define tag2 "D2 DF 58 A3"





MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(9600);  // Initiate a serial communication
  SPI.begin();         // Initiate  SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();


  lcd.init();
  lcd.backlight();

  // Set the cursor to the first column, first row
  lcd.setCursor(0, 0);

  // Print a message on the LCD

  pinMode(IR_SENSOR_1_PIN, INPUT);
  pinMode(IR_SENSOR_2_PIN, INPUT);
  pinMode(IR_SENSOR_3_PIN, INPUT);
  pinMode(IR_SENSOR_4_PIN, INPUT);
  pinMode(IR_SENSOR_5_PIN, INPUT);
  pinMode(IR_SENSOR_ENTRY_PIN, INPUT);
  pinMode(P1_RED,OUTPUT);
  pinMode(P2_RED,OUTPUT);
  pinMode(P3_RED,OUTPUT);
  pinMode(P4_RED,OUTPUT);
  pinMode(P5_RED,OUTPUT);
  pinMode(P1_GREEN,OUTPUT);
  pinMode(P2_GREEN,OUTPUT);
  pinMode(P3_GREEN,OUTPUT);
  pinMode(P4_GREEN,OUTPUT);
  pinMode(P5_GREEN,OUTPUT);




  EntryServo.attach(9);
}

void loop() {

  EntryServo.write(0);


  // Set the cursor to the first column, first row
  lcd.setCursor(0, 0);

  // Print a different message on the LCD


  int Parking1 = digitalRead(IR_SENSOR_1_PIN);
  int Parking2 = digitalRead(IR_SENSOR_2_PIN);
  int Parking3 = digitalRead(IR_SENSOR_3_PIN);
  int Parking4 = digitalRead(IR_SENSOR_4_PIN);
  int Parking5 = digitalRead(IR_SENSOR_5_PIN);
  int Entry = digitalRead(IR_SENSOR_ENTRY_PIN);
  int available = Parking1 + Parking2 + Parking3 + Parking4 + Parking5;
  Serial.println(available);






 if(Parking1 == 1){
   digitalWrite(P1_GREEN,HIGH);
   digitalWrite(P1_RED,LOW);
 }
  if(Parking1 == 0){
   digitalWrite(P1_GREEN,LOW);
   digitalWrite(P1_RED,HIGH);
 }

    
 if(Parking2 == 1){
   digitalWrite(P2_GREEN,HIGH);
   digitalWrite(P2_RED,LOW);
 }
  if(Parking2 == 0){
   digitalWrite(P2_GREEN,LOW);
   digitalWrite(P2_RED,HIGH);
 }

      
 if(Parking3 == 1){
   digitalWrite(P3_GREEN,HIGH);
   digitalWrite(P3_RED,LOW);
 }
  if(Parking3 == 0){
   digitalWrite(P3_GREEN,LOW);
   digitalWrite(P3_RED,HIGH);
 }

  if(Parking4 == 1){
   digitalWrite(P4_GREEN,HIGH);
   digitalWrite(P4_RED,LOW);
 }
  if(Parking4 == 0){
   digitalWrite(P4_GREEN,LOW);
   digitalWrite(P4_RED,HIGH);
 }

      
 if(Parking5 == 1){
   digitalWrite(P5_GREEN,HIGH);
   digitalWrite(P5_RED,LOW);
 }
  if(Parking5 == 0){
   digitalWrite(P5_GREEN,LOW);
   digitalWrite(P5_RED,HIGH);
 }
  /*
 Serial.println(Parking1);
 Serial.println(Parking2);
 Serial.println(Parking3);

 Serial.println(Parking4);
 Serial.println(Parking5);
 Serial.println(Entry);

 */



  if (available == 0) {
  
    delay(300);
    lcd.setCursor(0, 0);
    lcd.print("PARKING FULL   !");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  } else {


       lcd.setCursor(0, 0);
        lcd.print("BASIS SOFT EXPO");
         lcd.setCursor(0, 1);
        lcd.print("CAR PARKING");

if(Entry == 0){

        lcd.setCursor(0, 0);
        lcd.print("Available Slot ");
        lcd.setCursor(0, 15);
        lcd.print(available);
       
         
         if(Parking1 == 1){
            lcd.setCursor(0, 1);
        lcd.print("P1");
         }
        
        if(Parking2 == 1){
            lcd.setCursor(2, 1);
        lcd.print("P2");
        }
       
        if(Parking3 == 1){
            lcd.setCursor(4, 1);
        lcd.print("P3");
        }
       
        if(Parking4 == 1){
           lcd.setCursor(6, 1);
        lcd.print("P4");
        }
        
        if(Parking5 == 1){
            lcd.setCursor(8, 1);
        lcd.print("P5 ");
        }

               if(Parking1 == 0){
            lcd.setCursor(0, 1);
        lcd.print("  ");
         }
        
        if(Parking2 == 0){
            lcd.setCursor(2, 1);
        lcd.print("  ");
        }
       
        if(Parking3 == 0){
            lcd.setCursor(4, 1);
        lcd.print("  ");
        }
       
        if(Parking4 == 0){
           lcd.setCursor(6, 1);
        lcd.print("  ");
        }
        
        if(Parking5 == 0){
            lcd.setCursor(8, 1);
        lcd.print("       ");
        }
       
        delay(5000);
        
}
      // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor


    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();

    lcd.setCursor(0, 0);
    lcd.print("BASIS SOFT EXPO");
    lcd.setCursor(0, 1);
    lcd.print("CAR PARKING");

    if (content.substring(1) == card1)  //change here the UID of the card/cards that you want to give access
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome Dhaka");
      lcd.setCursor(0, 1);
      lcd.print("Metro GA3511");




 for(int pos = 0; pos <= 90; pos++) { 
    EntryServo.write(pos);              
    delay(15);                     
  }
      delay(10000);
  for(int pos = 90; pos >= 0; pos--) { 
    EntryServo.write(pos);              
    delay(15);                     
  }

      lcd.clear();
      
    lcd.setCursor(0, 0);
    lcd.print("BASIS SOFT EXPO");
    lcd.setCursor(0, 1);
    lcd.print("CAR PARKING");

    }






    else if (content.substring(1) == card2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome Dhaka");
      lcd.setCursor(0, 1);
      lcd.print(" Metro GA9389");
  for(int pos = 0; pos <= 90; pos ++) { 
    EntryServo.write(pos);              
    delay(15);                     
  }
      delay(10000);
      for(int pos = 90; pos >= 0; pos --) { 
    EntryServo.write(pos);              
    delay(15);                     
  }

    lcd.setCursor(0, 0);
    lcd.print("BASIS SOFT EXPO");
    lcd.setCursor(0, 1);
    lcd.print("CAR PARKING");
    }



    else if (content.substring(1) == tag1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome Dhaka");
      lcd.setCursor(0, 1);
      lcd.print("Metro GA9347");
      for(int pos = 0; pos <= 90; pos ++) { 
    EntryServo.write(pos);              
    delay(15);                     
  }
      delay(10000);
      for(int pos = 90; pos >= 0; pos -- ) { 
    EntryServo.write(pos);              
    delay(15);                     
  }

      delay(30);
      lcd.clear();
        lcd.setCursor(0, 0);
    lcd.print("BASIS SOFT EXPO");
    lcd.setCursor(0, 1);
    lcd.print("CAR PARKING");

    }

    else if (content.substring(1) == tag2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unauthorised");
      lcd.setCursor(0, 1);
      lcd.print("ENRTY ");
      delay(5000);
      lcd.clear();
      lcd.setCursor(0, 0);
    lcd.print("BASIS SOFT EXPO");
    lcd.setCursor(0, 1);
    lcd.print("CAR PARKING");
    }
  }
}




















void Accessing_Decision() {
}
