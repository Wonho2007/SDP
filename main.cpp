#include "FEHLCD.h"
#include "FEHUtility.h"

void MainMenu();
void SwitchScreen(int);

//Function to switch the screen.
void SwitchScreen(int screen)
{
    int questionsAnswered = 0;
    int x1 = 170, y1 = 20, width = 120, height = 30;
    int touchx, touchy;
    bool keepTrackingClicks = true;

    if (screen == 1)
    {
        //Clear screen
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        //Gameplay
        LCD.WriteAt("Play game here", 90, 80);
        LCD.Update();

        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();

        //Check if player clicks main menu button
        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu();
                keepTrackingClicks = false;
            }
        }

    } else if (screen ==2)
    {
        // Clear background
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        //Write statistics
        LCD.WriteAt("Statistics:", 100, 60);
        LCD.WriteAt("Questions Answered:", 55, 90);
        LCD.WriteAt(questionsAnswered, 150, 115);

        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();

        //Check if player clicks main menu button
        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu();
                keepTrackingClicks = false;
            }
        }

    } else if (screen ==3)
    {
        // Clear background
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();

        //Write statistics
        LCD.SetFontScale(0.5);
        LCD.WriteAt("Instructions:", 120, 60);
        LCD.WriteAt("When a question appears", 90, 90); 
        LCD.WriteAt("use the arrows to move", 90, 120);
        LCD.WriteAt("the car to the lane", 100, 150);
        LCD.WriteAt("with the correct answer!", 85, 180);

        

        //Check if player clicks main menu button
        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu();
                keepTrackingClicks = false;
            }
        }

    } else if (screen ==4)
    {
        // Clear background
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();

        //Write credits
        LCD.SetFontScale(1);
        LCD.WriteAt("Creators:", 106, 60);
        LCD.WriteAt("Wonho Lee", 110, 90); 
        LCD.WriteAt("Ashlea Budzinski", 60, 120);

        

        //Check if player clicks main menu button
        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu();
                keepTrackingClicks = false;
            }
        }

    }


}

void MainMenu() {
    int x1 = 130, y1 = 30;
    int x2 = 65, y2 = 70;
    int x3 = 75, y3 = 110;
    int x4 = 110, y4 = 150;
    int width = 60, height = 30;
    int width2 = 190, height2 = 30;
    int width3 = 170, height3 = 30;
    int width4 = 100, height4 = 30;
    int touchx, touchy;
    bool keepTrackingClicks = true;

    //Clear screen
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    // Draw Play button
    LCD.SetFontScale(1);
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x1, y1, width, height);
    LCD.WriteAt("PLAY", x1+5, y1+5);

    // Draw Statistics button
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x2, y2, width2, height2);
    LCD.WriteAt("VIEW STATISTICS", x2+5, y2+5);

    // Draw Instructions button
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x3, y3, width3, height3);
    LCD.WriteAt("INSTRUCTIONS", x3+12, y3+5);

    // Draw Credits button
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x4, y4, width4, height4);
    LCD.WriteAt("CREDITS", x4+7, y4+5);


    LCD.Update();

    //See where the player clicks and move to the corresponding screen
    while (keepTrackingClicks)
    {
        while(!LCD.Touch(&touchx, &touchy)){}
        while(LCD.Touch(&touchx, &touchy)){}


        if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
        {
            SwitchScreen(1);
            keepTrackingClicks = false;
        } else if (touchx < x2+width2 && touchx > x2 && touchy > y2 && touchy < y2+height2)
        {
            SwitchScreen(2);
            keepTrackingClicks = false;
        } else if (touchx < x3+width3 && touchx > x3 && touchy > y3 && touchy < y3+height3)
        {
            SwitchScreen(3);
            keepTrackingClicks = false;
        } else if (touchx < x4+width4 && touchx > x4 && touchy > y4 && touchy < y4+height4)
        {
            SwitchScreen(4);
            keepTrackingClicks = false;
        }
    }


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