#include <Arduino.h>

//DRIVER RIGHT WHEEL(1)
#define R_IS 4
#define L_IS 7

#define R_EN1 5
#define R_PWM1 6
#define L_EN1 8
#define L_PWM1 9

//DRIVER LEFT WHEEL(2)
#define R_EN2 12
#define R_PWM2 10
#define L_EN2 13
#define L_PWM2 11

// ENCODER RIGHT WHEEL(1)
#define phaseA1 2
#define phaseB1 1

// ENCODER LEFT WHEEL(2)
#define phaseA2 3
#define phaseB2 0

//read encoder pulse
long pos1 = 0;
long pos2 = 0;

void count1()
{
    if (digitalRead(phaseB1) == LOW)
    {
        pos1++;
    }
    else
    {
        pos1--;
    }
}
void count2()
{
    if (digitalRead(phaseB2) == HIGH)
    {
        pos2++;
    }
    else
    {
        pos2--;
    }
}
void motorOn()
{
    digitalWrite(R_EN1, HIGH);
    digitalWrite(L_EN1, HIGH);
    digitalWrite(R_EN2, HIGH);
    digitalWrite(L_EN2, HIGH);
}
void motorOff()
{
    digitalWrite(R_EN1, LOW);
    digitalWrite(L_EN1, LOW);
    digitalWrite(R_EN2, LOW);
    digitalWrite(L_EN2, LOW);
}

void goforward(int cm)
{
    /*encoder 600pulse, wheel diameter 10cm */
    long pulse = (cm * 600)/31.4;
    motorOn();
    //go forward (75% PWM)
    while(pos1 <= pulse)
    {
        analogWrite(R_PWM1, 190);
        analogWrite(L_PWM1, 0);
        analogWrite(R_PWM2, 0);
        analogWrite(L_PWM2, 190);
        delay(20);
    }
    pos1 = 0;
    motorOff();
}
void gobackward(int cm)
{
    long pulse = -(cm * 600)/31.4;
    motorOn();
    while (pos1 >= pulse)
    {
      //go backward (75% PWM)
      analogWrite(R_PWM1, 0);
      analogWrite(L_PWM1, 190);
      analogWrite(R_PWM2, 190);
      analogWrite(L_PWM2, 0);
      delay(20);
    }
    pos1 = 0;
    motorOff();
}
void turnright()
{
    pos2 = 0;
    digitalWrite(R_EN1, LOW);
    digitalWrite(L_EN1, LOW);
    digitalWrite(R_EN2, HIGH);
    digitalWrite(L_EN2, HIGH);
    while (pos2 < 900)
    {
        analogWrite(R_PWM1, 0);
        analogWrite(L_PWM1, 190);
    }
    pos2 = 0;
    motorOff();
}

void turnleft()
{
    pos1 = 0;
    digitalWrite(R_EN1, HIGH);
    digitalWrite(L_EN1, HIGH);
    digitalWrite(R_EN2, LOW);
    digitalWrite(L_EN2, LOW);
    while(pos1 < 900)
    {
        analogWrite(R_PWM1, 190);
        analogWrite(L_PWM1, 0);
    }
    pos1 = 0;
    motorOff();
}

void setup()
{
    Serial.begin(115200);
    pinMode(R_IS, OUTPUT);
    pinMode(L_IS, OUTPUT);
    digitalWrite(R_IS, LOW);
    digitalWrite(L_IS, LOW);

    pinMode(R_EN1, OUTPUT);
    pinMode(L_EN1, OUTPUT);
    pinMode(R_PWM1, OUTPUT);
    pinMode(L_PWM1, OUTPUT);
    digitalWrite(R_EN1, HIGH);
    digitalWrite(L_EN1, HIGH);

    pinMode(R_EN2, OUTPUT);
    pinMode(L_EN2, OUTPUT);
    pinMode(R_PWM2, OUTPUT);
    pinMode(L_PWM2, OUTPUT);
    digitalWrite(R_EN2, HIGH);
    digitalWrite(L_EN2, HIGH);

    //interrupt 0 is pin 2
    attachInterrupt(0, count1, FALLING);
    pinMode(phaseA1, INPUT_PULLUP);
    pinMode(phaseB1, INPUT_PULLUP);
    //interrupt 1 is pin 3
    attachInterrupt(1, count2, FALLING);
    pinMode(phaseA2, INPUT_PULLUP);
    pinMode(phaseB2, INPUT_PULLUP);
}

void loop()
{
  //run into a square
    for (int i = 0; i < 4; i++)
    {
        goforward(200);
        turnleft();
    }
    delay(10000);
}
