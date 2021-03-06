// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Map.h"

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44


double  g_dElapsedTime;
double  g_dDeltaTime;
double EnemyUpdateRate = 0.0;
double EnemyUpdateRate2 = 0.0;
double EnemyUpdateRate3 = 0.0;
double EnemyUpdateRate4 = 0.0;
double Charupdaterate = 0.0;


SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
SGameChar  g_sGhost[4];
SGameChar   g_biscuit[10];
SGameChar g_sBerry[4];
int score;
int prev_move;
int lives = 3;
int movement = 0;
EGAMESTATES g_eGameState = S_GAME; // initial state
Map g_sMap;

// Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_GAME;

    g_sChar.m_cLocation.X = (39);
    g_sChar.m_cLocation.Y = (15);
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);

    /* initialize random seed: */
    srand(time (NULL));

    for (int i = 0; i < 4; i++)
    {
            g_sGhost[i].m_cLocation.X = 37; 
            g_sGhost[i].m_cLocation.Y = 13;
            g_sGhost[i].m_bActive = true;
            g_sGhost[i].m_state = 0;
    }

    for (int i = 0; i < 10; i++)
    { 
        do {
            g_biscuit[i].m_cLocation.X = rand() % 80;
            g_biscuit[i].m_cLocation.Y = rand() % 25; // 35 10 44 14
        } while (g_sMap.mapArray[g_biscuit[i].m_cLocation.X][g_biscuit[i].m_cLocation.Y] == W || g_sMap.mapArray[g_biscuit[i].m_cLocation.X][g_biscuit[i].m_cLocation.Y] == T || g_sMap.mapArray[g_biscuit[i].m_cLocation.X][g_biscuit[i].m_cLocation.Y] == D ||  44 > g_biscuit[i].m_cLocation.X && g_biscuit[i].m_cLocation.X > 35 && 14 > g_biscuit[i].m_cLocation.Y &&   g_biscuit[i].m_cLocation.Y > 10);
        g_biscuit[i].m_bActive = true;

    }

    for (int i = 0; i < 4; i++)
    {
        do {
            g_sBerry[i].m_cLocation.X = rand() % 80;
            g_sBerry[i].m_cLocation.Y = rand() % 25; // 35 10 44 14
        } while (g_sMap.mapArray[g_sBerry[i].m_cLocation.X][g_sBerry[i].m_cLocation.Y] == W || g_sMap.mapArray[g_sBerry[i].m_cLocation.X][g_sBerry[i].m_cLocation.Y] == T || 44 > g_sBerry[i].m_cLocation.X && g_sBerry[i].m_cLocation.X > 35 && 14 > g_sBerry[i].m_cLocation.Y && g_sBerry[i].m_cLocation.Y > 10);
        g_sBerry[i].m_bActive = true;

    }

    for (int i = 0; i < 4; i++)
    {

        g_sGhost[i].m_eWaypoints[0].X = 42;
        g_sGhost[i].m_eWaypoints[0].Y = 13;
        g_sGhost[i].m_eWaypoints[1].X = 42;
        g_sGhost[i].m_eWaypoints[1].Y = 11;
        g_sGhost[i].m_eWaypoints[2].X = 37;
        g_sGhost[i].m_eWaypoints[2].Y = 11;
        g_sGhost[i].m_eWaypoints[3].X = 37;
        g_sGhost[i].m_eWaypoints[3].Y = 13;
    }

    // 0 x-, 1 y+, 2 x+, 3 y-, 4 x+, 5 y+, 6 x+, 7 y+, 8 x-, 9 y-, 10 x+, 11 y+, 12 x+, 4 y+, 3 x-, 13 y-, 0 x-
    g_sGhost[2].m_dWaypoints[0].X = 33;
    g_sGhost[2].m_dWaypoints[0].Y = 9;
    g_sGhost[2].m_dWaypoints[1].X = 33;
    g_sGhost[2].m_dWaypoints[1].Y = 15;
    g_sGhost[2].m_dWaypoints[2].X = 46;
    g_sGhost[2].m_dWaypoints[2].Y = 15;
    g_sGhost[2].m_dWaypoints[3].X = 46;
    g_sGhost[2].m_dWaypoints[3].Y = 12;
    g_sGhost[2].m_dWaypoints[4].X = 50;
    g_sGhost[2].m_dWaypoints[4].Y = 12;
    g_sGhost[2].m_dWaypoints[5].X = 50;
    g_sGhost[2].m_dWaypoints[5].Y = 15;
    g_sGhost[2].m_dWaypoints[6].X = 54;
    g_sGhost[2].m_dWaypoints[6].Y = 15;
    g_sGhost[2].m_dWaypoints[7].X = 54;
    g_sGhost[2].m_dWaypoints[7].Y = 23;
    g_sGhost[2].m_dWaypoints[8].X = 25;
    g_sGhost[2].m_dWaypoints[8].Y = 23;
    g_sGhost[2].m_dWaypoints[9].X = 25;
    g_sGhost[2].m_dWaypoints[9].Y = 1;
    g_sGhost[2].m_dWaypoints[10].X = 54;
    g_sGhost[2].m_dWaypoints[10].Y = 1;
    g_sGhost[2].m_dWaypoints[11].X = 54;
    g_sGhost[2].m_dWaypoints[11].Y = 9;
    g_sGhost[2].m_dWaypoints[12].X = 50;
    g_sGhost[2].m_dWaypoints[12].Y = 9;
    g_sGhost[2].m_dWaypoints[13].X = 46;
    g_sGhost[2].m_dWaypoints[13].Y = 9;

    g_sGhost[2].m_bPostBerry = false;
    g_sGhost[2].m_gDirection = 0;
    g_sChar.m_bBerry = false;
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
   
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_LOSE: gameplayKBHandler(keyboardEvent);
        break;
    case S_WIN : gameplayKBHandler(keyboardEvent);
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
   
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    case VK_W: key = K_UP; break;
    case VK_A: key = K_LEFT; break;
    case VK_S: key = K_DOWN; break;
    case VK_D: key = K_RIGHT; break;
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_MENU : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
        case S_LOSE: updateLoseScreen();
            break;
        case S_WIN: updatewinscreen();
            break;
        case S_DIE: updatedie();
            break;
    }
}


void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
    teleport();  
                        // sound can be played here too.
    UpdateGhost();
    ghostMovement();
    updatebiscuit();
    updateLoseScreen();
    updatewinscreen();
    updatedie();

    updateBerry();
}


void moveCharacter()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    g_sChar.Charupdaterate += g_dDeltaTime;
   
    if (g_skKeyEvent[K_UP].keyReleased && g_sChar.m_cLocation.Y > 0)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] != W )
        {
            //Beep(1440, 30);
            movement = 1;
            g_sChar.m_cLocation.Y--;
            g_sChar.Charupdaterate = 0;
        }

    }


    
    if (g_skKeyEvent[K_LEFT].keyReleased && g_sChar.m_cLocation.X > 0)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X - 1][g_sChar.m_cLocation.Y] != W )
        {
            //Beep(1440, 30);
            movement = 2;
            g_sChar.m_cLocation.X--;
            g_sChar.Charupdaterate = 0;
        }
    }



    if (g_skKeyEvent[K_DOWN].keyReleased && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y + 1] != W)
        {
            if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y + 1] != D)
            {
                //Beep(1440, 30);
                movement = 3;
                g_sChar.m_cLocation.Y++;
                g_sChar.Charupdaterate = 0;
            }
        }
    }


    if (g_skKeyEvent[K_RIGHT].keyReleased && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X + 1][g_sChar.m_cLocation.Y] != W )
        {
            //Beep(1440, 30);
            movement = 4;
            g_sChar.m_cLocation.X++;
            g_sChar.Charupdaterate = 0;
        }
    }

    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
    }


    if (movement == 4)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X + 1][g_sChar.m_cLocation.Y] != W && g_sChar.Charupdaterate > 0.2)
        {
            //Beep(1440, 30);
            movement = 4;
            g_sChar.m_cLocation.X++;
            g_sChar.Charupdaterate = 0;
        }
    }


    {
        if (movement == 1)
        {
            if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] != W && g_sChar.Charupdaterate > 0.2)
            {
                //Beep(1440, 30);

                g_sChar.m_cLocation.Y--;
                g_sChar.Charupdaterate = 0;
            }
        }
    }

    if (movement == 3)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y + 1] != W)
        {
            if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y + 1] != D && g_sChar.Charupdaterate > 0.2)
            {
                //Beep(1440, 30);
                g_sChar.m_cLocation.Y++;
                g_sChar.Charupdaterate = 0;
            }
        }
    }

    if (movement == 2)

    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X - 1][g_sChar.m_cLocation.Y] != W && g_sChar.Charupdaterate > 0.2)
        {
            //Beep(1440, 30);

            g_sChar.m_cLocation.X--;
            g_sChar.Charupdaterate = 0;
        }
    }

}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_MENU: renderSplashScreen();
        break;
    case S_GAME: renderGame();
        break;
    case S_LOSE: renderlosescreen();
        break;
    case S_RESTART: init();
        break;
    case S_WIN: renderwinscreen();
        break;

    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input event
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
   

}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();// renders the character into the buffer
    renderbiscuit();
    renderGhost();
    renderBerry();
}


void renderMap()
{
    for (int x = 0; x < 80; x++)
    {
        for (int y = 0; y < 25; y++) {
            COORD c;
            c.X = x;
            c.Y = y;
            g_Console.writeToBuffer(c, "  ", g_sMap.mapArray[x][y]);
        }
    }

    
   
}



void renderCharacter()
{
    // Draw the location of the character
    if (g_sChar.m_bBerry == false)
    {
        WORD charColor = 0X0C;
        if (g_sChar.m_bActive)
        {
            charColor = 224;
        }
        g_Console.writeToBuffer(g_sChar.m_cLocation, (char)7, charColor);
    }
    if (g_sChar.m_bBerry == true)
    {
        WORD charColor = 0X0C;
        if (g_sChar.m_bActive)
        {
            charColor = 200;
        }
        g_Console.writeToBuffer(g_sChar.m_cLocation, (char)7, charColor);
    }
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    //ss << std::fixed << std::setprecision(3);
    //ss << 1.0 / g_dDeltaTime << "fps";
    //c.X = g_Console.getConsoleSize().X - 9;
    //c.Y = 0;
    //g_Console.writeToBuffer(c, ss.str());

    //display score
    ss.str();
    ss << score <<  " points";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    ss.str("l");
    ss << lives << " lives";
    c.X = g_Console.getConsoleSize().X / 2;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);

    if (g_sChar.m_bBerry == true)
    {
        ss.str("");
        ss << g_sChar.BerryTimer << "secs";
        c.X = 18;
        c.Y = 0;
        g_Console.writeToBuffer(c, ss.str(), 0x59);
    }

}

// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    COORD startPos = {50, 2};
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        default: continue;
        }
      
        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    ss.str("");
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
            ss.str("Mouse wheeled down");
        else
            ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:
        break;
    }
}
void renderbiscuit()
{
  
    WORD charColor = 2;
    for (int i = 0; i < 10; i++) 
    {
          
            //if (g_sMap.mapArray[g_biscuit[i].m_cLocation.X][g_biscuit[i].m_cLocation.Y] != W & g_biscuit.)
        if (g_biscuit[i].m_bActive)
            {
                charColor = 1;

                g_Console.writeToBuffer(g_biscuit[i].m_cLocation, 'C', 55);
            }


    }


}

void updatebiscuit()
{
    for (int i = 0; i < 10; i++)
    {
        if (g_biscuit[i].m_bActive && g_biscuit[i].m_cLocation.X == g_sChar.m_cLocation.X && g_biscuit[i].m_cLocation.Y == g_sChar.m_cLocation.Y)
        {
            g_biscuit[i].m_bActive = false;
            score += 1;
        }

        if (score == 10)
        {
            g_eGameState = S_WIN;
        }
    }
   

    

}

void renderBerry()
{

    WORD charColor = 2;
    for (int i = 0; i < 4; i++)
    {

        //if (g_sMap.mapArray[g_biscuit[i].m_cLocation.X][g_biscuit[i].m_cLocation.Y] != W & g_biscuit.)
        if (g_sBerry[i].m_bActive)
        {
            charColor = 1;

            g_Console.writeToBuffer(g_sBerry[i].m_cLocation, 'B', 70);
        }


    }


}

void updateBerry()
{
    g_sChar.BerryTimer += g_dDeltaTime;
    for (int i = 0; i < 4; i++)
    {
        
        if (g_sBerry[i].m_bActive && g_sBerry[i].m_cLocation.X == g_sChar.m_cLocation.X && g_sBerry[i].m_cLocation.Y == g_sChar.m_cLocation.Y)
        {
            g_sBerry[i].m_bActive = false;
            g_sChar.m_bBerry = true;
            g_sChar.BerryTimer = 0.0;
        }
        if (g_sChar.BerryTimer > 10)
        {
            g_sChar.m_bBerry = false;
        }
    }
}

void teleport()
{

    if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == T && g_sChar.m_cLocation.X < 1)
    {
        g_sChar.m_cLocation.X = 78;
    }


    if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == T && g_sChar.m_cLocation.X > 78)
    {
        g_sChar.m_cLocation.X = 1;
    }

}

void UpdateGhost()
{
    for (int i = 0; i < 4; i++)
    {
        if (g_sGhost[i].m_bActive == true)
        {
            if (g_sChar.m_cLocation.X == g_sGhost[i].m_cLocation.X &&
                g_sChar.m_cLocation.Y == g_sGhost[i].m_cLocation.Y && g_sGhost[i].m_bActive == true && g_sChar.m_bBerry == false)
            {
                g_eGameState = S_DIE;
            }
            if (g_sChar.m_cLocation.X == g_sGhost[i].m_cLocation.X &&
                g_sChar.m_cLocation.Y == g_sGhost[i].m_cLocation.Y && g_sGhost[i].m_bActive == true && g_sChar.m_bBerry == true)
            {
                g_sGhost[i].m_bActive = false;
            }
        }
    }

    if (g_sGhost[0].m_bActive == false && g_sGhost[1].m_bActive == false && g_sGhost[2].m_bActive == false && g_sGhost[3].m_bActive == false)
    {
        g_eGameState = S_WIN;
    }

    for (int i = 0; i < 4; i++)
    {
        if (g_sGhost[i].m_bActive == true)
        {
            if (g_sGhost[i].m_state == 0)
            {
                g_sGhost[i].EnemyUpdateRate2 += g_dDeltaTime;
                //EnemyUpdateRate3 += g_dDeltaTime;
                if (g_sGhost[3].m_fDirection == 0)
                {
                    if (g_sGhost[i].m_cLocation.X == g_sGhost[i].m_eWaypoints[0].X && g_sGhost[i].m_cLocation.Y == g_sGhost[i].m_eWaypoints[0].Y)
                    {
                        g_sGhost[i].m_fDirection = 1;
                    }
                    else if (g_sGhost[i].EnemyUpdateRate2 > 0.4)
                    {
                        g_sGhost[i].m_cLocation.X++;
                        g_sGhost[i].EnemyUpdateRate2 = 0;
                    }
                }
                if (g_sGhost[i].m_fDirection == 1)
                {
                    if (g_sGhost[i].m_cLocation.X == g_sGhost[i].m_eWaypoints[1].X && g_sGhost[i].m_cLocation.Y == g_sGhost[i].m_eWaypoints[1].Y)
                    {
                        g_sGhost[i].m_fDirection = 2;
                    }
                    else if (g_sGhost[i].EnemyUpdateRate2 > 0.4)
                    {
                        g_sGhost[i].m_cLocation.Y--;
                        g_sGhost[i].EnemyUpdateRate2 = 0;
                    }
                }
                if (g_sGhost[i].m_fDirection == 2)
                {
                    if (g_sGhost[i].m_cLocation.X == g_sGhost[i].m_eWaypoints[2].X && g_sGhost[i].m_cLocation.Y == g_sGhost[i].m_eWaypoints[2].Y)
                    {
                        g_sGhost[i].m_fDirection = 3;
                    }
                    else if (g_sGhost[i].EnemyUpdateRate2 > 0.4)
                    {
                        g_sGhost[i].m_cLocation.X--;
                        g_sGhost[i].EnemyUpdateRate2 = 0;
                    }
                }
                if (g_sGhost[i].m_fDirection == 3)
                {
                    if (g_sGhost[i].m_cLocation.X == g_sGhost[i].m_eWaypoints[3].X && g_sGhost[i].m_cLocation.Y == g_sGhost[i].m_eWaypoints[3].Y)
                    {
                        g_sGhost[i].m_fDirection = 0;
                    }
                    else if (g_sGhost[i].EnemyUpdateRate2 > 0.4)
                    {
                        g_sGhost[i].m_cLocation.Y++;
                        g_sGhost[i].EnemyUpdateRate2 = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (g_sGhost[i].m_bActive == true)
        {
            g_sGhost[i].RenderUpdateTimer += g_dDeltaTime;
        }
    }
    if (g_dElapsedTime > 1 && g_sGhost[0].m_state == 0)
    {
        g_sGhost[0].m_state = 2;
    }
    if (g_sGhost[0].m_state == 2)
    {
        if (g_sGhost[0].m_cLocation.X == 39 && g_sGhost[0].m_cLocation.Y == 9)
        {
            g_sGhost[0].m_state = 1;
        }
        if (g_sGhost[0].RenderUpdateTimer > 0.4)
        {
            if (g_sGhost[0].m_cLocation.X >= 40)
            {
                if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X - 1][g_sGhost[0].m_cLocation.Y] != W)
                {
                    g_sGhost[0].m_cLocation.X -= 1;
                    g_sGhost[0].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[0].m_cLocation.X <= 38)
            {
                if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X + 1][g_sGhost[0].m_cLocation.Y] != W)
                {
                    g_sGhost[0].m_cLocation.X += 1;
                    g_sGhost[0].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[0].m_cLocation.Y >= 8)
            {
                if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X][g_sGhost[0].m_cLocation.Y - 1] != W)
                {
                    g_sGhost[0].m_cLocation.Y -= 1;
                    g_sGhost[0].RenderUpdateTimer = 0;
                }
            }
        }
    }
    if (g_dElapsedTime > 3 && g_sGhost[1].m_state == 0)
    {
        g_sGhost[1].m_state = 2;
    }
    if (g_sGhost[1].m_state == 2)
    {
        if (g_sGhost[1].m_cLocation.X == 39 && g_sGhost[1].m_cLocation.Y == 9)
        {
            g_sGhost[1].m_state = 1;
        }
        if (g_sGhost[1].RenderUpdateTimer > 0.4)
        {
            if (g_sGhost[1].m_cLocation.X >= 40)
            {
                if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X - 1][g_sGhost[1].m_cLocation.Y] != W)
                {
                    g_sGhost[1].m_cLocation.X -= 1;
                    g_sGhost[1].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[1].m_cLocation.X <= 38)
            {
                if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X + 1][g_sGhost[1].m_cLocation.Y] != W)
                {
                    g_sGhost[1].m_cLocation.X += 1;
                    g_sGhost[1].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[1].m_cLocation.Y >= 8)
            {
                if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X][g_sGhost[1].m_cLocation.Y - 1] != W)
                {
                    g_sGhost[1].m_cLocation.Y -= 1;
                    g_sGhost[1].RenderUpdateTimer = 0;
                }
            }
        }
    }
    if (g_dElapsedTime > 5 && g_sGhost[2].m_state == 0)
    {
        g_sGhost[2].m_state = 2;
    }
    if (g_sGhost[2].m_state == 2)
    {
        if (g_sGhost[2].m_cLocation.X == 39 && g_sGhost[2].m_cLocation.Y == 9)
        {
            g_sGhost[2].m_state = 1;
        }
        if (g_sGhost[2].RenderUpdateTimer > 0.4)
        {
            if (g_sGhost[2].m_cLocation.X >= 40)
            {
                if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X - 1][g_sGhost[2].m_cLocation.Y] != W)
                {
                    g_sGhost[2].m_cLocation.X -= 1;
                    g_sGhost[2].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[2].m_cLocation.X <= 38)
            {
                if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X + 1][g_sGhost[2].m_cLocation.Y] != W)
                {
                    g_sGhost[2].m_cLocation.X += 1;
                    g_sGhost[2].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[2].m_cLocation.Y >= 8)
            {
                if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X][g_sGhost[2].m_cLocation.Y - 1] != W)
                {
                    g_sGhost[2].m_cLocation.Y -= 1;
                    g_sGhost[2].RenderUpdateTimer = 0;
                }
            }
        }
    }
    if (g_dElapsedTime > 7 && g_sGhost[3].m_state == 0)
    {
        g_sGhost[3].m_state = 2;
    }
    if (g_sGhost[3].m_state == 2)
    {
        if (g_sGhost[3].m_cLocation.X == 39 && g_sGhost[3].m_cLocation.Y == 9)
        {
            g_sGhost[3].m_state = 1;
        }
        if (g_sGhost[3].RenderUpdateTimer > 0.4)
        {
            if (g_sGhost[3].m_cLocation.X >= 40)
            {
                if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X - 1][g_sGhost[3].m_cLocation.Y] != W)
                {
                    g_sGhost[3].m_cLocation.X -= 1;
                    g_sGhost[3].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[3].m_cLocation.X <= 38)
            {
                if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X + 1][g_sGhost[3].m_cLocation.Y] != W)
                {
                    g_sGhost[3].m_cLocation.X += 1;
                    g_sGhost[3].RenderUpdateTimer = 0;
                }
            }
            else if (g_sGhost[3].m_cLocation.Y >= 8)
            {
                if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y - 1] != W)
                {
                    g_sGhost[3].m_cLocation.Y -= 1;
                    g_sGhost[3].RenderUpdateTimer = 0;
                }
            }
        }
    }


}


void ghostMovement()
{
    int j = 0;
    if (g_sChar.m_bBerry == false)
    {
        if (g_sGhost[0].m_bActive == true)
        {
            if (g_sGhost[0].m_state == 1)
            {
                g_sGhost[0].EnemyUpdateRate += g_dDeltaTime;


                int random = rand() % 4 + 1;
                switch (random)
                {
                case 1:

                    if (g_sGhost[0].m_cLocation.X < g_Console.getConsoleSize().X - 1 && g_sGhost[0].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X + 1][g_sGhost[0].m_cLocation.Y] != W && g_sGhost[0].prev_move != 3)
                        {
                            g_sGhost[0].m_cLocation.X++;
                            g_sGhost[0].EnemyUpdateRate = 0;
                            g_sGhost[0].prev_move = 1;
                        }
                    }
                    break;
                case 2:
                    if (g_sGhost[0].m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && g_sGhost[0].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X][g_sGhost[0].m_cLocation.Y + 1] != W)
                        {
                            if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X][g_sGhost[0].m_cLocation.Y + 1] != D && g_sGhost[0].prev_move != 4)
                            {
                                g_sGhost[0].m_cLocation.Y++;
                                g_sGhost[0].EnemyUpdateRate = 0;
                                g_sGhost[0].prev_move = 2;
                            }
                        }
                    }
                    break;

                case 3:
                    if (g_sGhost[0].m_cLocation.X > 0 && g_sGhost[0].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X - 1][g_sGhost[0].m_cLocation.Y] != W && g_sGhost[0].prev_move != 1)
                        {
                            g_sGhost[0].m_cLocation.X--;
                            g_sGhost[0].EnemyUpdateRate = 0;
                            g_sGhost[0].prev_move = 3;
                        }
                    }
                    break;

                case 4:
                    if (g_sGhost[0].m_cLocation.Y > 0 && g_sGhost[0].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X][g_sGhost[0].m_cLocation.Y - 1] != W && g_sGhost[0].prev_move != 2)
                        {
                            g_sGhost[0].m_cLocation.Y--;
                            g_sGhost[0].EnemyUpdateRate = 0;
                            g_sGhost[0].prev_move = 4;
                        }
                    }
                    break;

                }
            }
        }
        if (g_sGhost[1].m_bActive == true)
        {
            if (g_sGhost[1].m_state == 1)
            {
                g_sGhost[1].EnemyUpdateRate += g_dDeltaTime;
                int random1 = rand() % 8 + 1;
                switch (random1)
                {

                case 1:
                    if (g_sGhost[1].m_cLocation.X < g_Console.getConsoleSize().X - 1 && g_sGhost[1].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X + 1][g_sGhost[1].m_cLocation.Y] != W)
                        {
                            g_sGhost[1].m_cLocation.X++;
                            g_sGhost[1].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 2:
                    if (g_sGhost[1].m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && g_sGhost[1].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X][g_sGhost[1].m_cLocation.Y + 1] != W)
                        {
                            if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X][g_sGhost[1].m_cLocation.Y + 1] != D)
                            {
                                g_sGhost[1].m_cLocation.Y++;
                                g_sGhost[1].EnemyUpdateRate = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if (g_sGhost[1].m_cLocation.X > 0 && g_sGhost[1].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X - 1][g_sGhost[1].m_cLocation.Y] != W)
                        {
                            g_sGhost[1].m_cLocation.X--;
                            g_sGhost[1].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 4:
                    if (g_sGhost[1].m_cLocation.Y > 0 && g_sGhost[1].EnemyUpdateRate > 0.4)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X][g_sGhost[1].m_cLocation.Y - 1] != W)
                        {
                            g_sGhost[1].m_cLocation.Y--;
                            g_sGhost[1].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                }
            }
        }
        if (g_sGhost[2].m_bActive == true)
        {
            if (g_sGhost[2].m_state == 1)
            {
                if (g_sGhost[2].m_bPostBerry == false)
                {
                    // 0 x-, 1 y+, 2 x+, 3 y-, 4 x+, 5 y+, 6 x+, 7 y+, 8 x-, 9 y-, 10 x+, 11 y+, 12 x+, 4 y+, 3 x-, 13 y-, 0 x-
                    g_sGhost[2].EnemyUpdateRate += g_dDeltaTime;
                    if (g_sGhost[2].m_gDirection == 0)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[0].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[0].Y)
                        {
                            g_sGhost[2].m_gDirection = 1;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X--;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 1)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[1].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[1].Y)
                        {
                            g_sGhost[2].m_gDirection = 2;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 2)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[2].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[2].Y)
                        {
                            g_sGhost[2].m_gDirection = 3;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 3)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[3].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[3].Y)
                        {
                            g_sGhost[2].m_gDirection = 4;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y--;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 4)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[4].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[4].Y)
                        {
                            g_sGhost[2].m_gDirection = 5;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 5)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[5].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[5].Y)
                        {
                            g_sGhost[2].m_gDirection = 6;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 6)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[6].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[6].Y)
                        {
                            g_sGhost[2].m_gDirection = 7;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 7)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[7].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[7].Y)
                        {
                            g_sGhost[2].m_gDirection = 8;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 8)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[8].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[8].Y)
                        {
                            g_sGhost[2].m_gDirection = 9;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X--;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 9)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[9].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[9].Y)
                        {
                            g_sGhost[2].m_gDirection = 10;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y--;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 10)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[10].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[10].Y)
                        {
                            g_sGhost[2].m_gDirection = 11;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 11)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[11].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[11].Y)
                        {
                            g_sGhost[2].m_gDirection = 12;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 12)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[12].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[12].Y)
                        {
                            g_sGhost[2].m_gDirection = 13;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X--;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 13)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[4].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[4].Y)
                        {
                            g_sGhost[2].m_gDirection = 14;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y++;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 14)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[3].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[3].Y)
                        {
                            g_sGhost[2].m_gDirection = 15;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.X--;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    if (g_sGhost[2].m_gDirection == 15)
                    {
                        if (g_sGhost[2].m_cLocation.X == g_sGhost[2].m_dWaypoints[13].X && g_sGhost[2].m_cLocation.Y == g_sGhost[2].m_dWaypoints[13].Y)
                        {
                            g_sGhost[2].m_gDirection = 0;
                        }
                        else if (g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            g_sGhost[2].m_cLocation.Y--;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                }
                if (g_sGhost[2].m_bPostBerry == true)
                {
                    g_sGhost[2].EnemyUpdateRate += g_dDeltaTime;
                    int random2 = rand() % 8 + 1;
                    switch (random2)
                    {
                    case 1:
                        if (g_sGhost[2].m_cLocation.X < g_Console.getConsoleSize().X - 1 && g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X + 1][g_sGhost[2].m_cLocation.Y] != W)
                            {
                                g_sGhost[2].m_cLocation.X++;
                                g_sGhost[2].EnemyUpdateRate = 0;
                            }
                        }
                        break;
                    case 2:
                        if (g_sGhost[2].m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X][g_sGhost[2].m_cLocation.Y + 1] != W)
                            {
                                if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X][g_sGhost[2].m_cLocation.Y + 1] != D)
                                {
                                    g_sGhost[2].m_cLocation.Y++;
                                    g_sGhost[2].EnemyUpdateRate = 0;
                                }
                            }
                        }
                        break;
                    case 3:
                        if (g_sGhost[2].m_cLocation.X > 0 && g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X - 1][g_sGhost[2].m_cLocation.Y] != W)
                            {
                                g_sGhost[2].m_cLocation.X--;
                                g_sGhost[2].EnemyUpdateRate = 0;
                            }
                        }
                        break;
                    case 4:
                        if (g_sGhost[2].m_cLocation.Y > 0 && g_sGhost[2].EnemyUpdateRate > 0.4)
                        {
                            if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X][g_sGhost[2].m_cLocation.Y - 1] != W)
                            {
                                g_sGhost[2].m_cLocation.Y--;
                                g_sGhost[2].EnemyUpdateRate = 0;
                            }
                        }
                        break;
                    }
                }
            }
        }
        if (g_sGhost[3].m_bActive == true)
        {
            if (g_sGhost[3].m_state == 1)
            {
                g_sGhost[3].EnemyUpdateRate += g_dDeltaTime;
                int random3 = rand() % 8 + 1;
                switch (random3)
                {
                case 1:
                    if (g_sGhost[3].m_cLocation.X >= g_sChar.m_cLocation.X && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X - 1][g_sGhost[3].m_cLocation.Y] != W)
                        {
                            g_sGhost[3].m_cLocation.X -= 1;
                            g_sGhost[3].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 2:
                    if (g_sGhost[3].m_cLocation.Y >= g_sChar.m_cLocation.Y && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y - 1] != W)
                        {
                            g_sGhost[3].m_cLocation.Y -= 1;
                            g_sGhost[3].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 3:
                    if (g_sGhost[3].m_cLocation.X <= g_sChar.m_cLocation.X && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X + 1][g_sGhost[3].m_cLocation.Y] != W)
                        {
                            g_sGhost[3].m_cLocation.X += 1;
                            g_sGhost[3].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 4:
                    if (g_sGhost[3].m_cLocation.Y <= g_sChar.m_cLocation.Y && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y + 1] != W)
                        {
                            if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y + 1] != D)
                            {
                                g_sGhost[3].m_cLocation.Y += 1;
                                g_sGhost[3].EnemyUpdateRate = 0;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    if (g_sChar.m_bBerry == true)
    {
        g_sGhost[2].m_bPostBerry = true;
        if (g_sGhost[0].m_bActive == true)
        {
            if (g_sGhost[0].m_state == 1)
            {
                g_sGhost[0].prev_move = 5;
                g_sGhost[0].EnemyUpdateRate += g_dDeltaTime;
                int random3 = rand() % 8 + 1;
                switch (random3)
                {
                case 1:
                    if (g_sGhost[0].m_cLocation.X >= g_sChar.m_cLocation.X && g_sGhost[0].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X + 1][g_sGhost[0].m_cLocation.Y] != W)
                        {
                            g_sGhost[0].m_cLocation.X += 1;
                            g_sGhost[0].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 2:
                    if (g_sGhost[0].m_cLocation.Y >= g_sChar.m_cLocation.Y && g_sGhost[0].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[0].m_cLocation.Y + 1] != W)
                        {
                            if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X][g_sGhost[0].m_cLocation.Y + 1] != D)
                            {
                                g_sGhost[0].m_cLocation.Y += 1;
                                g_sGhost[0].EnemyUpdateRate = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if (g_sGhost[0].m_cLocation.X <= g_sChar.m_cLocation.X && g_sGhost[0].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X - 1][g_sGhost[0].m_cLocation.Y] != W)
                        {
                            g_sGhost[0].m_cLocation.X -= 1;
                            g_sGhost[0].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 4:
                    if (g_sGhost[0].m_cLocation.Y <= g_sChar.m_cLocation.Y && g_sGhost[0].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[0].m_cLocation.X][g_sGhost[0].m_cLocation.Y - 1] != W)
                        {

                            g_sGhost[0].m_cLocation.Y -= 1;
                            g_sGhost[0].EnemyUpdateRate = 0;

                        }
                    }
                    break;
                }
            }
        }
        if (g_sGhost[1].m_bActive == true)
        {
            if (g_sGhost[1].m_state == 1)
            {
                g_sGhost[1].EnemyUpdateRate += g_dDeltaTime;
                int random3 = rand() % 8 + 1;
                switch (random3)
                {
                case 1:
                    if (g_sGhost[1].m_cLocation.X >= g_sChar.m_cLocation.X && g_sGhost[1].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X + 1][g_sGhost[1].m_cLocation.Y] != W)
                        {
                            g_sGhost[1].m_cLocation.X += 1;
                            g_sGhost[1].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 2:
                    if (g_sGhost[1].m_cLocation.Y >= g_sChar.m_cLocation.Y && g_sGhost[1].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X][g_sGhost[1].m_cLocation.Y + 1] != W)
                        {
                            if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X][g_sGhost[1].m_cLocation.Y + 1] != D)
                            {
                                g_sGhost[1].m_cLocation.Y += 1;
                                g_sGhost[1].EnemyUpdateRate = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if (g_sGhost[1].m_cLocation.X <= g_sChar.m_cLocation.X && g_sGhost[1].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X - 1][g_sGhost[1].m_cLocation.Y] != W)
                        {
                            g_sGhost[1].m_cLocation.X -= 1;
                            g_sGhost[1].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 4:
                    if (g_sGhost[1].m_cLocation.Y <= g_sChar.m_cLocation.Y && g_sGhost[1].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[1].m_cLocation.X][g_sGhost[1].m_cLocation.Y - 1] != W)
                        {

                            g_sGhost[1].m_cLocation.Y -= 1;
                            g_sGhost[1].EnemyUpdateRate = 0;

                        }
                    }
                    break;
                }
            }
        }
        if (g_sGhost[2].m_bActive == true)
        {
            if (g_sGhost[2].m_state == 1)
            {
                g_sGhost[2].EnemyUpdateRate += g_dDeltaTime;
                int random3 = rand() % 8 + 1;
                switch (random3)
                {
                case 1:
                    if (g_sGhost[2].m_cLocation.X >= g_sChar.m_cLocation.X && g_sGhost[2].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X + 1][g_sGhost[2].m_cLocation.Y] != W)
                        {
                            g_sGhost[2].m_cLocation.X += 1;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 2:
                    if (g_sGhost[2].m_cLocation.Y >= g_sChar.m_cLocation.Y && g_sGhost[2].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X][g_sGhost[2].m_cLocation.Y + 1] != W)
                        {
                            if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X][g_sGhost[2].m_cLocation.Y + 1] != D)
                            {
                                g_sGhost[2].m_cLocation.Y += 1;
                                g_sGhost[2].EnemyUpdateRate = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if (g_sGhost[2].m_cLocation.X <= g_sChar.m_cLocation.X && g_sGhost[2].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X - 1][g_sGhost[2].m_cLocation.Y] != W)
                        {
                            g_sGhost[2].m_cLocation.X -= 1;
                            g_sGhost[2].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 4:
                    if (g_sGhost[2].m_cLocation.Y <= g_sChar.m_cLocation.Y && g_sGhost[2].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[2].m_cLocation.X][g_sGhost[2].m_cLocation.Y - 1] != W)
                        {

                            g_sGhost[2].m_cLocation.Y -= 1;
                            g_sGhost[2].EnemyUpdateRate = 0;

                        }
                    }
                    break;
                }
            }
        }
        if (g_sGhost[3].m_bActive == true)
        {
            if (g_sGhost[3].m_state == 1)
            {
                g_sGhost[3].EnemyUpdateRate += g_dDeltaTime;
                int random3 = rand() % 8 + 1;
                switch (random3)
                {
                case 1:
                    if (g_sGhost[3].m_cLocation.X >= g_sChar.m_cLocation.X && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X + 1][g_sGhost[3].m_cLocation.Y] != W)
                        {
                            g_sGhost[3].m_cLocation.X += 1;
                            g_sGhost[3].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 2:
                    if (g_sGhost[3].m_cLocation.Y >= g_sChar.m_cLocation.Y && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y + 1] != W)
                        {
                            if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y + 1] != D)
                            {
                                g_sGhost[3].m_cLocation.Y += 1;
                                g_sGhost[3].EnemyUpdateRate = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if (g_sGhost[3].m_cLocation.X <= g_sChar.m_cLocation.X && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X - 1][g_sGhost[3].m_cLocation.Y] != W)
                        {
                            g_sGhost[3].m_cLocation.X -= 1;
                            g_sGhost[3].EnemyUpdateRate = 0;
                        }
                    }
                    break;
                case 4:
                    if (g_sGhost[3].m_cLocation.Y <= g_sChar.m_cLocation.Y && g_sGhost[3].EnemyUpdateRate > 1)
                    {
                        if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y - 1] != W)
                        {

                            g_sGhost[3].m_cLocation.Y -= 1;
                            g_sGhost[3].EnemyUpdateRate = 0;

                        }
                    }
                    break;
                }
            }
        }
    }
}

 
void renderGhost()
{
    /*for (int i = 0; i < 4; i++)
    {
        if (g_sGhost[i].m_bActive == true)
        {
            g_Console.writeToBuffer(g_sGhost[0].m_cLocation, (char)31, 9);
            g_Console.writeToBuffer(g_sGhost[1].m_cLocation, (char)31, 4);
            g_Console.writeToBuffer(g_sGhost[2].m_cLocation, (char)31, 5);
            g_Console.writeToBuffer(g_sGhost[3].m_cLocation, (char)31, 3);
        }
    }*/
    WORD charColor = 2;
    
        //if (g_sMap.mapArray[g_biscuit[i].m_cLocation.X][g_biscuit[i].m_cLocation.Y] != W & g_biscuit.)
    if (g_sGhost[0].m_bActive)
    {
        charColor = 1;

        g_Console.writeToBuffer(g_sGhost[0].m_cLocation, (char)31, 9);
    }
    if (g_sGhost[1].m_bActive)
    {
        charColor = 1;

        g_Console.writeToBuffer(g_sGhost[1].m_cLocation, (char)31, 4);
    }
    if (g_sGhost[2].m_bActive)
    {
        charColor = 1;

        g_Console.writeToBuffer(g_sGhost[2].m_cLocation, (char)31, 5);
    }
    if (g_sGhost[3].m_bActive)
    {
        charColor = 1;

        g_Console.writeToBuffer(g_sGhost[3].m_cLocation, (char)31, 3);
    }
}

void renderlosescreen()
{
    std::ostringstream ss;

    ss.str();
    ss << score;

    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 7;
    g_Console.writeToBuffer(c, "YOUR SCORE IS", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2;
    g_Console.writeToBuffer(c, ss.str(), 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit and 'Spacebar' to retry", 0x09);


}



void updateLoseScreen()
{
    if (g_eGameState == EGAMESTATES::S_LOSE && g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_bQuitGame = true;
    }

    if (g_eGameState == EGAMESTATES::S_LOSE && g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_eGameState = EGAMESTATES::S_RESTART;
        score = 0;
        lives = 3;
    }
}

void renderwinscreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 3;
    g_Console.writeToBuffer(c, "YOU WIN", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "Press 'Spacebar' to retry", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 5;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);

}

void updatewinscreen()
{
    if (g_eGameState == EGAMESTATES::S_WIN && g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_bQuitGame = true;
    }

    if (g_eGameState == EGAMESTATES::S_WIN && g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_eGameState = EGAMESTATES::S_RESTART;
        score = 0;
        lives = 3;
    }
}


void updatedie()
{
    if (g_eGameState == EGAMESTATES::S_DIE && lives --)
    {
        g_eGameState = EGAMESTATES::S_RESTART;
        score = 0;
    }

    if (lives == 0)
    {
        g_eGameState = EGAMESTATES::S_LOSE;
    }

}
