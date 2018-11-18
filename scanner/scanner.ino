#include <FPS_GT511C3.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//Define variables 
#define I2C_ADDR          0x27        //Define I2C Address where the PCF8574A is
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
    //Define the LCD as 16 column by 2 rows 
    lcd.begin (16,2);

    fps.Open();

    bool deleted = fps.DeleteAll();
    
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);

    if (deleted)
    {
        lcd.print("All IDs Deleted");
    }
    else
    {
        lcd.print("Nothing to Delete");
    }
}

void loop() 
{
    // FPS Blink LED Test
//    fps.SetLED(true); // turn on the LED inside the fps
//    delay(1000);
//    fps.SetLED(false);// turn off the LED inside the fps
//    delay(1000);
}
