#include "M5StickC.h"
#include "bugC.h"

BUGC BugC;

void setup() {
    M5.begin();
    BugC.Init();
    M5.Lcd.setTextColor(TFT_ORANGE);
    M5.Lcd.setRotation(1);
    M5.Lcd.drawCentreString("SHEYLLA  II", 79, 30, 4);
    M5.Axp.SetChargeCurrent(CURRENT_360MA);
}

void loop() {
    M5.update();
    
    BugC.BugCSetAllSpeed(-80, 80, -80, 80);
    delay(10);
    BugC.BugCSetAllSpeed(80, -80, 80, -80);
    delay(1000);
    BugC.BugCSetAllSpeed(0, 0, 0, 0);
    delay(100);
    BugC.BugCSetAllSpeed(100, -100, 100, -100);
}
