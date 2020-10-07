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

SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
SGameChar  g_sGhost[4];
EGAMESTATES g_eGameState = S_MENU; // initial state
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
    g_eGameState = S_MENU;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
    for (int i = 0; i < 4; i++)
    {
            g_sGhost[i].m_cLocation.X = (rand() % 68);
            g_sGhost[i].m_cLocation.Y = (rand() % 22);
            g_sGhost[i].m_bActive = false;
    }
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
                        // sound can be played here too.
    UpdateGhost();
    ghostMovement();
}


void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyReleased && g_sChar.m_cLocation.Y > 0)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] != W)
        {
            //Beep(1440, 30);
            g_sChar.m_cLocation.Y--;
        }
    }
    if (g_skKeyEvent[K_LEFT].keyReleased && g_sChar.m_cLocation.X > 0)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X - 1][g_sChar.m_cLocation.Y] != W)
        {
            //Beep(1440, 30);
            g_sChar.m_cLocation.X--;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyReleased && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y + 1] != W)
        {
            //Beep(1440, 30);
            g_sChar.m_cLocation.Y++;
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        if (g_sMap.mapArray[g_sChar.m_cLocation.X + 1][g_sChar.m_cLocation.Y] != W)
        {
            //Beep(1440, 30);
            g_sChar.m_cLocation.X++;
        }
    }
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;        
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
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    //renderbiscuit();
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
    //renderbiscuit();
    renderGhost();
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
    WORD charColor = 0X0C;
    if (g_sChar.m_bActive)
    {
        charColor = 224;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)7, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
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

}

//void renderbiscuit()
//{
//  
//    WORD charColor = 2;
//    if (g_sChar.m_bActive)
//    {
//        charColor = 1;
//    }
//     g_Console.writeToBuffer(, 'z', 55 );
//
//}

void UpdateGhost()
{
    for (int i = 0; i < 4; i++)
    {
        if (g_sChar.m_cLocation.X == g_sGhost[i].m_cLocation.X &&
            g_sChar.m_cLocation.Y == g_sGhost[i].m_cLocation.Y && g_sGhost[i].m_bActive == true)
        {
            g_eGameState = S_LOSE;
        }
    }
}


void ghostMovement()
{
    for (int i = 0; i < 3; i++)
    {
        EnemyUpdateRate += g_dDeltaTime;
        int random = rand() % 8 + 1;
        switch (random)
        {

        case 1:
            if (g_sGhost[i].m_cLocation.X < g_Console.getConsoleSize().X - 1 && EnemyUpdateRate > 0.4)
            {
                if (g_sMap.mapArray[g_sGhost[i].m_cLocation.X + 1][g_sGhost[i].m_cLocation.Y] != W)
                {
                    g_sGhost[i].m_cLocation.X++;
                    EnemyUpdateRate = 0;
                }
            }
            break;
        case 2:
            if (g_sGhost[i].m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && EnemyUpdateRate > 0.4)
            {
                if (g_sMap.mapArray[g_sGhost[i].m_cLocation.X][g_sGhost[i].m_cLocation.Y + 1] != W)
                {
                    g_sGhost[i].m_cLocation.Y++;
                    EnemyUpdateRate = 0;
                }
            }
            break;
        case 3:
            if (g_sGhost[i].m_cLocation.X > 0 && EnemyUpdateRate > 0.4)
            {
                if (g_sMap.mapArray[g_sGhost[i].m_cLocation.X - 1][g_sGhost[i].m_cLocation.Y] != W)
                {
                    g_sGhost[i].m_cLocation.X--;
                    EnemyUpdateRate = 0;
                }
            }
            break;
        case 4:
            if (g_sGhost[i].m_cLocation.Y > 0 && EnemyUpdateRate > 0.4)
            {
                if (g_sMap.mapArray[g_sGhost[i].m_cLocation.X][g_sGhost[i].m_cLocation.Y - 1] != W)
                {
                    g_sGhost[i].m_cLocation.Y--;
                    EnemyUpdateRate = 0;
                }
            }
            break;

        }

    }
    for (int i = 0; i < 4; i++)
    {
        EnemyUpdateRate2 += g_dDeltaTime;
        int random = rand() % 8 + 1;
        switch (random)
        {
        case 1:
            if (g_sGhost[3].m_cLocation.X >= g_sChar.m_cLocation.X && EnemyUpdateRate2 > 1)
            {
                if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X - 1][g_sGhost[3].m_cLocation.Y] != W)
                {
                    g_sGhost[3].m_cLocation.X -= 1;
                    EnemyUpdateRate2 = 0;
                }
            }
            break;
        case 2:
            if (g_sGhost[3].m_cLocation.Y >= g_sChar.m_cLocation.Y && EnemyUpdateRate2 > 1)
            {
                if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y - 1] != W)
                {
                    g_sGhost[3].m_cLocation.Y -= 1;
                    EnemyUpdateRate2 = 0;
                }
            }
            break;
        case 3:
            if (g_sGhost[3].m_cLocation.X <= g_sChar.m_cLocation.X && EnemyUpdateRate2 > 1)
            {
                if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X + 1][g_sGhost[3].m_cLocation.Y] != W)
                {
                    g_sGhost[3].m_cLocation.X += 1;
                    EnemyUpdateRate2 = 0;
                }
            }
            break;
        case 4:
            if (g_sGhost[3].m_cLocation.Y <= g_sChar.m_cLocation.Y && EnemyUpdateRate2 > 1)
            {
                if (g_sMap.mapArray[g_sGhost[3].m_cLocation.X][g_sGhost[3].m_cLocation.Y + 1] != W)
                {
                    g_sGhost[3].m_cLocation.Y += 1;
                    EnemyUpdateRate2 = 0;
                }
            }
            break;      
        }
    }
}

void renderGhost()
{

    for (int i = 0; i < 4; i++)
    {
        if (g_sMap.mapArray[g_sGhost[i].m_cLocation.X][g_sGhost[i].m_cLocation.Y] != W)
        {
            if (g_dElapsedTime > 1)
            {
                g_Console.writeToBuffer(g_sGhost[0].m_cLocation, (char)31, 7);
                g_sGhost[0].m_bActive = true;
            }
            if (g_dElapsedTime > 3)
            {
                g_Console.writeToBuffer(g_sGhost[1].m_cLocation, (char)31, 7);
                g_sGhost[1].m_bActive = true;
            }
            if (g_dElapsedTime > 5)
            {
                g_Console.writeToBuffer(g_sGhost[2].m_cLocation, (char)31, 7);
                g_sGhost[2].m_bActive = true;
            }
            if (g_dElapsedTime > 7)
            {
                g_Console.writeToBuffer(g_sGhost[3].m_cLocation, (char)31, 7);
                g_sGhost[3].m_bActive = true;
            }
        }
    }
}
