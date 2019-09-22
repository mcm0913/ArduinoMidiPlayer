#define FILENAME "midifile.txt"
//Loop Precision = 100
const int BUZZERS=3;
//int BUZZERARRAY[BUZZERS]={30,31,32,33,34,35,36,37};
int BUZZERARRAY[3]={30,31,32};
double TIMEMULTIPLYER=0.6;
/*
    Beeper Music Player REV 01(Alpha)
    Jun 22 2019
    By CHMM, (temporarily) all rights reserved.

    For a single beeper only.
    File should be stored in the root of SD card,
    file format as shown:
        48 1000 1
        Nt Time V
        Nt  =Note(0~88)
        Time=The time of the event should happen, counted from the beginning, in millisecond.
        V   =Velocity(0 to switch off, other value to switch on)
    !!!    FILE SHOULD END WITH NEWLINE!

    You will need the Tone Library.
    This library will help you to create more Tone instance, but UP TO 3!!!!!!!!!!!

    delay(); is not malfunctioning.
    newDelay(); is only for Arduino with 16MHz Clock speed.    
*/
/*
    According to the SD Library, the SD card should be attached in the following way:
      CONNECTOR | ArduinoUNO/Duemilanove | Mega1280/2560 
      MOSI      |           11           |      51
      MISO      |           12           |      50
      CLK       |           13           |      52
      CS/SS     |           4            |      4
    SD Library created by Tom Igoe at Apr 9 2012 and is in the public domain. Thankyou!

    Supplyment Information:
    Other than the SD, you need some buzzers (no more than 3), which should have positive (5v) connected to the declared pins above,
    and have the same negative connected to the Arduino. There is no need of other wires, but you can watch the progress of the Arduino
    sound via the serial monitor. 

    Thankyou for playing(LOL) with this.
*/

#include <SPI.h>
#include <SD.h>
#include <stdio.h>
#include <Tone.h>

#define dd4tick  __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t"); 
#define delayOneUs(){dd4tick; dd4tick; dd4tick; dd4tick;}

void newDelay(int ms);
double getFreq(int key);
long readInt(File file);

File midiFile;

int channelOccupyNote[BUZZERS];

Tone notePlayer[BUZZERS];

void setup() {
  Serial.begin(9600);
  if(!SD.begin(4))
  {
    Serial.println("Init. failed!");
    while(true) continue;
  }
  Serial.println("Init. Done!");
  midiFile=SD.open(FILENAME);
  if(!midiFile)
  {
    Serial.println("File read err.");
    while(true) continue;
  }

  for(int t=0;t<BUZZERS;t++)
    notePlayer[t].begin(BUZZERARRAY[t]);
  
  
  long nowTime=0;
  long nowCmdNote=readInt(midiFile);
  long nowCmdTime=readInt(midiFile)*TIMEMULTIPLYER;
  long nowCmdVelo=readInt(midiFile);
//  Serial.print("Next operation(Note,Time,Velo)=");Serial.print(nowCmdNote);Serial.print(" ");Serial.print(nowCmdTime);Serial.print(" ");Serial.println(nowCmdVelo);

  while(midiFile.available())
  {
//    Serial.print("NowTime=");Serial.println(nowTime);
    while(nowCmdTime<=nowTime)
    {
      if(nowCmdNote>0 && nowCmdNote<=88)
      {
        if(nowCmdVelo==0)
        {
          bool isStop=false;
          for(int t=0;t<BUZZERS && !isStop;t++)
          {
            if(channelOccupyNote[t]==nowCmdNote)
            {
//              Serial.print("Note ");Serial.print(nowCmdNote);Serial.print(" on ");Serial.print(t);Serial.println(" channel Stopped.");
              notePlayer[t].stop();
              channelOccupyNote[t]=0;
              isStop=true;
            }
          }
        }
        else
        {
          bool isPlayed=false;
          for(int t=0;t<BUZZERS && !isPlayed;t++)
          {
            if(channelOccupyNote[t]==0)
            {
              isPlayed=true;
              notePlayer[t].play(getFreq(nowCmdNote));
              channelOccupyNote[t]=nowCmdNote;
//              Serial.print("Note ");Serial.print(nowCmdNote);Serial.print(" playing on ");Serial.print(t);Serial.println(" channel.");
            }
          }
          if(!isPlayed)
          {
            Serial.print("Lack of buzzers to play note ");Serial.print(nowCmdNote);Serial.println("!");
          }
        }
      }
      nowCmdNote=readInt(midiFile),nowCmdTime=readInt(midiFile)*TIMEMULTIPLYER,nowCmdVelo=readInt(midiFile);
//      Serial.print("Next operation(Note,Time,Velo)=");Serial.print(nowCmdNote);Serial.print(" ");Serial.print(nowCmdTime);Serial.print(" ");Serial.println(nowCmdVelo);
    }
     newDelay(20);
     nowTime+=20;
  }
  
  
  midiFile.close();
}

void loop() {
  // put your main code here, to run repeatedly:

}

double getFreq(int key)
{
  switch(key)
  {
    case 1:
      return 27.500000;
    case 2:
      return 29.135235;
    case 3:
      return 30.867706;
    case 4:
      return 32.703196;
    case 5:
      return 34.647829;
    case 6:
      return 36.708096;
    case 7:
      return 38.890873;
    case 8:
      return 41.203445;
    case 9:
      return 43.653529;
    case 10:
      return 46.249303;
    case 11:
      return 48.999429;
    case 12:
      return 51.913087;
    case 13:
      return 55.000000;
    case 14:
      return 58.270470;
    case 15:
      return 61.735413;
    case 16:
      return 65.406391;
    case 17:
      return 69.295658;
    case 18:
      return 73.416192;
    case 19:
      return 77.781746;
    case 20:
      return 82.406889;
    case 21:
      return 87.307058;
    case 22:
      return 92.498606;
    case 23:
      return 97.998859;
    case 24:
      return 103.826174;
    case 25:
      return 110.000000;
    case 26:
      return 116.540940;
    case 27:
      return 123.470825;
    case 28:
      return 130.812783;
    case 29:
      return 138.591315;
    case 30:
      return 146.832384;
    case 31:
      return 155.563492;
    case 32:
      return 164.813778;
    case 33:
      return 174.614116;
    case 34:
      return 184.997211;
    case 35:
      return 195.997718;
    case 36:
      return 207.652349;
    case 37:
      return 220.000000;
    case 38:
      return 233.081881;
    case 39:
      return 246.941651;
    case 40:
      return 261.625565;
    case 41:
      return 277.182631;
    case 42:
      return 293.664768;
    case 43:
      return 311.126984;
    case 44:
      return 329.627557;
    case 45:
      return 349.228231;
    case 46:
      return 369.994423;
    case 47:
      return 391.995436;
    case 48:
      return 415.304698;
    case 49:
      return 440.000000;
    case 50:
      return 466.163762;
    case 51:
      return 493.883301;
    case 52:
      return 523.251131;
    case 53:
      return 554.365262;
    case 54:
      return 587.329536;
    case 55:
      return 622.253967;
    case 56:
      return 659.255114;
    case 57:
      return 698.456463;
    case 58:
      return 739.988845;
    case 59:
      return 783.990872;
    case 60:
      return 830.609395;
    case 61:
      return 880.000000;
    case 62:
      return 932.327523;
    case 63:
      return 987.766603;
    case 64:
      return 1046.502261;
    case 65:
      return 1108.730524;
    case 66:
      return 1174.659072;
    case 67:
      return 1244.507935;
    case 68:
      return 1318.510228;
    case 69:
      return 1396.912926;
    case 70:
      return 1479.977691;
    case 71:
      return 1567.981744;
    case 72:
      return 1661.218790;
    case 73:
      return 1760.000000;
    case 74:
      return 1864.655046;
    case 75:
      return 1975.533205;
    case 76:
      return 2093.004522;
    case 77:
      return 2217.461048;
    case 78:
      return 2349.318143;
    case 79:
      return 2489.015870;
    case 80:
      return 2637.020455;
    case 81:
      return 2793.825851;
    case 82:
      return 2959.955382;
    case 83:
      return 3135.963488;
    case 84:
      return 3322.437581;
    case 85:
      return 3520.000000;
    case 86:
      return 3729.310092;
    case 87:
      return 3951.066410;
    case 88:
      return 4186.009045;
  } 
  /*
   * Generating Code (C++) for this function.
        #include<cstdio>
        #include<cmath>
        int main()
        {
         double v=27.500;
          double k=pow(2,1.0/12.0);
          for(int i=1;i<=88;i++)
          {
            printf("    case %d:\n      return %lf;\n",i,v);
            v*=k;
          }
        }
   */
}

long readInt(File file)
{
  long ch=0,res=0;
  while(ch<'0' || ch>'9') ch=file.read();
  while(ch>='0' && ch<='9')
  {
    res=res*10+ch-'0';
    ch=file.read();
  }
  return res;
}



void newDelay(int ms)
{
  for(int t=0;t<ms;t++)
  {
    for(int j=0;j<1000;j++)
    {
      delayOneUs();
    }
  }
}
