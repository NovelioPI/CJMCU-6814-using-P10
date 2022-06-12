#include <LedMatrix.hpp>
#include <fonts/Droid_Sans_12.h>

SoftDMD dmd(WIDTH,1);  // DMD controls the entire display

void matrix_init()
{
    dmd.setBrightness(255);
    dmd.selectFont(Droid_Sans_12);
    dmd.begin();
}

void matrix_display(float co, float nh3, float no2)
{
    String text1 = String(co/1.0);
    String text2 = String(nh3/1.0);
    String text3 = String(no2/1.0);

    dmd.drawString(0, 3, text1);
    dmd.drawString(32, 3, text2);
    dmd.drawString(64, 3, text3);
    delay(1000);
    dmd.clearScreen();
}