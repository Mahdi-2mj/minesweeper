/*
# minesweeper
git: https://github.com/Mahdi-2mj/minesweeper.git
contact : mahdi.2mj.2003@gmail.com
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <conio.h>
#include <windows.h>

using namespace std;

const int row = 9;
const int column = 9;
const char mine = '*';
const char blank = '#';
char mainBoard[row][column];
char hiddenBoard[row][column];
string firstPlayer;
string secondPlayer;
int firstPlayerPoint = 0, secondPlayerPoint = 0, minesNum = 0;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
void checkExit(int);

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
    SetConsoleTextAttribute(hConsole, 14);
    cout << "\t->1) Play" << endl;
    cout << "\t  2) How to play" << endl;
    cout << "\t  3) Quit Program" << endl << endl;
}

int getChoice()
{
    int choice;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Enter your choice: ";
    cin >> choice;
    while (choice < 1 || choice > 3)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "The only valid choices are 1-3, Please re-enter." << endl << endl;
        mainMenu();
        SetConsoleTextAttribute(hConsole, 11);
        cout << "Enter your choice: ";
        cin >> choice;
    }
    return choice;
}

void help()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 10);
    cout << "\tHOW TO PLAY?\n";
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\t\tMinesweeper is a game where mines are hidden in a grid of squares.\n"
    "\t\tSafe squares have numbers telling you how many mines touch the square.\n"
    "\t\tYou can use the number clues to find the remaining mines.\n"
     "\t\tIf you click on a mine you get a point!\n\n";
     mainMenu();
}

void getPlayersName(string &x, string &y)
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\t\t\t\t\tNOTE: press ESC or x to exit the game when playing...\n" << endl;
    SetConsoleTextAttribute(hConsole, 7);
    cout << "Enter first player's name: " << endl;
    SetConsoleTextAttribute(hConsole, 1);
    cin >> x;
    SetConsoleTextAttribute(hConsole, 7);
    cout << "Enter second player's name: " << endl;
    SetConsoleTextAttribute(hConsole, 4);
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
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board[i][j] == mine)
                minesNum++;
}

void boardDisplay(char board[row][column]){
    system("cls");
    SetConsoleTextAttribute(hConsole, 14);
    cout << "    ";
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 8; j++){
            if (i == 0)
            {
                SetConsoleTextAttribute(hConsole, 8);
                cout << j + 1 << "   ";
            }

            else
            {
                if(j == 0)
                {
                    SetConsoleTextAttribute(hConsole, 8);
                    cout << i << "   ";
                }
                SetConsoleTextAttribute(hConsole, 14);
                cout << board[i][j] <<  "   " ;
            }
        }
     cout << endl;
     }
     cout << endl;

     SetConsoleTextAttribute(hConsole, 2);
     cout << "There are " << minesNum << " mines in this game. Try to find them!" << endl << endl;

     SetConsoleTextAttribute(hConsole, 6);
     cout << "\t\t\t\t\t ScoreBoard:" << endl;
     cout << "\t\t\t\t\t|" << firstPlayer << " point: " << firstPlayerPoint << endl;
     cout << "\t\t\t\t\t|" << secondPlayer << " point: " << secondPlayerPoint << endl;
}


void minesGen(char board[row][column])
{
    int row, column;
    for (int i = 0; i < 14; i++)
    {
        row = rand() % 8;
        column = rand() % 8;
        board[row][column] = mine;
    }
}

void numbersGen(char board[row][column])
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != mine)
            {
                if (i > 0 && board[i - 1][j] == mine)
                    count++;
                if (i > 0 && j > 0 && board[i - 1][j - 1] == mine)
                    count++;
                if (i > 0 && j < 9 && board[i - 1][j + 1] == mine)
                    count++;
                if (j > 0 && board[i][j - 1] == mine)
                    count++;
                if (j < 9 && board[i][j + 1] == mine)
                    count++;
                if (i < 9 && j > 0 && board[i + 1][j - 1] == mine)
                    count++;
                if (i < 9 && board[i + 1][j] == mine)
                    count++;
                if (i < 9 && j < 9 && board[i + 1][j + 1] == mine)
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
        SetConsoleTextAttribute(hConsole, 12);
        cout << "(Press x or Esc to forfeit, any key to continue)";
        checkExit(count);
        cout << "\r                                                 ";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\rEnter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> column;
        while (row <= 0 || row > 8 || column <= 0 || column > 8)
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Invalid input! Please enter row and column between 1 to 8." << endl;
            SetConsoleTextAttribute(hConsole, 11);
            cout << "Enter row: ";
            cin >> row;
            cout << "Enter column: ";
            cin >> column;
        }
        column -= 1;
        if (hiddenBoard[row][column] == mine)
        {
            if(count % 2)
                secondPlayerPoint++;
            else
                firstPlayerPoint++;
            mainBoard[row][column] = hiddenBoard[row][column];
            boardDisplay(mainBoard);
            if((firstPlayerPoint == minesNum/2) && (secondPlayerPoint == minesNum/2))
            {
                SetConsoleTextAttribute(hConsole, 13);
                cout << "^^^^^^^ What a game! Tie it is! ^^^^^^^";
                play = false;
                exit(0);
            }
            if(firstPlayerPoint == (minesNum / 2) + 1)
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << "****** \"" << firstPlayer << "\" won the game! ******";
                play = false;
                exit(0);
            }
            if(secondPlayerPoint == (minesNum / 2) + 1)
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << "****** \"" << secondPlayer << "\" won the game! ******";
                play = false;
                exit(0);
            }
            hiddenBoard[row][column] = blank;
        }
        else if((mainBoard[row][column] != mine) && (mainBoard[row][column] != blank))
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "This point was found. Select another one!" << endl;
            sleep(3);
        }
        else if (hiddenBoard[row][column] != blank)
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

        else if (mainBoard[row][column] == mine)
        {
            SetConsoleTextAttribute(hConsole, 12);
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
    {
        SetConsoleTextAttribute(hConsole, 4);
        cout << "It is " << secondPlayer << "'s turn!" << endl << endl;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 1);
        cout << "It is " << firstPlayer << "'s turn!" << endl << endl;
    }

}

void checkExit(int count)
{
    char ch = _getch();
    if ((ch == 27) || (ch == 120) || (ch == 88)){
            if(count % 2){
                SetConsoleTextAttribute(hConsole, 10);
                cout << "\n\n****** \"" << firstPlayer << "\" won the game! ******";
                exit(0);
            }else{
                SetConsoleTextAttribute(hConsole, 10);
                cout << "\n\n****** \"" << secondPlayer << "\" won the game! ******";
                exit(0);
            }
    }
}

