// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT14L
// Names: YAP HAN WAI | MEMBER_NAME_2 | MEMBER_NAME_3
// IDs: 1211101843 | MEMBER_ID_2 | MEMBER_ID_3
// Emails: 1211101843@student.mmu.edu.my | MEMBER_EMAIL_2 | MEMBER_EMAIL_3
// Phones: 011-28216621 | MEMBER_PHONE_2 | MEMBER_PHONE_3
// *********************************************************

// REMINDER:
// 1. After running the program in VSC, find the <filename>.exe file location and double-click to run it.
// 2. For people other than the host, copy and paste the code into your VSC, then repeat step one.
// 3. Remember DO NOT USE VSC AS TERMINAL TO DISPLAY THE OUTPUT.

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <climits>
#include <limits>
#include <time.h>
#include <iomanip>
#include <numeric>
#include <string>
using namespace std;

int turn = 0;

class Alien
{
private:
    int life;
    int attack;
    string nextMove;

public:
    Alien()
    {
        nextMove = "";
    }
    Alien(int i, int j)
    {
        life = i;   // Life of Alien
        attack = j; // Attack of Alien
        nextMove = "";
    }
    void setLife(int i) { life = i; } // Set life to Alien in the beginning
    int getLife() { return life; }    // Increase the life to Alien during the gameplay

    void setAttack(int i) { attack = i; } // Set attack to Alien in the beginning
    int getAttack() { return attack; }    // Increase the attack value to Alien during the gameplay

    void setNextMove(string i) { nextMove = i; }
    string getNextMove() { return nextMove; }
};

class Zombie
{
private:
    int life;
    int attack;
    int range;

public:
    Zombie() {}
    Zombie(int i, int j, int k)
    {
        life = i;   // Life of Zombie
        attack = j; // Attack of Zombie
        range = k;  // Range of Zombie
    }

    void setLife(int i) { life = i; } // Set life to Zombie in random value
    int getLife() { return life; }    // Increase the life to Zombie during the gameplay

    void setAttack(int i) { attack = i; } // Set attack to Zombie in the beginning
    int getAttack() { return attack; }    // Increase the attack value to Zombie during the gameplay

    void setRange(int i) { range = i; } // Set random range value to Zombie in the beginning
    int getRange() { return range; }    // Get the range value of zombie
};

class Coordinate
{
private:
    int x;
    int y;

public:
    Coordinate() {}
    Coordinate(int i, int j)
    {
        y = i; // My X and Y is set wrongly in the beginning. Hence I will insert Y first then X
        x = j;
    }

    void setX(int i) { x = i; }
    int getX() { return x; }

    void setY(int i) { y = i; }
    int getY() { return y; }
};

Coordinate getAlienCoordinate(int rows, int columns, string blocks[5][19]) // Maximum value for rows is from 3 to 5 //Maximum value for columns is from 7 to 19
{
    for (int i = 0; i < rows; i++) // To find where is Alien
    {
        for (int j = 0; j < columns; j++)
        {
            if (blocks[i][j] == "A")
            {
                return Coordinate(i, j);
            }
        }
    }
    return Coordinate(0, 0); // never gonna happen, just to fulfilled the condition
}

Coordinate getZombieCoordinate(int rows, int columns, string blocks[5][19], string zombieName) // To find where are Zombies and display the coordinates for each zombies
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (blocks[i][j] == zombieName)
            {
                return Coordinate(i, j);
            }
        }
    }
    return Coordinate(0, 0); // never gonna happen, just to fulfilled the condition
}

string randomBlock(bool forRock)
{
    // forRock means to random a new block to replace rock, otherwise it is random for the initial board
    if (forRock)
    {
        string possibleBlocks[2] = {"h", "p"};
        return possibleBlocks[rand() % 2];
    }
    else
    {
        string possibleBlocks[10] = {"h", "p", "r", " ", " ", " ", "^", "v", "<", ">"};
        return possibleBlocks[rand() % 10];
    }
}

void removeDotsFromBoard(int rows, int columns, string blocks[5][19]) // Remove the dots from the dot to empty space
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (blocks[i][j] == ".")
            {
                blocks[i][j] = " ";
            }
        }
    }
}

void dealDamageToZombie(int atk, string zombieName, Zombie zombies[3], int zombieCount)
{
    // get the zombie
    Zombie z = zombies[stoi(zombieName) - 1];
    if (z.getLife() - atk > 0)
    {
        turn++;
        zombies[stoi(zombieName) - 1].setLife(z.getLife() - atk);
        cout << "Dealt " << atk << " ATK to Zombie " << zombieName << endl;
        getch();
    }
    else
    {
        z.setLife(0);
        cout << "Alien killed Zombie " << zombieName << endl;
        getch();
    }
}

string updateCharacterStats(int rows, int columns, int y, int x, string blocks[5][19], Alien &alien, Zombie zombies[3], int zombieCount) // Update the stats of Alien and Zombie
{
    if (blocks[y][x] == "v" || blocks[y][x] == "<" || blocks[y][x] == "^" || blocks[y][x] == ">")
    {
        cout << "Alien will gain +20 ATK and will change its direction to (" << blocks[y][x] << ") after one move." << endl; // Gain damage if take arroww, "^", "v", "<", ">"
        alien.setAttack(alien.getAttack() + 20);                                                                             // Increase damage by 20
        alien.setNextMove(blocks[y][x]);
    }
    else if (blocks[y][x] == "p") // Gain damage if take pod
    {
        cout << "Alien picks up a pod, +10 ATK!" << endl; // Increase damage by 10
        alien.setAttack(alien.getAttack() + 10);
    }
    else if (blocks[y][x] == "h") // Gain health if take h
    {
        int newLife = alien.getLife() + 20; // Increase health by 20
        if (newLife > 100)
        {
            alien.setLife(100);
            cout << "Alien picks up a health pack, restored to max HP!" << endl; // Cant increase any health because it is Max
        }
        else
        {
            alien.setLife(newLife);
            cout << "Alien picks up a health pack, 20 HP!" << endl; // Increase health by 20
        }
    }
    else if (blocks[y][x] == "r")
    {
        alien.setNextMove("");
        blocks[y][x] = randomBlock(true);
        cout << "Alien hits a rock, turn ended!" << endl; // Turn will end if hits the rock
        turn++;
        removeDotsFromBoard(rows, columns, blocks);
        return "r";
    }
    else if (blocks[y][x] == "1" || blocks[y][x] == "2" || blocks[y][x] == "3")
    {
        alien.setNextMove("");
        cout << "Alien hits a zombie, dealing damage to zombie & stop!" << endl;

        dealDamageToZombie(alien.getAttack(), blocks[y][x], zombies, zombieCount);
        removeDotsFromBoard(rows, columns, blocks);
        alien.setAttack(0);
        // int zcLife = zombie.
        return "z";
    }

    return "";
}

void alienMoveRight(int rows, int columns, int y, int x, string blocks[5][19], Alien &alien, Zombie zombies[3], int zombieCount) // For move right part if Alien hits the border
{
    if (x + 1 == columns)
    {
        turn++;
        alien.setNextMove("");
        cout << "Alien hits a border and ended his turn." << endl;
        cout << "Press any key to continue..." << endl;
        removeDotsFromBoard(rows, columns, blocks);
        getch();
    }
    else
    {
        string mov = updateCharacterStats(rows, columns, y, x + 1, blocks, alien, zombies, zombieCount);
        if (mov == "")
        {
            blocks[y][x + 1] = "A";
            blocks[y][x] = ".";
            cout << "Alien will move right." << endl;
        }
        cout << "Press any key to continue..." << endl;
        getch();
    }
}

void alienMoveDown(int rows, int columns, int y, int x, string blocks[5][19], Alien &alien, Zombie zombies[3], int zombieCount) // For move down part if Alien hits the border
{
    if (y + 1 == rows)
    {
        turn++;
        alien.setNextMove("");
        cout << "Alien hits a border and ended his turn." << endl;
        cout << "Press any key to continue..." << endl;
        removeDotsFromBoard(rows, columns, blocks);
        getch();
    }
    else
    {
        string mov = updateCharacterStats(rows, columns, y + 1, x, blocks, alien, zombies, zombieCount);
        if (mov == "")
        {
            blocks[y + 1][x] = "A";
            blocks[y][x] = ".";
            cout << "Alien will move down." << endl;
        }
        cout << "Press any key to continue..." << endl;
        getch();
    }
}

void alienMoveLeft(int rows, int columns, int y, int x, string blocks[5][19], Alien &alien, Zombie zombies[3], int zombieCount) // For move left part if Alien hits the border
{
    if (x == 0)
    {
        turn++;
        alien.setNextMove("");
        cout << "Alien hits a border and ended his turn." << endl;
        cout << "Press any key to continue..." << endl;
        removeDotsFromBoard(rows, columns, blocks);
        getch();
    }
    else
    {
        string mov = updateCharacterStats(rows, columns, y, x - 1, blocks, alien, zombies, zombieCount);
        if (mov == "")
        {
            blocks[y][x - 1] = "A";
            blocks[y][x] = ".";
            cout << "Alien will move left." << endl;
        }
        cout << "Press any key to continue..." << endl;
        getch();
    }
}

void alienMoveUp(int rows, int columns, int y, int x, string blocks[5][19], Alien &alien, Zombie zombies[3], int zombieCount) // For move up part if Alien hits the border
{
    if (y == 0)
    {
        turn++;
        alien.setNextMove("");
        cout << "Alien hits a border and ended his turn." << endl;
        cout << "Press any key to continue..." << endl;
        removeDotsFromBoard(rows, columns, blocks);
        getch();
    }
    else
    {
        string mov = updateCharacterStats(rows, columns, y - 1, x, blocks, alien, zombies, zombieCount);
        if (mov == "")
        {
            blocks[y - 1][x] = "A";
            blocks[y][x] = ".";
            cout << "Alien will move up." << endl;
        }
        cout << "Press any key to continue..." << endl;
        getch();
    }
}

void alienMove(int rows, int columns, string blocks[5][19], string command, Alien &alien, Zombie zombies[3], int zombieCount)    //Alien move 
{
    // Find out where is the alien
    Coordinate alienCoordinate = getAlienCoordinate(rows, columns, blocks);
    string decidedAction;

    if (command == ">")
    {
        alienMoveRight(rows, columns, alienCoordinate.getY(), alienCoordinate.getX(), blocks, alien, zombies, zombieCount);         //Rigth
    }
    else if (command == "v")
    {
        alienMoveDown(rows, columns, alienCoordinate.getY(), alienCoordinate.getX(), blocks, alien, zombies, zombieCount);          //Down
    }
    else if (command == "<")
    {
        alienMoveLeft(rows, columns, alienCoordinate.getY(), alienCoordinate.getX(), blocks, alien, zombies, zombieCount);          //Left
    }
    else
    {
        alienMoveUp(rows, columns, alienCoordinate.getY(), alienCoordinate.getX(), blocks, alien, zombies, zombieCount);            //Right
    }
}

bool zombieCanAttackAlien(int alienX, int alienY, int zombieX, int zombieY, int range)       //bool to find where zombie can attack zombie or not
{
    int distX = alienX - zombieX;
    int distY = alienY - zombieY;
    if (distX < 0)
    {
        distX = -distX;
    }
    if (distY < 0)
    {
        distY = -distY;
    }
    if (range + 2 > distX + distY)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void zombieMove(int rows, int columns, int x, int y, string blocks[5][19], Zombie zombie, int zombieName)                       //To let zombie move
{
    // try up, down, left, right in sequence
    if (y != 0 && blocks[y - 1][x] != "1" && blocks[y - 1][x] != "2" && blocks[y - 1][x] != "3" && blocks[y - 1][x] != "A")
    {
        cout << "Zombie " << zombieName << " moved up." << endl;
        blocks[y - 1][x] = to_string(zombieName);
        blocks[y][x] = " ";
    }
    else if (y + 1 != rows && blocks[y + 1][x] != "1" && blocks[y + 1][x] != "2" && blocks[y + 1][x] != "3" && blocks[y + 1][x] != "A")
    {
        cout << "Zombie " << zombieName << " moved down." << endl;
        blocks[y + 1][x] = to_string(zombieName);
        blocks[y][x] = " ";
    }
    else if (x != 0 && blocks[y][x - 1] != "1" && blocks[y][x - 1] != "2" && blocks[y][x - 1] != "3" && blocks[y][x - 1] != "A")
    {
        cout << "Zombie " << zombieName << " moved left." << endl;
        blocks[y][x - 1] = to_string(zombieName);
        blocks[y][x] = " ";
    }
    else if (x + 1 != columns && blocks[y][x + 1] != "1" && blocks[y][x + 1] != "2" && blocks[y][x + 1] != "3" && blocks[y][x + 1] != "A")
    {
        cout << "Zombie " << zombieName << " moved right." << endl;
        blocks[y][x + 1] = to_string(zombieName);
        blocks[y][x] = " ";
    }
    else
    {
        cout << "Zombie " << zombieName << " has no space to move, skipping its turn!" << endl;
    }
}

int main()
{
    cout << "Default Game Settings" << endl; // Main page
    cout << "------------------------------------------" << endl;

    srand(time(NULL)); // Random accordingly to the time(NULL)

    // Rows
    int dsg1 = 3;          // dsg1 is Rows
    dsg1 = rand() % 3 + 3; // Random it and modulus 3 and + 3 the random generated number of rows is minimum 3, maximum 5
    while (dsg1 % 2 == 0)  // To ensure it is an even number
    {
        dsg1 = rand() % 3 + 3;
    }
    cout << "Board Rows    : " << dsg1 << endl; // Display

    // Columns
    int dsg2 = 9;           // dsg2 is Columns
    dsg2 = rand() % 13 + 7; // Random it and modulus 13 and + 7 the random generated number of columns is minimum 7, maximum 19
    while (dsg2 % 2 == 0)   // To ensure it is an even number
    {
        dsg2 = rand() % 13 + 7;
    }
    cout << "Board Columns : " << dsg2 << endl; // Display

    // Zombies
    int dsg3;              // dsg3 isZombies
    dsg3 = rand() % 3 + 1; // Random it and modulus 3 and + 1 the random generated number of zombies is minimum 1, maximum 3

    cout << "Zombie Count  : " << dsg3 << endl // Display
         << endl;

    string dsg4;
    cout << "Do you wish to change the game settings (y/n): "; // Display
    cin >> dsg4;                                               // Let user input the value
    system("CLS");

    if (dsg4 == "y") // IF statement that if user wish to change the game settings
    {
        cout << "Board Setting" << endl;               // Display
        cout << "---------------------------" << endl; // Display
        cout << "Enter Rows => ";                      // Display
        cin >> dsg1;
        while (dsg1 % 2 == 0 || dsg1 > 5) // To ensure it is an even number and not greater than 5
        {
            cout << "Please re-enter an ODD NUMBER (<=5): "; // Display
            cin >> dsg1;                                     // Let user input the value
        }
        cout << endl
             << endl;

        cout << "Board Setting" << endl;               // Display
        cout << "---------------------------" << endl; // Display
        cout << "Enter Columns => ";                   // Display
        cin >> dsg2;                                   // Let user input the value
        while (dsg2 % 2 == 0 || dsg2 > 20)             // To ensure it is an even number and not greater than 20
        {
            cout << "Please re-enter an ODD NUMBER (<=19): "; // Display
            cin >> dsg2;                                      // Let user input the value
        }
        cout << endl
             << endl;

        cout << "Zombie Settings" << endl;             // Display
        cout << "---------------------------" << endl; // Display
        cout << "Enter number of zombies => ";         // Display
        while (true)
        {

            cin >> dsg3;
            if (dsg3 > 3)
            {
                cout << "Please re-enter the Zombie count (<=3): "; // Let user input the value and ensure that the zombie value is not greater than 3
            }
            else
            {
                break;
            }
        }

        cout << endl
             << endl;
        cout << "Settings Updated." << endl; // Display

        cout << "Press any key to Continue ";
        getch();
    }

    // string blocks[dsg1][dsg2];
    string blocks[5][19]; // Maximum value of the game board is 5 x 19 which 5 is rows and 19 is columns

    for (int i = 0; i < dsg1; i++)
    {
        for (int j = 0; j < dsg2; j++)
        {
            blocks[i][j] = randomBlock(false);
        }
    }

    blocks[(dsg1 + 1) / 2 - 1][(dsg2 + 1) / 2 - 1] = "A"; // To put where Alien is as "A" in the middle of game board

    Zombie zombies[3];
    Alien alien = Alien(100, 0);

    for (int i = 1; i <= dsg3; i++)
    {
        int xc = rand() % dsg2;
        int yc = rand() % dsg1;

        while (blocks[yc][xc] == "A" || blocks[yc][xc] == "1" || blocks[yc][xc] == "2")
        {
            xc = rand() % dsg2;
            yc = rand() % dsg1;
        }

        blocks[yc][xc] = to_string(i);

        zombies[i - 1] = Zombie((rand() % 4 + 2) * 50, (rand() % 4 + 2) * 5, (rand() % 3 + 1)); //*50 is to set the life value for Zombie for bigger value, *5 is to set the attack value
    }

    int whoseTurn = 0;

    while (true) // while loop for gameplay start here
    {
        system("CLS");

        cout << " ||| Alien vs Zombie ||| " << endl; // Game title

        cout << endl;
        cout << "    ";

        for (int col = 0; col < dsg2; col++) // Column will be display as +-
        {
            cout << "+-";
        }
        cout << "+"; // Add a + behind the "+-" to fancy it
        cout << endl;

        for (int i = 1; i <= dsg1; i++) // row
        {
            if (i < 10)
            {
                cout << "  ";
            }
            else
            {
                cout << " ";
            }
            cout << i << " ";

            for (int j = 0; j < dsg2; j++) // column
            {
                cout << "|" << blocks[i - 1][j];
            }
            cout << "|" << endl;
            cout << "    ";

            for (int k = 0; k < dsg2; k++) // column
            {
                cout << "+-";
            }

            cout << "+" << endl;
        }

        if (dsg2 >= 10)
        {
            cout << "     ";
            for (int i = 0; i < dsg2; i++)
            {
                if (i < 9)
                {
                    cout << "  ";
                }

                else
                {
                    cout << "1 ";
                }
            }
            cout << endl;
        }

        cout << "     ";

        for (int i = 1; i <= dsg2; i++)
        {
            cout << i % 10;
            cout << " ";
        }

        cout << endl
             << endl;

        cout << "Alien   : Life " << alien.getLife() << ", Attack   " << alien.getAttack() << endl;           //To display the details under the game board to show life, attack for alien 

        for (int i = 0; i < dsg3; i++)
        {
            cout << "Zombie " << i + 1 << ": Life " << zombies[i].getLife() << ", Attack  " << zombies[i].getAttack() << ", Range  " << zombies[i].getRange() << endl;   //To display the details under the game board to show life, attack for alien 
        }

        cout << endl;

        string command;

        string cmup = "up";
        string cmdown = "down";
        string cmleft = "left";
        string cmright = "right";

        // Means it is alien's turn
        if (turn % (dsg3 + 1) == 0)
        {
            if (alien.getNextMove() == "")
            {
                cout << "command > ";
                cin >> command;

                while (command != cmup && command != cmdown && command != cmleft && command != cmright)         //To determine whether user type in correct or not
                {
                    cout << "Please type in a proper input (up, down, left, right) => ";
                    cin >> command;
                }

                if (command == cmup)
                {
                    alien.setNextMove("^");                                                                 //Up
                    alienMove(dsg1, dsg2, blocks, alien.getNextMove(), alien, zombies, dsg3);
                }
                else if (command == cmleft)
                {
                    alien.setNextMove("<");                                                                  //Left
                    alienMove(dsg1, dsg2, blocks, alien.getNextMove(), alien, zombies, dsg3);
                }
                else if (command == cmright)
                {
                    alien.setNextMove(">");
                    alienMove(dsg1, dsg2, blocks, alien.getNextMove(), alien, zombies, dsg3);               //Right
                }
                else
                {
                    alien.setNextMove("v");
                    alienMove(dsg1, dsg2, blocks, alien.getNextMove(), alien, zombies, dsg3);               //Down
                }
            }
            else
            {
                cout << "Alien will continue moving." << endl;
                getch();
                alienMove(dsg1, dsg2, blocks, alien.getNextMove(), alien, zombies, dsg3);
            }
        }
        else                                                                                                            //This is the part where zombie move and attack Alien if is inside range
        {
            int zombieTurn = turn % (dsg3 + 1);
            int deadZombies = 0;
            cout << "Now its Zombie " << zombieTurn << "'s turn." << endl;
            Coordinate alienCoord = getAlienCoordinate(dsg1, dsg2, blocks);
            Coordinate zombieCoord = getZombieCoordinate(dsg1, dsg2, blocks, to_string(zombieTurn));
            cout << "Coordinate of Zombie " << zombieTurn << " is (" << zombieCoord.getX() + 1 << ", " << zombieCoord.getY() + 1 << ")" << endl;
            zombieMove(dsg1, dsg2, zombieCoord.getX(), zombieCoord.getY(), blocks, zombies[zombieTurn - 1], zombieTurn);
            if (zombieCanAttackAlien(alienCoord.getX(), alienCoord.getY(), zombieCoord.getX(), zombieCoord.getY(), zombies[zombieTurn - 1].getRange()))
            {
                cout << "Zombie " << zombieTurn << " is in range to deal " << zombies[zombieTurn - 1].getAttack() << " ATK to Alien." << endl;
                if (alien.getLife() - zombies[zombieTurn - 1].getAttack() <= 0)
                {
                    cout << "Game over." << endl;
                }
                else
                {
                    alien.setLife(alien.getLife() - zombies[zombieTurn - 1].getAttack());
                }
            }
            turn++;
            getch();
        }
    }

    int lllll;
    cin >> lllll;
}
