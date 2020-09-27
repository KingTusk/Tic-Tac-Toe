#include <iostream>
#include <string>

bool winCon(char table[], char pturn); //this function is used for checking the win conditions
void printTable(char table[], int tablesize); //this function i sused to print the tic-tac-tow table
int getRandomNumber(int min, int max); //this function is used to get a random number
bool checkForError(); //this function checks for error in the input
int AIchoice(char table[], int tabesize); //this function is used to determine which tile the AI will choose


struct player { //this struct is used to store values on each player
    std::string pname = "no name given";
    char pid = 'n';
}playerx, playero, playerAI, playervsAI;


int main() {
    bool cont = true;
    bool AImode = false;
    std::string name = "no name given";
    char table[9] = { '1','2','3','4','5','6','7','8','9' };
    char pturn = 'o';
    int choice = 0;
    bool win = false;
    bool draw = true;
    int tablesize = sizeof(table) / sizeof(table[0]);

    std::cout << "Welcome to tic tac toe! " << std::endl;
    std::cout << "Do you want to play vs another player or an AI? type 0 for player and 1 for AI: "; //makes players choose game mode, AI or duo
    std::cin >> AImode;
    do { //this do while loop runs until a valid answer is given
        cont = true;
        if (checkForError()) { //ensures valid input
            std::cout << "Invalid input, please try again: ";
            cont = false;
            std::cin >> AImode;
        }
    } while (!cont);
    std::cin.ignore(32767, '\n');//clears cin for use of getline later
    if (AImode) {
        char answer = 'y';

        std::cout << "Do you want to go first? (y/n) ";
        std::cin >> answer;
        std::cin.ignore(32767, '\n');//clears cin for use of getline later
        if (answer == 'y' || answer == 'Y') { //this if else determines who will go first
            playerAI.pid = 'o';
            playervsAI.pid = 'x';
        }
        else if (answer == 'n' || answer == 'N') {
            playerAI.pid = 'x';
            playervsAI.pid = 'o';
        }
        playerAI.pname = "AI";
        std::cout << "Please enter your name: \n";
        std::getline(std::cin, playervsAI.pname); //saves player name

    }
    else {
        std::cout << "Player x please give your name: \n";
        std::getline(std::cin, playerx.pname); //saves player name

        std::cout << "Player o please give your name: \n";
        std::getline(std::cin, playero.pname); //saves player name

        playerx.pid = 'x';
        playero.pid = 'o';
    }

    do { //this do while loop runs until there is a winner, or there is a draw

        if(AImode){//this if else statment determines whether it's player vs AI or player vs player
            draw = true;
            bool pchoice = true;
            if (pturn == playerAI.pid) { //if else determines whose turn it is
                pturn = playervsAI.pid;
            }
            else if (pturn == playervsAI.pid) {
                pturn = playerAI.pid;
            }
            else {
                std::cout << "There was an error determining player turn, terminating application.";
                return 0;
            }
            name = playervsAI.pname;
            printTable(table, tablesize); //prints table
            if (pturn == playervsAI.pid) { //This code runs on players turn
                do { //this do while loop runs until the player chooses a valid position
                    pchoice = true,
                        std::cout << "\nPlayer " << name << " it is your turn, pick a number";
                    std::cin >> choice;
                    if(checkForError()) { //checks for invalid input and fixes any issues
                        std::cout << "Please only use numbers!";
                        pchoice = false;
                    }
                    else if (table[choice - 1] == playerx.pid || table[choice - 1] == playero.pid) { //Checks whether or not chosen spot has been taken
                        std::cout << "Spot taken, try again.\n";
                        pchoice = false;
                    }
                } while (!pchoice);
            }
            else { //this code runs in AIs turn
                choice = AIchoice(table, tablesize); //this code gives AI choice of tile
            }
            table[choice - 1] = pturn;

            win = winCon(table, pturn); //checks whether or not there is a winner
            for (int i = 0; i < tablesize; i++) { //determines whether or not the game is a draw
                if (table[i] != 'x' && table[i] != 'o') {
                    draw = false;
                }
            }
            system("cls");
        }

        else {//this is part of the if else statement to determine player vs player or pleyer vs AI
            draw = true;
            bool pchoice = true; 
            if (pturn == playerx.pid) { //if else determines whose turn it is
                pturn = playero.pid;
                name = playero.pname;
            }
            else if (pturn == playero.pid) {
                pturn = playerx.pid;
                name = playerx.pname;
            }
            else {
                std::cout << "There was an error determining player turn, terminating application.";
                return 0;
            }
            printTable(table, tablesize); //prints table
            do { //this do while loop runs until the player chooses a valid position
                pchoice = true,
                std::cout << "\nPlayer " << name << " it is your turn, pick a number: ";
                std::cin >> choice;
                if (checkForError()) { //checks for invalid inout and fixes any issues
                    std::cout << "Please only use numbers!";
                    pchoice = false;
                }
                else if (table[choice - 1] == playerx.pid || table[choice - 1] == playero.pid) { //Checks whether or not chosen spot has been taken
                    std::cout << "Spot taken, try again.\n";
                    pchoice = false;
                }
            } while (!pchoice);
            table[choice - 1] = pturn;

            win = winCon(table, pturn);
            for (int i = 0; i < tablesize; i++) { //determines whether or not the game is a draw
                if (table[i] != 'x' && table[i] != 'o') {
                    draw = false;
                }
            }
            system("cls");
        }
    } while (!win&&!draw);
    printTable(table, tablesize);
    if (win) { //if else statement declares winner or draw
        std::cout << "\nCongratulations " << name << ", You have won the game!";
    }
    else {
        std::cout << "\nGame is a draw! Well played";
    }
}

int AIchoice(char table[], int tablesize) {
    //the code below generates a random number and checks whether or not the spot has been taken
    int choice = 0;
    bool free = true;
    do {
        free = true;
        choice = getRandomNumber(1, tablesize);
        if (table[choice - 1] == playerAI.pid || table[choice - 1] == playervsAI.pid) {
            free = false;
        }
    } while (!free);
    return choice;

}

bool checkForError() {//Checks whether if the input was an invalid value and fixes potential issues caused by this
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return true;
    }
    else {
        return false;
    }
}

bool winCon(char table[], char pturn) {
    //below if statements checks for win conditions after every placed symbol
    bool win = false;
    if (table[0] == pturn && table[1] == pturn && table[2] == pturn) {
        win = true;
    }
    else if (table[3] == pturn && table[4] == pturn && table[5] == pturn) {
        win = true;
    }
    else if (table[6] == pturn && table[7] == pturn && table[8] == pturn) {
        win = true;
    }
    else if (table[0] == pturn && table[3] == pturn && table[6] == pturn) {
        win = true;
    }
    else if (table[1] == pturn && table[4] == pturn && table[7] == pturn) {
        win = true;
    }
    else if (table[2] == pturn && table[5] == pturn && table[8] == pturn) {
        win = true;
    }
    else if (table[0] == pturn && table[4] == pturn && table[8] == pturn) {
        win = true;
    }
    else if (table[2] == pturn && table[4] == pturn && table[6] == pturn) {
        win = true;
    }
    return win;
}

void printTable(char table[], int tablesize) { //Prints every element of the table in rows of three
    for (int i = 0; i < tablesize; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "|\n\n";
        }
        std::cout << "|\t"<<table[i] << "\t";
    }
    std::cout << "|";
}

int getRandomNumber(int min, int max) //code is from learncpp.com, it produces a random number between min and max
{
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}