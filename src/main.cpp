#include <Arduino.h>

/*Board connections
  esp12e   Encoder
  3v3      Vcc
  Gnd      Gnd
  D2       CLK
  D3       DT
  Tested on D0,D1 and D6,D7 
  All GPIO can be used except D16  */

#define CLK D2
#define DT D3
#define MAX_COUNT 20
#define MIN_COUNT 0

volatile int intCount = MIN_COUNT;

void ICACHE_RAM_ATTR myISR()
{
  cli(); //disable interupts
  if (!digitalRead(DT))
    intCount = intCount + (intCount < MAX_COUNT);
  else
    intCount = intCount - (intCount > MIN_COUNT);
  Serial.print(intCount);
  Serial.print(":");
  sei(); //enable interupts
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting, count limited 0-20");
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLK), myISR, RISING);
}

void loop()
{
}
