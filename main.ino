#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(3, 2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int dw = 0;

#define s0 7        //Module pins wiring
#define s1 9
#define s2 10
#define s3 11
#define out 12


int f_red = 0;
int f_green = 0;
int f_blue = 0;

int merah = 1;
int biru = 2;
int hijau = 3;
int kuning = 4;

int bt = 850;
int br = 780;
int bb = 500;
int bg = 300;
int bk = 100;

// 1 kuning
// 2 warna benda tidak terdeteksi
// 3 pembukaan
// 4 merah
// 5 biru
// 6 hijau

long randNumber;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  pinMode(s0, OUTPUT);   //pin modes
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  lcd.begin();
  digitalWrite(s0, HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
  digitalWrite(s1, LOW); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%

  // put your setup code here, to run once:
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  myDFPlayer.begin(mySoftwareSerial);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(3);  //Play the first mp3
  printLcd("Pengenalan warna","Lisma Autia");
  delay(8000);
}

void loop() {
  printLcd("Silahkan","Dekatkan benda");
  delay(2000);
  cekWarna();
}

void utama()
{
  randNumber = random(6);

  // put your main code here, to run repeatedly:
  Serial.print("Nilai RAND : ");
  Serial.println(randNumber);
  delay(5000);
  if (randNumber == 3) {

  } else {
    if (randNumber == merah) {
      Serial.println("Benda berwarna merah");
      myDFPlayer.play(4);
      delay(3000);
    } else if (randNumber == biru) {
      Serial.println("Benda berwarna biru");
      myDFPlayer.play(5);
      delay(3000);
    } else if (randNumber == hijau) {
      Serial.println("Benda berwarna hijau");
      myDFPlayer.play(6);
      delay(3000);
    } else if (randNumber == kuning) {
      Serial.println("Benda berwarna kuning");
      myDFPlayer.play(1);
      delay(3000);
    } else {
      Serial.println("Tidak terdeteksi");
      myDFPlayer.play(2);
      delay(3000);
    }

  }


  if (dw == 5) {
    dw = 0;
  } else {
    dw++;
  }
  delay(2000);
}

void cekWarna()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  f_red = pulseIn(out, LOW);
  Serial.print("R = ");
  Serial.print(f_red);
  delay(250);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  f_green = pulseIn(out, LOW);
  Serial.print(" - G = ");
  Serial.print(f_green);
  delay(250);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  f_blue = pulseIn(out, LOW);
  Serial.print(" - B = ");
  Serial.println(f_blue);
  delay(250);

  if (f_green > bt) {
    Serial.println("Tidak terdeteksi");
        myDFPlayer.play(2);
    printLcd("Warna tidak","terdeteksi");
    delay(3000);
  } else if (f_green > br) {
    Serial.println("Merah");
        myDFPlayer.play(4);
    printLcd("Warna merah","terdeteksi");
    delay(3000);
  } else if (f_green > bb) {
    Serial.println("Biru");
        myDFPlayer.play(5);
    printLcd("Warna biru","terdeteksi");
    delay(3000);
  } else if (f_green > bg) {
    Serial.println("Hijauu");
        myDFPlayer.play(6);
    printLcd("Warna hijau","terdeteksi");
    delay(3000);
  } else if (f_green > bk) {
    Serial.println("Kuning");
        myDFPlayer.play(1);
    printLcd("Warna kuning","terdeteksi");
    delay(3000);
  }

  delay(2000);

}

void printLcd(String teks, String teks2){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(teks);
  lcd.setCursor(0,1);
  lcd.print(teks2);
}
