#include "Mario.h"
#include "TheDonkykongGame.h"
#include <conio.h> // For _kbhit() and _getch()


char getCharXY(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ידית למסך הקונסולה
    CHAR_INFO charInfo;
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT readRegion = { x, y, x, y }; // הגדרת האזור לקריאה (תו יחיד)

    COORD bufferSize = { 1, 1 }; // גודל האזור לקריאה (1x1 תווים)

    // קריאה מהמסך
    if (ReadConsoleOutput(hConsole, &charInfo, bufferSize, bufferCoord, &readRegion)) {
        return charInfo.Char.AsciiChar; // החזרת התו שנמצא במיקום
    }

    return ' '; // במקרה של שגיאה, מחזירים רווח
}
char Mario::getCharAt(int x, int y)
{

    // Handle for the console screen buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Define a CHAR_INFO structure to hold the character information
    CHAR_INFO charInfo;

    // Set the buffer coordinates for the area to read (we're reading 1 character)
    COORD bufferCoord = { 0, 0 };

    // Define the region to read (a single character at (x, y))
    SMALL_RECT readRegion = { x, y, x, y };

    // Set the size of the buffer to read (1x1 character)
    COORD bufferSize = { 1, 1 };

    // Read the console output at the given coordinates
    if (ReadConsoleOutput(hConsole, &charInfo, bufferSize, bufferCoord, &readRegion)) {
        // Return the ASCII character if the read was successful
        return charInfo.Char.AsciiChar;


        // Return a space if there was an error reading the character
        return ' ';
    }
}
TheDonkykongGame game;

void Mario::move() {
    
    static char savedChar = ' '; // Saved character from Mario's previous position
    static int jumpStep = 0;     // Tracks the current step of the jump sequence
    static int jumpDirection = 0; // Direction during the jump (2: LEFT, 3: RIGHT)
    static int prevDirection = 3; // Tracks Mario's last horizontal direction (default to RIGHT)

    int prevX = body[0].getX(); // Mario's current position
    int prevY = body[0].getY();

    int nextX = prevX;
    int nextY = prevY;

    

    // Handle jumping logic
    if (jumpStep > 0) {
        jumping = true;  // Mario is in the middle of a jump
        // Execute jump sequence
        if (jumpStep == 1) {
            nextY -= 2; // Jump up by 2 units
        }
        else if (jumpStep >= 2 && jumpStep <= 4) {
            nextX += (jumpDirection == 2 ? -1 : 1); // Move horizontally during the jump
        }
        jumpStep++;
        if (jumpStep > 4) {
            jumpStep = 0; // Reset jump after completion
            jumping = false;  // Mario is no longer jumping
            direction = prevDirection;  // Set direction back to previous value
        }
    }
    else {
        // Handle normal movement
        switch (direction) {
        case 0: // UP
            if (getCharAt(prevX, prevY) == 'H' || getCharAt(prevX, prevY - 1) == 'H') {
                // Climbing up a ladder
                nextY--;
            }
            else if (getCharAt(prevX, prevY + 1) == '=' || getCharAt(prevX, prevY + 1) == '<' || getCharAt(prevX, prevY + 1) == '>' || getCharAt(prevX, prevY + 1) == 'Q') {
                // Start jumping if Mario is on a platform
                jumpStep = 1;
                jumpDirection = prevDirection; // Use last recorded horizontal direction
                return; // Begin jump sequence; stop further processing this frame
            }
            break;

        case 1: // DOWN
            if (getCharAt(prevX, prevY + 1) == 'H') {
                nextY++;
            }
            break;

        case 2: // LEFT
            nextX--;
            prevDirection = 2; // Update last direction to LEFT
            break;

        case 3: // RIGHT
            nextX++;
            prevDirection = 3; // Update last direction to RIGHT
            break;
        }
    }
    if (getCharAt(nextX, nextY) == 'p')
    {
        hammer = true;
       // printf("gg");
    }
    /*if (checkBarrelCollision())
    {
        if (hammer) {
            
        }
        else {
            loseLife();
        }
        return;
    }*/
    
    else
    {
        if (checkBarrelCollision())
        {
           
            if (attack)
            {
                
                destroyNearbyEnemies();
                score = score + 20;
                attack = false;
                
            }
            else
            {
                
                loseLife();
                return;
            }

        }
    }
    // Now we only check for falling if Mario is NOT jumping and has finished jumping (jumpStep == 0)
    if (!jumping && jumpStep == 0 && checkFall()) {
        // Mario is falling, so lose a life
        loseLife();
        return;  // Exit early, no need to process other movement logic
    }

    // Check if Mario is going out of bounds
    if (nextX < 1 || nextX > 79 || nextY < 1 || nextY > 25) {
        return; // Prevent out-of-bounds movement
    }

    // Get the characters at relevant positions
    char nextChar = getCharAt(nextX, nextY);
    char belowChar = getCharAt(prevX, prevY + 1);

    if (nextChar == '$') {
        system("cls"); // Clear the screen
   
        //std::cout << "\n\n\t\tYou Won! Mario saved Pauline!\n\n";
        reached == true;
       // exit(0); // End the game
        game.nextLevel(); // Load the next level
        //resetPosition(game.mX, game.mY);
        
        resetPosition(startingX,startingY);

        return;
    }

    // Determine if Mario can move
    bool canMove = false;

    if (jumpStep > 0) {
        // During a jump, allow movement
        canMove = true;
    }
    else {
        // Regular movement logic
        if ((direction == 0 || direction == 1) && nextChar == 'H') {
            // Climbing up or down a ladder
            canMove = true;
        }
        else if ((direction == 2 || direction == 3) &&
            (belowChar == '=' || belowChar == '<' || belowChar == '>' || belowChar == 'H' || belowChar == 'Q')) {
            // Moving left or right on supported ground
            canMove = true;
        }
        else if (belowChar == ' ' && nextChar != 'H') {
            // Falling logic: no support below
            nextY++;
            canMove = true;
        }
    }

    if (canMove) {
        // Restore the character Mario was standing on
        if (savedChar == 'H') {
            body[0].draw('H'); // Ensure ladder remains if Mario leaves it
        }
        else {
            body[0].draw(savedChar); // Restore the saved character
        }

        // Save the character at Mario's new position
        char newCharAtPosition = getCharAt(nextX, nextY);

        if (jumpStep > 0 && newCharAtPosition == 'H') {
            // If jumping into a ladder, preserve the 'H' character
            savedChar = 'H';
        }
        else {
            savedChar = newCharAtPosition; // Save the new position's character
        }

        // Update Mario's position
        body[0].setX(nextX);
        body[0].setY(nextY);
    }

    body[0].draw(Signs::MARIO);

    // Display the current number of lives
    displayLives();
}
// Draw Mario at the new po
void Mario::draw(char symbol) {
    // This function draws Mario at the current position
   // std::cout << "Drawing Mario at position (" << body[0].getX() << ", " << body[0].getY() << ")\n";
    // Your existing logic to display Mario using the symbol (e.g., 'M')
}

bool Mario::checkBarrelCollision() {
    int x = body[0].getX();
    int y = body[0].getY();

    // Check current position and surrounding positions
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (getCharAt(x + dx, y + dy) == 'O' || getCharAt(x + dx, y + dy) == 'x') {
                return true;
            }
        }
    }
    return false;
}

bool Mario::checkFall() {
    int x = body[0].getX();
    int y = body[0].getY();

    // We check if Mario is too high from the ground (say 4 or more units above the floor)
    for (int i = 1; i <= 4; ++i) {
        char belowChar = getCharAt(x, y + i); // Check the 4 positions below Mario
        if (belowChar != ' ') {
            return false; // Mario is not falling, something is below him
        }
    }
    return true; // Mario is falling, there's no support below for 4 units
}

void Mario::loseLife() {
    if (!marioWon)
    {
        lives--;

        if (lives <= 0) {
            system("cls");
            std::cout << "Game Over!" << std::endl;
            //exit(0);
        }
    }

    char currentChar = getCharAt(body[0].getX() + 1, body[0].getY());
    if (currentChar == 'H') {
        // If Mario is on a ladder, redraw the ladder instead of an empty space

        //body[0].draw('H');
    }
    else {
        body[0].draw(' ');
    }

    direction = 4;
    resetPosition(startingX,startingY);
    draw(Signs::MARIO);
}


void Mario::resetPosition(int x, int y) {
    // Set Mario's position to the starting point
    body[0].setX(x);
    body[0].setY(y);
    
    
}

Mario::Mario() : lives(3) , score(0)
{
    // Initialize Mario's position
   // body[0].setX(startingX);  // Set Mario's X position
    //body[0].setY(startingY);  // Set Mario's Y position
    resetPosition(startingX,startingY);
}

void Mario::displayLives() const {
   
    std::string s = "off";

    // Output the string to the console
    
    if (hammer == true)
    {
        s = "on ";
    }
    
    
    gotoxy(livesX, livesY);// Move the cursor to the top-left of the screen
    //std::cout << "Lives: " << lives << std::flush;  // Display the lives count
    printf("Lives:%d",lives);
    gotoxy(livesX, livesY +1);
    printf("Score:%d", score);
    gotoxy(livesX, livesY + 2);
    printf("Hammer:%s", s.c_str());
    
  
    
    
    

}

int Mario::getDirection(char key)
{
    for (int i = 0; i < 5; ++i)
    {
        if (key == arrowKeys[i])
            return i;
    }
    return -1;
}

bool Mario::setHammer()
{
    return hammer;
}
void Mario::setAttack(bool value) {
    attack = value; // Set the attack state
}

void Mario::destroyNearbyEnemies() 
{
    int x = body[0].getX(); // Mario's current X position
    int y = body[0].getY(); // Mario's current Y position

    // Check and "destroy" nearby barrels or ghosts
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            char nearbyChar = getCharAt(x + dx, y + dy);

            // Check for barrels or ghosts ('O' and 'x' as examples)
            if (nearbyChar == 'O' || nearbyChar == 'x') 
            {
                
                // Replace the character with an empty space
                gotoxy(x + dx, y + dy); // Move cursor to the enemy's position
                std::cout << " "; // Replace with a space

                // Prevent recursive calls, avoid calling destroyNearbyEnemies() again here
                break;
            }
        }
    }
}


