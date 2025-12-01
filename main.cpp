#include "FEHLCD.h"
#include "FEHUtility.h"

void MainMenu();


void MainMenu() {
    int x1 = 130, y1 = 50;
    int x2 = 50, y2 = 100;
    int x3 = 0, y3 = 0;
    int x4 = 0, y4 = 0;
    int width = 60, height = 30;


    // Draw Play button
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x1, y1, width, height);
    LCD.WriteAt("PLAY", x1+5, y1);



    LCD.Update();

    
}

int main() {
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    MainMenu();

    while (1) {
        LCD.Update();
        // Never end
    }
    return 0;
}