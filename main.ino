#include <Servo.h>
#include <Keypad.h>

Servo ServoMotor;
const String password = "425";  // change the password here, just pick any 3 numbers
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 8, 7, 6, 9 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int RedpinLock = 13;
int GreenpinUnlock = 10;

void setup()
{
  Serial.begin(9600);
pinMode(RedpinLock, OUTPUT);
pinMode(GreenpinUnlock, OUTPUT);
ServoMotor.attach(12);
LockedPosition(true);
}

void loop()
{
char key = keypad.getKey();
//Serial.print(key);
if (key == '*' || key == '#')
{
 
position = 0;
LockedPosition(true);
}
if (key == password[position])
{
position ++;
}
if (position == 3)
{
LockedPosition(false);
}
delay(100);
}
void LockedPosition(int locked)
{
if (locked)
{
digitalWrite(RedpinLock, HIGH);
digitalWrite(GreenpinUnlock, LOW);
ServoMotor.write(12);
}
else
{
digitalWrite(RedpinLock, LOW);
digitalWrite(GreenpinUnlock, HIGH);
ServoMotor.write(100);
}
}
