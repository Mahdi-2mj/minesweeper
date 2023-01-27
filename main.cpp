#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <conio.h>

using namespace std;

const int row = 9;
const int column = 9;
const char bomb = '*';
const char blank = '#';
char mainBoard[row][column];
char hiddenBoard[row][column];
string firstPlayer;
string secondPlayer;
int firstPlayerPoint = 0, secondPlayerPoint = 0;

void mainMenu();
int getChoice();
void help();
void getPlayersName(string&, string&);
void boardGen(char[row][column]);
void boardReform(char[row][column]);
void boardDisplay(char[row][column]);
void minesGen(char[row][column]);
void numbersGen(char[row][column]);
void play(char[row][column], char[row][column]);
void switchPlayers(int&);
void checkExit();

int main()
{
    srand(time(0));
    mainMenu();
    int choice;
    do{
        choice = getChoice();
        switch(choice){
            case 1:
                getPlayersName(firstPlayer, secondPlayer);
                boardGen(mainBoard);
                boardGen(hiddenBoard);
                minesGen(hiddenBoard);
                boardReform(hiddenBoard);
                numbersGen(hiddenBoard);
                play(mainBoard, hiddenBoard);
                break;
            case 2:
                help();
                break;
            case 3:
                exit(0);
                break;
        }
    } while(choice != 3);
}

void mainMenu()
{
    cout << "\t->1) Play" << endl;
    cout << "\t  2) How to play" << endl;
    cout << "\t  3) Quit Program" << endl << endl;
}

int getChoice()
{
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    while (choice < 1 || choice > 3)
    {
        cout << "The only valid choices are 1-3, Please re-enter." << endl << endl;
        mainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
    }
    return choice;
}

void help()
{
    system("cls");
    cout << "\tHOW TO PLAY?\n";
    cout << "\t\tMinesweeper is a game where mines are hidden in a grid of squares.\n"
    "\t\tSafe squares have numbers telling you how many mines touch the square.\n"
    "\t\tYou can use the number clues to find the remaining mines.\n"
     "\t\tIf you click on a mine you get a point!\n\n";
     mainMenu();
}

void getPlayersName(string &x, string &y)
{
    system("cls");
    cout << "press ESC or x to exit the game when playing..." << endl;
    cout << "Enter first player's name: " << endl;
    cin >> x;
    cout << "Enter second player's name: " << endl;
    cin >> y;
    if (x == y){
        x += "1";
        y += "2";
    }
}


void boardGen(char board[row][column]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            board[i][j] = blank;
    }
}

void boardReform(char board[row][column])
{
    for(int i = 0; i < 9; i++)
        board[0][i] = blank;
}

void boardDisplay(char board[row][column]){
    system("cls");
    cout << "    ";
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 8; j++){
            if (i == 0)
                cout << j + 1 << "   ";
            else
            {
                if(j == 0)
                    cout << i << "   ";
                cout << board[i][j] <<  "   " ;
            }

        }
     cout << endl;
     }
     cout << endl;
     cout << "\t\t\t\t\t" << firstPlayer << " point: " << firstPlayerPoint << endl;
     cout << "\t\t\t\t\t" << secondPlayer << " point: " << secondPlayerPoint << endl;
}


void minesGen(char board[row][column])
{
    int row, column;
    for (int i = 0; i < 13; i++)
    {
        row = rand() % 8;
        column = rand() % 8;
        board[row][column] = bomb;
    }
}

void numbersGen(char board[row][column])
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '*')
            {
                if (i > 0 && board[i - 1][j] == '*')
                    count++;
                if (i > 0 && j > 0 && board[i - 1][j - 1] == '*')
                    count++;
                if (i > 0 && j < 9 && board[i - 1][j + 1] == '*')
                    count++;
                if (j > 0 && board[i][j - 1] == '*')
                    count++;
                if (j < 9 && board[i][j + 1] == '*')
                    count++;
                if (i < 9 && j > 0 && board[i + 1][j - 1] == '*')
                    count++;
                if (i < 9 && board[i + 1][j] == '*')
                    count++;
                if (i < 9 && j < 9 && board[i + 1][j + 1] == '*')
                    count++;
                board[i][j] = count + '0';
                count = 0;
            }
        }
    }
}

void play(char mainBoard[row][column], char hiddenBoard[row][column])
{
    bool play = true;
    int row, column, count = 0;
    char ch;
    while(play){
        boardDisplay(mainBoard);
        switchPlayers(count);
        char choice;
        cout << "Enter row: ";
        //checkExit();
        cin >> row;
        cout << "Enter column: ";
        //checkExit();
        cin >> column;
        while (row <= 0 || row > 8 || column <= 0 || column > 8)
        {
            cout << "Invalid input! Please enter row and column between 0 and 8." << endl;
            cout << "Enter row: ";
            //checkExit();
            cin >> row;
            cout << "Enter column: ";
            //checkExit();
            cin >> column;
        }
        column -= 1;
        if (hiddenBoard[row][column] == '*')
        {
            if(count % 2)
                secondPlayerPoint++;
            else
                firstPlayerPoint++;
            mainBoard[row][column] = hiddenBoard[row][column];
            boardDisplay(mainBoard);
            if((firstPlayerPoint == 6) && (secondPlayerPoint == 6))
            {
                cout << "^^^^^^^ What a game! Tie it is!^^^^^^^";
                play = false;
                exit(0);
            }
            if(firstPlayerPoint == 7)
            {
                cout << "****** " << firstPlayer << " won the game! ******";
                play = false;
                exit(0);
            }
            if(secondPlayerPoint == 7)
            {
                cout << "****** " << secondPlayer << " won the game! ******";
                play = false;
                exit(0);
            }
            hiddenBoard[row][column] = blank;
        }

        else if (hiddenBoard[row][column] != '#')
        {
            if(hiddenBoard[row][column] == '0')
            {
                mainBoard[row][column] = hiddenBoard[row][column];
                mainBoard[row + 1][column] = hiddenBoard[row + 1][column];
                mainBoard[row - 1][column] = hiddenBoard[row - 1][column];
                mainBoard[row][column + 1] = hiddenBoard[row][column + 1];
                mainBoard[row][column - 1] = hiddenBoard[row][column - 1];
                mainBoard[row + 1][column + 1] = hiddenBoard[row + 1][column + 1];
                mainBoard[row - 1][column - 1] = hiddenBoard[row - 1][column - 1];
                mainBoard[row + 1][column - 1] = hiddenBoard[row + 1][column - 1];
                mainBoard[row - 1][column + 1] = hiddenBoard[row - 1][column + 1];
                count++;
                switchPlayers(count);
            }
            else
            {
                mainBoard[row][column] = hiddenBoard[row][column];
                count++;
                switchPlayers(count);
            }
        }
        else if (mainBoard[row][column] == '*')
        {
            cout << "This mine was found!" << endl;
            sleep(3);
        }
        else
        {
            mainBoard[row][column] = hiddenBoard[row][column];
            count++;
            switchPlayers(count);
        }

    }
}

void switchPlayers(int& count)
{
    if(count % 2)
        cout << "It's " << secondPlayer << "'s turn!" << endl << endl;
    else
        cout << "It's " << firstPlayer << "'s turn!" << endl << endl;

}

void checkExit()
{
    char ch = _getch();
    if ((ch == 27) || (ch == 120) || (ch == 88))
            exit(0);
}

