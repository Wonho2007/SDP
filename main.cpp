//320 x 240
//lane1x=30, lane2x=70, lane3x=110
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHRandom.h"
#include "FEHImages.h"

void MainMenu();
void StartGame(int);
void SwitchScreen(int);
void MoveLeft(int *);
void MoveRight(int *);

class question
{
public:
    int level;
    int num1;
    int num2;
    int response;
    int answer;


    question(int = 1, int = 0, int = 0, int = 0, int = 0);
    void random();
};

//Function to move car left
void MoveLeft(int *xptr){
    int carx=*xptr, lane1x=30, lane2x=70, lane3x=110, cary=160;
    FEHImage car("car.png");

    if (carx>=70){
        LCD.SetFontColor(BLACK);
        LCD.FillRectangle(carx, cary, 25, 45); // Draw over old car
        LCD.FillRectangle(170, 202, 115, 38);
        LCD.Update();
        carx-=40;
        *xptr-=40;
        car.Draw(carx, cary);
        LCD.Update();
    } else {
        LCD.SetFontColor(WHITE);
        LCD.SetFontScale(0.75);
        LCD.WriteAt("Already in", 180, 202);
        LCD.WriteAt("left lane!", 180, 217);
    }

}

//Function to move car right
void MoveRight(int *xptr){
    int carx=*xptr, cary=160;
    FEHImage car("car.png");

    if (carx<=70){
        LCD.SetFontColor(BLACK);
        LCD.FillRectangle(carx, cary, 25, 45); // Draw over old car
        LCD.FillRectangle(170, 202, 115, 38);
        LCD.Update();
        carx+=40;
        *xptr+=40;
        car.Draw(carx, cary);
        LCD.Update();
    } else {
        LCD.SetFontColor(WHITE);
        LCD.SetFontScale(0.75);
        LCD.WriteAt("Already in", 180, 202);
        LCD.WriteAt("right lane!", 179, 217);
    }
}


//Function to start game
void StartGame(int level)
{
    //Clear screen
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    if (level == 1)
    {
        int questionsAnswered = 0;
        int x1 = 170, y1 = 20, width = 120, height = 30;
        int touchx, touchy;
        bool keepTrackingClicks = true;


        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();

        //Draw arrow buttons
        int rectX=175, rectY=170, rectW=105, rectH=30, lineX=227;
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(rectX, rectY, rectW, rectH);
        LCD.DrawLine(lineX, 170, lineX, 199);
        LCD.WriteAt("<--", 178, 175);
        LCD.WriteAt("-->", 238, 175);
        LCD.Update();

        question levelOne(1);
        //Generate a random question
        levelOne.random();
        
        //Import car image and draw
        FEHImage car("car.png");
        int carx=70, cary=160, *xptr=&carx;
        car.Draw(carx, cary);
        LCD.Update();

        //Draw road lines
        LCD.DrawLine(160, 0, 160, 240);
        LCD.DrawLine(20, 0, 20, 240);
        LCD.DrawLine(140, 0, 140, 240);
        LCD.DrawLine(60, 0, 60, 240);
        LCD.DrawLine(100, 0, 100, 240);


        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu();
                keepTrackingClicks = false;
            } else if (touchx < rectX+(rectW/2) && touchx > rectX && touchy > rectY && touchy < rectY+rectH){
                //Move car left
                MoveLeft(xptr);
            } else if (touchx < rectX+rectW && touchx > rectX+(rectW/2) && touchy > rectY && touchy < rectY+rectH){
                //Move car right
                MoveRight(xptr);
            }
        }
    } else if (level == 2)
    {

        int questionsAnswered = 0;
        int x1 = 170, y1 = 20, width = 120, height = 30;
        int touchx, touchy;
        bool keepTrackingClicks = true;


        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();

        //Draw arrow buttons
        int rectX=175, rectY=170, rectW=105, rectH=30, lineX=227;
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(rectX, rectY, rectW, rectH);
        LCD.DrawLine(lineX, 170, lineX, 199);
        LCD.WriteAt("<--", 178, 175);
        LCD.WriteAt("-->", 238, 175);
        LCD.Update();


        question levelTwo(2);
        //Generate a random question
        levelTwo.random();
        //Import car image and draw
        FEHImage car("car.png");
        car.Draw(50, 120);
        LCD.Update();


        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu();
                keepTrackingClicks = false;
            } else if (touchx < rectX+(rectW/2) && touchx > rectX && touchy > rectY && touchy < rectY+rectH){
                //Move car left
                LCD.WriteAt("left", touchx, touchy);
                
            } else if (touchx < rectX+rectW && touchx > rectX+(rectW/2) && touchy > rectY && touchy < rectY+rectH){
                //Move car right
                LCD.WriteAt("right", touchx, touchy);
            }
        }

    } else if (level ==3)
    {
        int questionsAnswered = 0;
        int x1 = 170, y1 = 20, width = 120, height = 30;
        int touchx, touchy;
        bool keepTrackingClicks = true;


        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();

        //Draw arrow buttons
        int rectX=175, rectY=170, rectW=105, rectH=30, lineX=227;
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(rectX, rectY, rectW, rectH);
        LCD.DrawLine(lineX, 170, lineX, 199);
        LCD.WriteAt("<--", 178, 175);
        LCD.WriteAt("-->", 238, 175);
        LCD.Update();




        question levelThree(3);
        //Generate a random question
        levelThree.random();
        //Import car image and draw
        FEHImage car("car.png");
        car.Draw(50, 120);
        LCD.Update();


        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu();
                keepTrackingClicks = false;
            } else if (touchx < rectX+(rectW/2) && touchx > rectX && touchy > rectY && touchy < rectY+rectH){
                //Move car left
                LCD.WriteAt("left", touchx, touchy);
                
            } else if (touchx < rectX+rectW && touchx > rectX+(rectW/2) && touchy > rectY && touchy < rectY+rectH){
                //Move car right
                LCD.WriteAt("right", touchx, touchy);
            }
        }


    }


}

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

        // Draw Main Menu button
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(x1, y1, width, height);
        LCD.WriteAt("Main Menu", x1+5, y1+5);
        LCD.Update();


        // Draw Difficulty buttons
        int levelButtonx = 110, levelButtony = 60, levelButtonWidth = 100, levelButtonHeight = 30;
        int levelButtony2 = levelButtony+40;
        int levelButtony3 = levelButtony2+40; 

        LCD.SetFontScale(1);
        LCD.SetFontColor(RED);
        LCD.DrawRectangle(levelButtonx, levelButtony, levelButtonWidth, levelButtonHeight);
        LCD.WriteAt("LEVEL 1", levelButtonx+5, levelButtony+5);

        LCD.DrawRectangle(levelButtonx, levelButtony2, levelButtonWidth, levelButtonHeight);
        LCD.WriteAt("LEVEL 2", levelButtonx+5, levelButtony2+5);

        LCD.DrawRectangle(levelButtonx, levelButtony3, levelButtonWidth, levelButtonHeight);
        LCD.WriteAt("LEVEL 3", levelButtonx+5, levelButtony3+5);
        

        //Check what button the player clicks
        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {

                MainMenu();
                keepTrackingClicks = false;

            } else if (touchx < levelButtonx+levelButtonWidth && touchx > levelButtonx && touchy > levelButtony && touchy < levelButtony+levelButtonHeight)
            {
                StartGame(1);
                keepTrackingClicks = false;
            } else if (touchx < levelButtonx+levelButtonWidth && touchx > levelButtonx && touchy > levelButtony2 && touchy < levelButtony2+levelButtonHeight)
            {
                StartGame(2);
                keepTrackingClicks = false;
            } else if (touchx < levelButtonx+levelButtonWidth && touchx > levelButtonx && touchy > levelButtony3 && touchy < levelButtony3+levelButtonHeight)
            {
                StartGame(3);
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

question::question(int l, int a, int b, int x, int y)
{

    level = l;
    num1 = a;
    num2 = b;
    response = x;
    answer = y;

}

void question::random()
{
    int a;
    int b;
    int decoy1 = 0;
    int decoy2 = 0;
    int randomNumber;
    char addSub;
    num1 = 0;
    num2 = 0;
    int ansLocation;

    if (level == 1)
    {

        //Pick 2 random integers less than 100
        while (num1 == 0)
        {
            a = Random.RandInt()/200;

            if (a < 100)
            {
                num1 = a;

            }
        }

        while (num2==0)
        {
            b = Random.RandInt()/200;

            if (b < 100)
            {
                num2 = b;
            }
            
        }

        //Pick random addition or subtraction, print question
        answer = num1+num2;

        if (answer%2 != 0)
        {
            addSub = '+';
            //Write question
            LCD.SetFontScale(1);
            LCD.WriteAt(num1, 120, 15);
            LCD.WriteAt(addSub, 150, 15);
            LCD.WriteAt(num2, 170, 15);

        } else
        {
            addSub = '-';
            if (num1 >= num2)
            {

            answer = num1 - num2;
            //Write question
            LCD.SetFontScale(1);
            LCD.WriteAt(num1, 120, 15);
            LCD.WriteAt(addSub, 150, 15);
            LCD.WriteAt(num2, 170, 15);

            } else
            {

                answer = num2 - num1;
                //Write question
                LCD.SetFontScale(1);
                LCD.WriteAt(num2, 120, 15);
                LCD.WriteAt(addSub, 150, 15);
                LCD.WriteAt(num1, 170, 15);

            }
        }

        //Pick random 1-3 gate that the answer falls through.
        while (decoy2 == 0)
        {
            randomNumber = Random.RandInt()/200;

            if (randomNumber > 10 && randomNumber < 15)
            {
                //Draw true answer in first box.
                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(answer, 50+5, 40+5);
                ansLocation=50; //Store answer location


                //Draw decoy answer
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(decoy1, 130+5, 40+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 > 0)
                {
                    LCD.DrawRectangle(210, 40, 50, 30);
                    LCD.WriteAt(decoy2, 210+5, 40+5);
                } else
                {
                    decoy2 = answer + randomNumber + 5;
                    LCD.DrawRectangle(210, 40, 50, 30);
                    LCD.WriteAt(decoy2, 210+5, 40+5);
                }

            } else if (randomNumber > 15 && randomNumber < 20)
            {
                //Draw true answer in second box.
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(answer, 130+5, 40+5);
                ansLocation=130; //Store answer location


                //Draw decoy answer
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(decoy1, 50+5, 40+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 > 0)
                {
                    LCD.DrawRectangle(210, 40, 50, 30);
                    LCD.WriteAt(decoy2, 210+5, 40+5);
                } else
                {
                    decoy2 = answer + randomNumber + 5;
                    LCD.DrawRectangle(210, 40, 50, 30);
                    LCD.WriteAt(decoy2, 210+5, 40+5);
                }

            } else if (randomNumber > 20 && randomNumber < 25)
            {
                //Draw true answer in third box.
                LCD.DrawRectangle(210, 40, 50, 30);
                LCD.WriteAt(answer, 210+5, 40+5);
                ansLocation=210; //Store answer location


                //Draw decoy answer
                decoy1 = (a + b + randomNumber) * 6.0/7.0 ;
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(decoy1, 130+5, 40+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 > 0)
                {
                    LCD.DrawRectangle(50, 40, 50, 30);
                    LCD.WriteAt(decoy2, 50+5, 40+5);
                } else
                {
                    decoy2 = answer + randomNumber + 5;
                    LCD.DrawRectangle(50, 40, 50, 30);
                    LCD.WriteAt(decoy2, 50+5, 40+5);
                }

            }



        }

        



    } else if (level == 2)
    {

        //Pick 2 random integers less than 100
        while (num1 == 0)
        {
            a = Random.RandInt()/200;

            if (a <= 12 && a >= 2)
            {
                num1 = a;

            }
        }

        while (num2==0)
        {
            b = Random.RandInt()/200;

            if (b <= 12 && b >= 2)
            {
                num2 = b;
            }
            
        }

        //Pick random division, print question
        answer = num1 * num2;

        addSub = '+';
        //Write question
        LCD.SetFontScale(1);
        LCD.WriteAt(num1, 120, 15);
        LCD.WriteAt('X', 150, 15);
        LCD.WriteAt(num2, 170, 15);

    
        //Pick random 1-3 gate that the answer falls through.
        while (decoy2 == 0)
        {
            randomNumber = Random.RandInt()/200;

            if (randomNumber > 10 && randomNumber < 15)
            {
                //Draw true answer in first box.
                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(answer, 50+5, 40+5);


                //Draw decoy answer
                decoy1 = Random.RandInt();

                if (decoy1%2 == 0)
                {
                    decoy1 = answer-a;
                } else 
                {
                    decoy1 = answer+a;
                }

                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(decoy1, 130+5, 40+5);

                //Draw decoy answer
                if (randomNumber%2 == 0)
                {
                    decoy2 = answer-b;
                } else 
                {
                    decoy2 = answer+b;
                }
                
            
                LCD.DrawRectangle(210, 40, 50, 30);
                LCD.WriteAt(decoy2, 210+5, 40+5);
                

            } else if (randomNumber > 15 && randomNumber < 20)
            {
                //Draw true answer in second box.
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(answer, 130+5, 40+5);


                //Draw decoy answer
                decoy1 = ((a-1) * (b+1));
                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(decoy1, 50+5, 40+5);

                //Draw decoy answer
                if (randomNumber%2 == 0)
                {
                    decoy2 = answer-b;
                } else 
                {
                    decoy2 = answer+b;
                }
                
            
                LCD.DrawRectangle(210, 40, 50, 30);
                LCD.WriteAt(decoy2, 210+5, 40+5);

            } else if (randomNumber > 20 && randomNumber < 25)
            {
                //Draw true answer in third box.
                LCD.DrawRectangle(210, 40, 50, 30);
                LCD.WriteAt(answer, 210+5, 40+5);


                //Draw decoy answer
                decoy1 = ((a-1) * (b+1));
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(decoy1, 130+5, 40+5);

                //Draw decoy answer
                if (randomNumber%2 == 0)
                {
                    decoy2 = answer-b;
                } else 
                {
                    decoy2 = answer+b;
                }
                
            
                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(decoy2, 50+5, 40+5);

            }



        }

        



    } else if (level == 3)
    {
        int c = 0;
        int num3 = 0;

        //Pick 2 random integers between 2 and 12 and an integer less than 100
        while (num1 == 0)
        {
            a = Random.RandInt()/200;

            if (a <= 12 && a >= 2)
            {
                num1 = a;

            }
        }

        while (num2==0)
        {
            b = Random.RandInt()/200;

            if (b <= 12 && b >= 2)
            {
                num2 = b;
            }
            
        }


        while (num3 == 0)
        {
            c = Random.RandInt()/200;

            if (c < 100)
            {
                num3 = c;
            }
        }



        answer = num1 * num2 + num3;

        //Write question
        LCD.SetFontScale(1);
        LCD.WriteAt(num1, 20, 15);
        LCD.WriteAt('X', 50, 15);
        LCD.WriteAt(num2, 80, 15);
        LCD.WriteAt('+', 110, 15);
        LCD.WriteAt(num3, 140, 15);



        //Pick random 1-3 gate that the answer falls through.
        while (decoy2 == 0)
        {
            randomNumber = Random.RandInt()/200;

            if (randomNumber > 10 && randomNumber < 15)
            {
                //Draw true answer in first box.
                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(answer, 50+5, 40+5);


                //Draw decoy answer
                c = Random.RandInt();
                if (c%2 == 0)
                {
                    decoy1 = answer-a;
                } else 
                {
                    decoy1 = answer+a;
                }

               
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(decoy1, 130+5, 40+5);

                //Draw decoy answer
                if (randomNumber%2 == 0)
                {
                    decoy2 = answer-b;
                } else 
                {
                    decoy2 = answer+b;
                }
                
            
                LCD.DrawRectangle(210, 40, 50, 30);
                LCD.WriteAt(decoy2, 210+5, 40+5);
                

            } else if (randomNumber > 15 && randomNumber < 20)
            {
                //Draw true answer in second box.
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(answer, 130+5, 40+5);


                //Draw decoy answer
                c = Random.RandInt();
                if (c%2 == 0)
                {
                    decoy1 = answer-a;
                } else 
                {
                    decoy1 = answer+a;
                }

                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(decoy1, 50+5, 40+5);

                //Draw decoy answer
                if (randomNumber%2 == 0)
                {
                    decoy2 = answer-b;
                } else 
                {
                    decoy2 = answer+b;
                }
                
            
                LCD.DrawRectangle(210, 40, 50, 30);
                LCD.WriteAt(decoy2, 210+5, 40+5);

            } else if (randomNumber > 20 && randomNumber < 25)
            {
                //Draw true answer in third box.
                LCD.DrawRectangle(210, 40, 50, 30);
                LCD.WriteAt(answer, 210+5, 40+5);


                //Draw decoy answer
                c = Random.RandInt();
                if (c%2 == 0)
                {
                    decoy1 = answer-a;
                } else 
                {
                    decoy1 = answer+a;
                }
                
                LCD.DrawRectangle(130, 40, 50, 30);
                LCD.WriteAt(decoy1, 130+5, 40+5);

                //Draw decoy answer
                if (randomNumber%2 == 0)
                {
                    decoy2 = answer-b;
                } else 
                {
                    decoy2 = answer+b;
                }
                
            
                LCD.DrawRectangle(50, 40, 50, 30);
                LCD.WriteAt(decoy2, 50+5, 40+5);

            }



        }
        




    }
    
    

}