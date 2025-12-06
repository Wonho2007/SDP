//320 x 240
//lane1x=30, lane2x=70, lane3x=110
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHRandom.h"
#include "FEHImages.h"
#include "FEHSound.h"

void MainMenu(int *);
void StartGame(int, int *, int *, FEHSound);
void SwitchScreen(int, int *, FEHSound);
void MoveLeft(int *);
void MoveRight(int *);
void endScreen(int *, int *);
void cheat(int *, FEHSound);

class question
{
public:
    int level;
    int decoy1;
    int decoy2;
    int response;
    int answer;
    int correctX;

    int decoy1X;
    int decoy2X;

    int answerY;


    question(int = 1, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int=0);
    void random();
    int moveAnswers(int *);
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

//Function to show endscreen
void endScreen(int *score, int *qptr){
    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.Clear();
    LCD.SetFontScale(1); 
    LCD.WriteAt("YOU CRASHED!", 85, 180); 
    LCD.WriteAt("SCORE: ", 95, 50); 
    LCD.WriteAt(*score, 190, 50); 
    FEHImage dead ("deademoji.png"); 
    dead.Draw(100, 17);
    Sleep(1.0);
    FEHImage sad ("sademoji.png");
    sad.Draw(100, 17);
    Sleep(1.0);
    dead.Draw(100, 17);
    Sleep(1.0);
    sad.Draw(100, 17);
    Sleep(1.0);
    dead.Draw(100, 17);
    Sleep(1.0);
    MainMenu(qptr); 
}

//Function when cheating
void cheat(int *qptr, FEHSound music){
    int fail=0;

    //Stop music
    music.pause();
    FEHSound explosionSound("explosionSound.wav");
    explosionSound.restart();

    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    LCD.SetFontScale(1.5); 
    LCD.WriteAt("CHEATER!", 83, 170); 
    FEHImage mad1 ("mad1.png");
    mad1.Draw(100, 7);
    Sleep(1.0);
    FEHImage mad2 ("mad2.png");
    mad2.Draw(100, 7);
    Sleep(1.0);
    mad1.Draw(100, 7);
    Sleep(1.0);
    mad2.Draw(100, 7);
    Sleep(1.0);
    mad1.Draw(100, 7);
    Sleep(1.0);
    MainMenu(qptr); 
}


//Function to start game
void StartGame(int level, int *qptr, int *tptr, FEHSound music)
{
    //Clear screen
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    if (level == 1)
    {
       
        int x1 = 170, y1 = 20, width = 120, height = 30;
        int touchx, touchy;
        bool keepTrackingClicks = true, game = true;

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
       
        //Import car image and draw
        FEHImage car("car.png");
        int carx=70, cary=160, *xptr=&carx;
        car.Draw(carx, cary);
        LCD.Update();

        //Draw grass
        FEHImage g1 ("grass1.png");
        FEHImage g2 ("grass2.png");
        FEHImage g3 ("grass3.png");
        g3.Draw(1, 0);
        g1.Draw(140, 0);


        //Draw road lines
        LCD.DrawLine(160, 0, 160, 240);
        LCD.DrawLine(20, 0, 20, 240);
        LCD.DrawLine(1, 0, 1, 240);
        LCD.DrawLine(140, 0, 140, 240);
        LCD.DrawLine(60, 0, 60, 240);
        LCD.DrawLine(100, 0, 100, 240);

        question levelOne(1);
        //Generate a random question
        levelOne.random();

        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy))
            {
                LCD.SetFontScale(1);
                //Move options down
                int gameState = levelOne.moveAnswers(xptr);

                if (gameState == 2)
                {
                    (*tptr)++;
                    if ((*tptr)>(*qptr)){
                        (*qptr)=(*tptr);
                    }
                    StartGame(1, qptr, tptr, music);

                } else if (gameState == 0)
                {
                    //Draw car explosion, play sound effect
                    music.pause();
                    FEHImage explosion("explosion.png");
                    FEHImage explosionBig("explosionBig.png");
                    FEHSound explosionSound("explosionSound.wav");
                    explosionSound.restart();

                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(carx, cary, 25, 45); // Draw over old car
                    LCD.FillRectangle(170, 202, 115, 38);
                    
                    explosion.Draw(carx-15, cary);
                    LCD.Update();
                    Sleep(0.1);
                    explosionBig.Draw(carx-30, cary-10);
                    LCD.Update();
                    Sleep(0.3);

                    endScreen(tptr, qptr);
                }
               
            }

            //Make sure user is not holding button for too long
            float timeStart = TimeNow();

            while(LCD.Touch(&touchx, &touchy))
            {
               
                if (TimeNow() - timeStart > 0.6)
                {
                    cheat(qptr, music);
                }

               
            }


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu(qptr);
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

        int x1 = 170, y1 = 20, width = 120, height = 30;
        int touchx, touchy;
        bool keepTrackingClicks = true, game = true;

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
       
        //Import car image and draw
        FEHImage car("car.png");
        int carx=70, cary=160, *xptr=&carx;
        car.Draw(carx, cary);
        LCD.Update();

        //Draw grass
        FEHImage g1 ("grass1.png");
        FEHImage g2 ("grass2.png");
        FEHImage g3 ("grass3.png");
        g3.Draw(1, 0);
        g1.Draw(140, 0);


        //Draw road lines
        LCD.DrawLine(160, 0, 160, 240);
        LCD.DrawLine(20, 0, 20, 240);
        LCD.DrawLine(1, 0, 1, 240);
        LCD.DrawLine(140, 0, 140, 240);
        LCD.DrawLine(60, 0, 60, 240);
        LCD.DrawLine(100, 0, 100, 240);

        question levelTwo(2);
        //Generate a random question
        levelTwo.random();

        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy))
            {
                LCD.SetFontScale(1);
                //Move options down
                int gameState = levelTwo.moveAnswers(xptr);

                if (gameState == 2)
                {
                    (*tptr)++;
                    if ((*tptr)>(*qptr)){
                        (*qptr)=(*tptr);
                    }
                    StartGame(2, qptr, tptr, music);

                } else if (gameState == 0)
                {
                    //Draw car explosion
                    music.pause();
                    FEHImage explosion("explosion.png");
                    FEHImage explosionBig("explosionBig.png");
                    FEHSound explosionSound("explosionSound.wav");
                    explosionSound.restart();

                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(carx, cary, 25, 45); // Draw over old car
                    LCD.FillRectangle(170, 202, 115, 38);

                    explosion.Draw(carx-15, cary);
                    LCD.Update();
                    Sleep(0.1);
                    explosionBig.Draw(carx-30, cary-10);
                    LCD.Update();
                    Sleep(0.3);

                    endScreen(tptr, qptr);
                }
               
            }

            //Make sure user is not holding button for too long
            float timeStart = TimeNow();

            while(LCD.Touch(&touchx, &touchy))
            {
               
                if (TimeNow() - timeStart > 0.6)
                {
                    cheat(qptr, music);
                }

               
            }


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu(qptr);
                keepTrackingClicks = false;
            } else if (touchx < rectX+(rectW/2) && touchx > rectX && touchy > rectY && touchy < rectY+rectH){
                //Move car left
                MoveLeft(xptr);
               


            } else if (touchx < rectX+rectW && touchx > rectX+(rectW/2) && touchy > rectY && touchy < rectY+rectH){
                //Move car right
                MoveRight(xptr);
            }
        }
    } else if (level ==3)
    {
        int x1 = 170, y1 = 20, width = 120, height = 30;
        int touchx, touchy;
        bool keepTrackingClicks = true, game = true;

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
       
        //Import car image and draw
        FEHImage car("car.png");
        int carx=70, cary=160, *xptr=&carx;
        car.Draw(carx, cary);
        LCD.Update();

        //Draw grass
        FEHImage g1 ("grass1.png");
        FEHImage g2 ("grass2.png");
        FEHImage g3 ("grass3.png");
        g3.Draw(1, 0);
        g1.Draw(140, 0);


        //Draw road lines
        LCD.DrawLine(160, 0, 160, 240);
        LCD.DrawLine(20, 0, 20, 240);
        LCD.DrawLine(1, 0, 1, 240);
        LCD.DrawLine(140, 0, 140, 240);
        LCD.DrawLine(60, 0, 60, 240);
        LCD.DrawLine(100, 0, 100, 240);

        question levelThree(3);
        //Generate a random question
        levelThree.random();

        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy))
            {
                LCD.SetFontScale(1);
                //Move options down
                int gameState = levelThree.moveAnswers(xptr);

                if (gameState == 2)
                {
                    (*tptr)++;
                    if ((*tptr)>(*qptr)){
                        (*qptr)=(*tptr);
                    }
                    StartGame(3, qptr, tptr, music);

                } else if (gameState == 0)
                {
                    //Draw car explosion
                    music.pause();
                    FEHImage explosion("explosion.png");
                    FEHImage explosionBig("explosionBig.png");
                    FEHSound explosionSound("explosionSound.wav");
                    explosionSound.restart();

                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(carx, cary, 25, 45); // Draw over old car
                    LCD.FillRectangle(170, 202, 115, 38);

                    explosion.Draw(carx-15, cary);
                    LCD.Update();
                    Sleep(0.1);
                    explosionBig.Draw(carx-30, cary-10);
                    LCD.Update();
                    Sleep(0.3);

                    endScreen(tptr, qptr);
                }
               
            }

            //Make sure user is not holding button for too long
            float timeStart = TimeNow();

            while(LCD.Touch(&touchx, &touchy))
            {
               
                if (TimeNow() - timeStart > 0.6)
                {
                    cheat(qptr, music);
                }

               
            }


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu(qptr);
                keepTrackingClicks = false;
            } else if (touchx < rectX+(rectW/2) && touchx > rectX && touchy > rectY && touchy < rectY+rectH){
                //Move car left
                MoveLeft(xptr);
               


            } else if (touchx < rectX+rectW && touchx > rectX+(rectW/2) && touchy > rectY && touchy < rectY+rectH){
                //Move car right
                MoveRight(xptr);
            }
        }
    }
}

//Function to switch the screen.
void SwitchScreen(int screen, int *qptr, FEHSound sound)
{
    int x1 = 170, y1 = 20, width = 120, height = 30;
    int touchx, touchy;
    bool keepTrackingClicks = true;
    int tempScore=0, *tptr;
    tptr=&tempScore;


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
                sound.pause();
                MainMenu(qptr);
                keepTrackingClicks = false;

            } else if (touchx < levelButtonx+levelButtonWidth && touchx > levelButtonx && touchy > levelButtony && touchy < levelButtony+levelButtonHeight)
            {
                sound.pause();
                FEHSound coconutMall("coconutMall.wav");
                coconutMall.restart();
                StartGame(1, qptr, tptr, coconutMall);
                keepTrackingClicks = false;
            } else if (touchx < levelButtonx+levelButtonWidth && touchx > levelButtonx && touchy > levelButtony2 && touchy < levelButtony2+levelButtonHeight)
            {
                sound.pause();
                FEHSound coconutMall("coconutMall.wav");
                coconutMall.restart();
                StartGame(2, qptr, tptr, coconutMall);
                keepTrackingClicks = false;
            } else if (touchx < levelButtonx+levelButtonWidth && touchx > levelButtonx && touchy > levelButtony3 && touchy < levelButtony3+levelButtonHeight)
            {
                sound.pause();
                FEHSound coconutMall("coconutMall.wav");
                coconutMall.restart();
                StartGame(3, qptr, tptr, coconutMall);
                keepTrackingClicks = false;
            }
        }



    } else if (screen ==2)
    {
        // Clear background
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        //Write statistics
        LCD.WriteAt("High Score:", 95, 100);
        LCD.WriteAt((*qptr), 150, 125);

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
                MainMenu(qptr);
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
        LCD.WriteAt("Don't hold the arrows!", 90, 210);

       

        //Check if player clicks main menu button
        while (keepTrackingClicks)
        {
            while(!LCD.Touch(&touchx, &touchy)){}
            while(LCD.Touch(&touchx, &touchy)){}


            if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
            {
                MainMenu(qptr);
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
                MainMenu(qptr);
                keepTrackingClicks = false;
            }
        }

    }


}

void MainMenu(int *qptr) {
    int x1 = 130, y1 = 80;
    int x2 = 65, y2 = 120;
    int x3 = 75, y3 = 160;
    int x4 = 110, y4 = 200;
    int width = 60, height = 30;
    int width2 = 190, height2 = 30;
    int width3 = 170, height3 = 30;
    int width4 = 100, height4 = 30;
    int touchx, touchy;
    bool keepTrackingClicks = true;

    FEHSound mainMenuMusic("mainMenuMusic.wav");
    mainMenuMusic.restart();

    //Clear screen
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();


    //Write title of game
    LCD.SetFontScale(1.5);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("GAME", 123, 10);
    LCD.Update();
    Sleep(0.4);

    LCD.SetFontScale(1.5);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("NAME", 123, 45);
    LCD.Update();

    Sleep(0.8);

    // Draw Play button
    LCD.SetFontScale(1);
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x1, y1, width, height);
    LCD.WriteAt("PLAY", x1+5, y1+5);
    Sleep(0.2);
    LCD.Update();

    // Draw Statistics button
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x2, y2, width2, height2);
    LCD.WriteAt("VIEW STATISTICS", x2+5, y2+5);
    Sleep(0.2);
    LCD.Update();

    // Draw Instructions button
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x3, y3, width3, height3);
    LCD.WriteAt("INSTRUCTIONS", x3+12, y3+5);
    Sleep(0.2);
    LCD.Update();

    // Draw Credits button
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(x4, y4, width4, height4);
    LCD.WriteAt("CREDITS", x4+7, y4+5);
    Sleep(0.2);
    LCD.Update();

    Sleep(0.2);
    LCD.Update();

    //See where the player clicks and move to the corresponding screen
    while (keepTrackingClicks)
    {
        while(!LCD.Touch(&touchx, &touchy)){}
        while(LCD.Touch(&touchx, &touchy)){}


        if (touchx < x1+width && touchx > x1 && touchy > y1 && touchy < y1+height)
        {
            SwitchScreen(1, qptr, mainMenuMusic);
            keepTrackingClicks = false;
        } else if (touchx < x2+width2 && touchx > x2 && touchy > y2 && touchy < y2+height2)
        {
            mainMenuMusic.pause();
            SwitchScreen(2, qptr, mainMenuMusic);
            keepTrackingClicks = false;
        } else if (touchx < x3+width3 && touchx > x3 && touchy > y3 && touchy < y3+height3)
        {
            mainMenuMusic.pause();
            SwitchScreen(3, qptr, mainMenuMusic);
            keepTrackingClicks = false;
        } else if (touchx < x4+width4 && touchx > x4 && touchy > y4 && touchy < y4+height4)
        {
            mainMenuMusic.pause();
            SwitchScreen(4, qptr, mainMenuMusic);
            keepTrackingClicks = false;
        }
    }


}

int main() {
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    int qAns=0, *qptr;
    qptr=&qAns;
    MainMenu(qptr);

    while (1) {
        LCD.Update();
        // Never end
    }
    return 0;
}

//Constructor for question function 
question::question(int l, int a, int b, int x, int y, int z, int c, int d, int e)
{

    level = l;
    decoy1 = a;
    decoy2 = b;
    response = x;
    answer = y;
    correctX = z;

    decoy1X = c;
    decoy2X = d;

    answerY = e;
}

//Function to move the answer options and check if player won
int question::moveAnswers(int *xptr)
{
    FEHImage g1 ("grass1.png");
    FEHImage g2 ("grass2.png");
    FEHImage g3 ("grass3.png");

    //See if the car is at the correct x position and y
    if (*xptr == correctX+10 && answerY >= 160-30)
    {
        //You win 
        return(2);


    }else if (answerY < 160-30 )
    {
        //Draw over old answers
        int x1=20, x2=60, x3=100, rectH=30, rectW=40;
   
        LCD.SetFontColor(BLACK);
        LCD.FillRectangle(x1, answerY, rectW, rectH);
        LCD.FillRectangle(x2, answerY, rectW, rectH);
        LCD.FillRectangle(x3, answerY, rectW, rectH);

        LCD.SetFontColor(WHITE);
        LCD.DrawLine(160, 0, 160, 240);
        LCD.DrawLine(20, 0, 20, 240);
        LCD.DrawLine(1, 0, 1, 240);
        LCD.DrawLine(140, 0, 140, 240);
        LCD.DrawLine(60, 0, 60, 240);
        LCD.DrawLine(100, 0, 100, 240);
        LCD.Update();
       
        answerY+=1;

        if (answerY%6==0){
            g3.Draw(1,0);
            g1.Draw(140,0);
        } else if (answerY%6==1){
            g3.Draw(1,0);
            g1.Draw(140,0);
        } else if (answerY%6==2){
            g2.Draw(1,0);
            g3.Draw(140,0);
        } else if (answerY%6==3){
            g2.Draw(1,0);
            g3.Draw(140,0);
        } else if (answerY%6==4){
            g1.Draw(1,0);
            g2.Draw(140,0);
        } else {
            g1.Draw(1,0);
            g2.Draw(140,0);
        }

        //Redraw rectangles and answers
        LCD.DrawRectangle(correctX, answerY, rectW, rectH);
        LCD.WriteAt(answer, correctX+3, answerY+5);
        LCD.DrawRectangle(decoy1X, answerY, rectW, rectH);
        LCD.WriteAt(decoy1, decoy1X+3, answerY+5);
        LCD.DrawRectangle(decoy2X, answerY, rectW, rectH);
        LCD.WriteAt(decoy2, decoy2X+3, answerY+5);
        LCD.Update();
   

        return(1);

    }else
    {
        return(0);
    }
}

void question::random()
{
    int a;
    int b;
    int randomNumber;
    char addSub;
    int num1 = 0;
    int num2 = 0;

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
            LCD.WriteAt(num1, 190, 90);
            LCD.WriteAt(addSub, 220, 90);
            LCD.WriteAt(num2, 240, 90);

        } else
        {
            addSub = '-';
            if (num1 >= num2)
            {

            answer = num1 - num2;
            //Write question
            LCD.SetFontScale(1);
            LCD.WriteAt(num1, 190, 90);
            LCD.WriteAt(addSub, 220, 90);
            LCD.WriteAt(num2, 240, 90);

            } else
            {

                answer = num2 - num1;
                //Write question
                LCD.SetFontScale(1);
                LCD.WriteAt(num2, 190, 90);
                LCD.WriteAt(addSub, 220, 90);
                LCD.WriteAt(num1, 240, 90);

            }
        }

        //Pick random 1-3 gate that the answer falls through.
        LCD.SetFontScale(0.8);
        int rectW = 40, rectY = 0;
        while (decoy2 == 0)
        {
            randomNumber = Random.RandInt()/200;

            if (randomNumber > 10 && randomNumber < 15)
            {
                //Draw true answer in first box.
                correctX = 20;
                LCD.DrawRectangle(correctX, rectY, rectW, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 60;
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, rectW, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 100;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

            } else if (randomNumber > 15 && randomNumber < 20)
            {
                //Draw true answer in second box.
                correctX=60; //Store answer location
                LCD.DrawRectangle(correctX, rectY, rectW, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 20;
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, rectW, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 100;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

            } else if (randomNumber > 20 && randomNumber < 25)
            {
                //Draw true answer in third box.
                correctX=100; //Store answer location
                LCD.DrawRectangle(correctX, rectY, 40, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 60;
                decoy1 = (a + b + randomNumber) * 6.0/7.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, 40, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 20;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

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

        //Write question
        LCD.SetFontScale(1);
        LCD.WriteAt(num1, 190, 90);
        LCD.WriteAt('X',220, 90);
        LCD.WriteAt(num2, 240, 90);

   
        //Pick random 1-3 gate that the answer falls through.
        LCD.SetFontScale(0.8);
        int rectW = 40, rectY=0;
        while (decoy2 == 0)
        {
            randomNumber = Random.RandInt()/200;

            if (randomNumber > 10 && randomNumber < 15)
            {
                //Draw true answer in first box.
                correctX = 20;
                LCD.DrawRectangle(correctX, rectY, rectW, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 60;
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, rectW, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 100;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

            } else if (randomNumber > 15 && randomNumber < 20)
            {
                //Draw true answer in second box.
                correctX=60; //Store answer location
                LCD.DrawRectangle(correctX, rectY, rectW, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 20;
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, rectW, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 100;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

            } else if (randomNumber > 20 && randomNumber < 25)
            {
                //Draw true answer in third box.
                correctX=100; //Store answer location
                LCD.DrawRectangle(correctX, rectY, 40, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 60;
                decoy1 = (a + b + randomNumber) * 6.0/7.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, 40, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 20;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

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
        LCD.WriteAt(num1, 180, 90);
        LCD.WriteAt('X', 210, 90);
        LCD.WriteAt(num2, 230, 90);
        LCD.WriteAt('+', 250, 90);
        LCD.WriteAt(num3, 270, 90);



        //Pick random 1-3 gate that the answer falls through.
        LCD.SetFontScale(0.8);
        int rectW=40, rectY=0;
        while (decoy2 == 0)
        {
            randomNumber = Random.RandInt()/200;

            if (randomNumber > 10 && randomNumber < 15)
            {
                //Draw true answer in first box.
                correctX = 20;
                LCD.DrawRectangle(correctX, rectY, rectW, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 60;
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, rectW, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 100;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

            } else if (randomNumber > 15 && randomNumber < 20)
            {
                //Draw true answer in second box.
                correctX=60; //Store answer location
                LCD.DrawRectangle(correctX, rectY, rectW, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 20;
                decoy1 = (a + b + randomNumber) * 4.0/5.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, rectW, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 100;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

            } else if (randomNumber > 20 && randomNumber < 25)
            {
                //Draw true answer in third box.
                correctX=100; //Store answer location
                LCD.DrawRectangle(correctX, rectY, 40, 30);
                LCD.WriteAt(answer, correctX+3, rectY+5);
               

                //Draw decoy answer
                decoy1X = 60;
                decoy1 = (a + b + randomNumber) * 6.0/7.0 ;
                //Check for same options
                if (decoy1==answer){
                    decoy1++;
                }
                LCD.DrawRectangle(decoy1X, rectY, 40, 30);
                LCD.WriteAt(decoy1, decoy1X+3, rectY+5);

                //Draw decoy answer
                decoy2 = answer - randomNumber;
                if (decoy2 <= 0)
                {
                   decoy2 = answer + randomNumber + 5;
                }
                //Check for same options
                if (decoy2==answer){
                    decoy2++;
                }

                decoy2X = 20;
                LCD.DrawRectangle(decoy2X, rectY, rectW, 30);
                LCD.WriteAt(decoy2, decoy2X+3, rectY+5);
                LCD.Update();

            }



        }
       




    }
   
   

}