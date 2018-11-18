#include <FPS_GT511C3.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//Define variables 
#define I2C_ADDR           0x27
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

// connect fps to RX (0) and TX (1)
FPS_GT511C3 fps(0, 1);

// initialize lcd with serial
LiquidCrystal_I2C lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {

    // initialize fps
    fps.Open();
    bool deleted = fps.DeleteAll();

    // initialize lcd
    lcd.begin (16,2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.setBacklight(HIGH);

    if (deleted)
    {
        lcdPrint("All IDs Deleted");
    }
    else
    {
        lcdPrint("Nothing to Delete");
    }
}

void lcdPrint(String line)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(line.substring(16));
}

void loop() 
{
  
}
