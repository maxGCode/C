/*

PINOUT:

RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V

*
Test
* Include the standard Arduino SPI library *
#include <SPI.h>
/* Include the RFID library */
#include "RFID.h"

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 9
#define RESET_DIO 8
int productname[5]={83,18,37,75,24};
int product[5]={100,120,230,125,70};
int token[5]={0,0,0,0,0};
int Total;
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 

void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  pinMode(2,OUTPUT);
}

void loop()
{
  /* Temporary loop counter */
  byte i=0;
  byte j=0;
  byte k=0;
  int ID;
  bool ledSet = LOW;

  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    //Serial.print(RC522.serNum[i],DEC);

    

    /* Output the serial number to the UART */
    int ID=RC522.serNum[0];
    Serial.println("Card detected:");
    Serial.println(RC522.serNum[0],DEC);  
    //Serial.print(" " + ID);
    //Serial.println(" ");
    for(i=0;i<5;i++)
    {
      if(productname[i]==ID)
      {
        digitalWrite(2,!digitalRead(2));
        
        Serial.println("Total Purchase");
        if(token[i]==0)
        {
          Total=Total+product[i];
          token[i]=1;
        }
        else
        {
          Total=Total-product[i];
          token[i]=0;
        }
        
        Serial.println(Total);
        break;
      }
      else if(i==5)
      { 
        Serial.println("Access Denied"); 
        break;
      }
    }
    Serial.println();
    Serial.println();
  }
  delay(1000);
}
