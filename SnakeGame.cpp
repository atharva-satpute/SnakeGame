#if defined(unix) || defined(__linux__)
    #include "kbhit.hpp"
    #define CLEARSCREEN system("clear")
#elif defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #define CLEARSCREEN system("cls")
#endif


#include <iostream>
#include <stdio.h>


class SnakeGame{

    const int width{20},height{20};
    int x,y,fruitX,fruitY,score,nTail;
    int tailX[100],tailY[100];

    bool gameOver = false;

    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN};
    Direction direction;

    public:
    // Constructor (to construct the setup of game)
    SnakeGame(){
        direction = STOP;
        x = width / 2;
        y = width / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        tailX[0] = 0;
        tailY[0] = 0;
    }   

    bool isGameOver();

    void draw(){
        CLEARSCREEN;
        for(int i =0; i < width + 2; i++){
            std::cout << "=";
        }

        std::cout << '\n';

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++) {
                if(j == 0)
                    std::cout << '|';
                if(i == y && j == x)
                    std::cout << "\u22C4";
                else if(i == fruitY && j == fruitX)
                    std::cout << 'F';
                else{
                    bool print = false;
                    for(int k = 0;k < nTail; k++){
                        if(tailX[k] == j && tailY[k] == i){
                            std::cout << "\u2218";
                            print = true;
                        }
                    }
                    if(!print){
                        std::cout << ' ';
                    }
                }

                if(j == width - 1)
                    std::cout << "|";
            }
            std::cout << '\n';
        }

        for(int i = 0; i < width + 2; i++)
            std::cout << "=";
        std::cout << '\n';

        // Displaying score
        std::cout << "Score: " << score << '\n';
        std::cout << "Press 'a' for LEFT, 'd' for RIGHT, 'w' for UP, 's' for DOWN\n";
        std::cout << "To quit the game press 'x'\n";
    }

    void input(){
        if(!_kbhit()){
            switch(getchar()){
                // Left
                case 'a':
                    direction = LEFT;
                    break;
                //Right
                case 'd':
                    direction = RIGHT;
                    break;
                // Up
                case 'w':
                    direction = UP;
                    break;
                // Down
                case 's':
                    direction = DOWN;
                    break;
                // End Game
                case 'x':
                    gameOver = true;
                    break;
                default: break;
            }
            return;
        }    
    }

    void logic(){
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X,prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for(int i = 1;i < nTail; i++){
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch(direction){
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
            default: break;
        }

        if(x >= width) x=0;      //If snake hits the right wall
        if(y > height - 1) y=0;     //If snake hits the bottom wall
        if(x < 0) x = width;    //If snake hits the left wall
        if(y < 0) y = height - 1;   //If snake hits the top wall

        for(int i = 0; i < nTail; i++){
            if(tailX[i] == x && tailY[i] == y)
                gameOver = true;
                break;
        }

        // Increase the score if the snake eats the fruit
        if(x == fruitX && y == fruitY){
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            nTail++;
        }
    }
};

bool SnakeGame::isGameOver(){
    return gameOver;
}
 
int main(){
    SnakeGame obj;
    while(!obj.isGameOver()){
        obj.draw();
        obj.input();
        obj.logic();
    }
    std::cout << '\n';
    kbhit_finish();
    return 0;
}