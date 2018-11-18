#include <FPS_GT511C3.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR           0x27
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

#define MAXIDS 20

// connect fps to RX (0) and TX (1)
FPS_GT511C3 fps(0, 1);

// initialize lcd with serial
LiquidCrystal_I2C lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  
    // initialize fps
    fps.Open();
    fps.SetLED(true);

    // initialize lcd
    lcd.begin (16,2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.setBacklight(HIGH);

    Enroll();
}

void Enroll()
{
    // find open ID
    int enrollID;
    for (enrollID = 0; enrollID < MAXIDS; enrollID++)
    {
        if (!fps.CheckEnrolled(enrollID))
        {
            break;
        }
        else if (enrollID == MAXIDS - 1)
        {
            lcdPrint("All IDs Used");
            return;
        }
    }
    
    fps.EnrollStart(enrollID);
  
    // enroll
    lcdPrint("Press Finger");
    
    while(fps.IsPressFinger() == false) delay(100);
    bool bret = fps.CaptureFinger(true);
    int iret = 0;
    if (bret != false)
    {
        lcdPrint("Remove finger");
        fps.Enroll1(); 
        while(fps.IsPressFinger() == true) delay(100);
        lcdPrint("Press finger again");
        while(fps.IsPressFinger() == false) delay(100);
        bret = fps.CaptureFinger(true);
        if (bret != false)
        {
            lcdPrint("Remove finger");
            fps.Enroll2();
            while(fps.IsPressFinger() == true) delay(100);
            lcdPrint("Press finger again");
            while(fps.IsPressFinger() == false) delay(100);
            bret = fps.CaptureFinger(true);
            if (bret != false)
            {
                lcdPrint("Remove finger");
                iret = fps.Enroll3();
                if (iret == 0)
                {
                    lcdPrint("Enrolled: " + String(enrollID));
                }
                else
                {
                    lcdPrint("Failed: " + String(iret));
                }
            }
            else lcdPrint("Failed to capture third finger");
        }
        else lcdPrint("Failed to capture second finger");
    }
    else lcdPrint("Failed to capture first finger");
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
