//
//  main.cpp
//  Snake_Game
//
//  Created by Никита Акимов on 27/10/2018.
//  Copyright © 2018 Никита Акимов. All rights reserved.
//

#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}



void Setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    
}

void Draw(){
    system("cls");
    for(int a = 0; a < 100000000; a++){
        
    }
    for(int i = 0; i < width + 1; i++){
        cout << "#";
    }
    cout << endl;
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if (j == 0 || j == width - 1){cout << "#";}
            if(i == y && j == x){cout << "0";}
            else if(i == fruitY && j == fruitX){cout << "F";}
            else {
                bool print = false;
                for(int k = 0; k < nTail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        print = true;
                        cout << "o";
                    }
                }
                if(!print){
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    
    for(int i = 0; i < width + 1; i++){
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void InputGo(){
    if(kbhit()){
        switch(getchar()){
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
    
}

void Logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    
    //if(x > width || x < 0 || y > height || y < 0){gameOver = true;}
    if(x >= width){x = 0;}
    else if(x < 0){x = width - 1;}
    
    if(y >= height){y = 0;}
    else if(y < 0){y = height - 1;}
    
    for(int i = 0; i < nTail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    
    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    
}

int main(int argc, char* argv[])
{
    Setup();
    while(!gameOver){
        Draw();
        InputGo();
        Logic();
    }
    
    return 0;
}
