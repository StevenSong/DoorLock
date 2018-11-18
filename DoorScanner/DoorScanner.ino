#include <FPS_GT511C3.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define I2C_ADDR           0x27
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

#define BUTTON  8
#define SERVO   10
#define TIMEOUT 4000
#define MAXIDS  20

#define STEVEN 0
#define JONAH  1

// connect fps to RX (0) and TX (1)
FPS_GT511C3 fps(0, 1);

// connect lcd with serial
LiquidCrystal_I2C lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// create servo
Servo servo;

void setup() {

    // initialize fps
    fps.Open();

    // initialize lcd
    lcd.begin (16,2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);

    // initialize servo
    servo.attach(SERVO);
    servo.write(0);

    // initialize button
    pinMode(BUTTON, INPUT);
}

int reading;
int previous;

bool isOn = false;

void loop()
{
    reading = digitalRead(BUTTON);
  
    if (reading == HIGH && previous == LOW)
    {
        isOn = true;
    }

    if (isOn)
    {
        for (int i = 0; i < TIMEOUT; i++)
        {
            if (i == 0)
            {
                lcd.setBacklight(HIGH);
                fps.SetLED(true);
                
                lcdPrint("Press Finger");
            }

            if (fps.IsPressFinger())
            {
                fps.CaptureFinger(false);
                int id = fps.Identify1_N();

                // if finger matches stored finger
                if (id < MAXIDS)
                {
                    String welcome = "Welcome ";
                    if (id == STEVEN)
                    {
                        welcome += "Steven";
                    }
                    else if (id == JONAH)
                    {
                        welcome += "Jonah";
                    }

                    lcdPrint(welcome);
                    servo.write(90);
                    delay(5000);
                    break;
                }
                else
                {
                    lcdPrint("Nope");
                    delay(5000);
                    break;
                }
            }

            delay(1);
        }

        lcd.setBacklight(LOW);
        fps.SetLED(false);
        
        isOn = false;
    }
    
    previous = reading;
}

void lcdPrint(String line)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(line.substring(16));
}
