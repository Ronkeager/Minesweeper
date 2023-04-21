/******************************************************************************
Minesweeper in C++

Documentation:
Welcome to Minesweeper! This is a simple 10x10 game where you sweep mines (self explanatory).

The greetPlayer() fuction explains the rules and controls of the game. Once enter is pressed,
the gamestate variable will be changed.

gamestate 0 = Main Menu
          1 = Load new game
          2 = In-game
          3 = Controls
          4 = Unload current game and load new game
          5 = Win screen
          6 = Loss screen

The mine detection system is also very complex. When generating the map and rendering it, different blockstates get different minelocation[] values.

minelocation[] = 1 = hidden non-mine
minelocation[] = 2 = hidden mine
minelocation[] = 3 = user pressed non-mine
minelocation[] = 4 = user pressed mine! BOOM!

*******************************************************************************/

#include <iostream>
#include <Windows.h>
#include <climits>
#include <cstdlib>

using namespace std;

bool game_running = true;
bool gameplayloop = true;
bool globalbool = false;
string user_input;
int gamestate = 0;
int current_gamestate = 0;
int global_input_int = 0;
int check_if_game_won;

int minelocation[10][10] = {};

void controls() {
    std::cout << "This is a 10x10 game where you choose how many mines that are randomly placed on the board. \n";
    std::cout << "You need to guess where the mines are based on numbers that pop up.\n";
    std::cout << "To input what tile to click, input it's coordinates.\n";
    std::cout << "After you do this, the tile will be replaced with a number indicating the amount\nof neighbouring mines.\n";
    std::cout << "When all mines are defused, you have won, but you will die if the input matches a bomb.\n\n";
    std::cout << "If you at any point get stuck/forget the controls, type 'help' to see all actions.\n\n";
    std::cout << "Controls and commands: \nInput coordinates to guess tile\n'help' to see controls in-game\n";
    std::cout << "'restart' to start a new game\n\n";
    std::cout << "# are uncovered tiles and numbers, well, you already know that.\nGood luck! You are gonna need it.\n\n";
}

void greetPlayer() {
    bool continue_loop = true;

    while (continue_loop) {
        std::cout << "Welcome to minesweeper! Do you want to hear the rules? (Y/N)\n";
        std::cin >> user_input;

        if (user_input == "y") {
            controls();
            continue_loop = false;
        }
        else if (user_input == "n") {
            continue_loop = false;
        }
        else {
            continue_loop = true;
        }
    }
}

void generateMap(int mines_remaining) {
    int mine_pos_x; int mine_pos_y;
    srand((unsigned)time(NULL));

    while (mines_remaining > 0) {
        mine_pos_x = rand() % 10;
        mine_pos_y = rand() % 10;

        if (minelocation[mine_pos_y][mine_pos_x] == 0) {
            minelocation[mine_pos_y][mine_pos_x] = 2;
            --mines_remaining;
        }
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (minelocation[i][j] == 0) {
                minelocation[i][j] = 1;
            }
        }
    }
    gamestate = 2;
}

void gameRenderer() {
    int surrounding_mines = 0;
    int posx = 0;
    int posy = 0;

    std::cout << "   ABCDEFGHIJ\n\n";

    for (int y = 0; y < 10; ++y) {
        std::cout << y << "  ";

        for (int x = 0; x < 10; ++x) {
            switch (minelocation[y][x]) {
                case 3:
                    for (int offset_x = -1; offset_x < 2; ++offset_x) {
                        for (int offset_y = -1; offset_y < 2; ++offset_y) {
                            posx = x + offset_x;
                            posy = y + offset_y;

                            //Check that tile is valid and within size constraints
                            if (posx >= 0 && posx < 10 && posy >= 0 && posy < 10) {
                                if (minelocation[posy][posx] == 2 or minelocation[posy][posx] == 4  ) {
                                    ++surrounding_mines;    
                                }
                            }
                        }
                    }

                    if (surrounding_mines == 0) {
                        std::cout << " ";
                    }
                    else {
                        std::cout << surrounding_mines;
                    }

                    surrounding_mines = 0;
                    break;
                case 4:
                    std::cout << "x";
                    gamestate = 6;
                    break;
                case 2:
                    std::cout << "#";
                    break;
                case 1:
                    std::cout << "#";
                    break;
            }
        }

        std::cout << "\n";
    }

}

void inputDecoder() {
    string user_input;
    int posx = 0;
    int posy = 0;

    std::cout << "\n What will you do?\n";

    std::cin >> user_input;

    if (user_input.size() == 2) {
        switch (user_input[0]) {
        case 'A':
            posx = 0;
            break;
        case 'B':
            posx = 1;
            break;
        case 'C':
            posx = 2;
            break;
        case 'D':
            posx = 3;
            break;
        case 'E':
            posx = 4;
            break;
        case 'F':
            posx = 5;
            break;
        case 'G':
            posx = 6;
            break;
        case 'H':
            posx = 7;
            break;
        case 'I':
            posx = 8;
            break;
        case 'J':
            posx = 9;
            break;
        default:
            posx = 10;
            break;
        }

        switch (user_input[1]) {
        case '0':
            posy = 0;
            break;
        case '1':
            posy = 1;
            break;
        case '2':
            posy = 2;
            break;
        case '3':
            posy = 3;
            break;
        case '4':
            posy = 4;
            break;
        case '5':
            posy = 5;
            break;
        case '6':
            posy = 6;
            break;
        case '7':
            posy = 7;
            break;
        case '8':
            posy = 8;
            break;
        case '9':
            posy = 9;
            break;
        default:
            posy = 10;
            break;
        }

        if (posx >= 0 && posx < 10 && posy >= 0 && posy < 10) {
            if (minelocation[posy][posx] == 1) {
                minelocation[posy][posx] = 3;
            }
            else if (minelocation[posy][posx] == 2) {
                minelocation[posy][posx] = 4;
            }
            else {
                std::cout << "That tile is already uncovered!\n";
            }
        }
    }
    else if (user_input == "help") {
        controls();
    }
    else if (user_input == "restart") {
        std::cout << "Ok, restarting game. ";
        gamestate = 4;
    }
    else {
        std::cout << "That's not a command! Try again.\n";
    }
}

int main()
{

    greetPlayer();

    marker:
    global_input_int = 0;

    while (global_input_int > 99 or global_input_int < 1) {
        std::cout << "How many mines do you want to use?\n";
        std::cin >> global_input_int;
    }

    std::cout << "Press ENTER to start game:\n";

    cin.ignore(INT_MAX, '\n');
    int a = cin.get();

    generateMap(global_input_int);

    while (game_running) {
        Sleep(0.5);
        while (gameplayloop) {
            gameRenderer();
            if (gamestate == 6) {
                gameplayloop = false;
                game_running = false;
                break;
            }

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (minelocation[i][j] == 1) {
                        check_if_game_won++;
                    }
                }
            }

            if (check_if_game_won == 0) {
                gamestate = 5;
                gameplayloop = false;
            }

            inputDecoder();

            if (gamestate == 4) {
                goto marker;
            }
        }

        if (gamestate == 5) {
            std::cout << "You did it! You found all the mines! Do you want to play again? (Y/N)";
            while (!globalbool) {
                cin >> user_input;

                if (user_input == "Y") {
                    std::cout << "Ok, restarting game. ";
                }
                else if (user_input == "N") {
                    std::cout << "Goodbye hero!";
                }
            }
        }
    }
}







