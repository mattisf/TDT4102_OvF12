#pragma once
#include "Graph.h"

bool isBetween(int x, int lower, int upper);

class Racket {
    private:
        Point position;
        static constexpr int velocity = 8;
    public:
        static constexpr int length = 4;
        static constexpr int blockSize = 10;
        
        Racket() {}
        Racket(Point initPos) : position{initPos} {}
        Point getPosition() const { return position; };
        int getX() const { return position.x; }
        int getY() const { return position.y; }
        void moveUp();
        void moveDown();
};

class Ball {
    private:
        static constexpr int velocity = 8;
        static constexpr int blockSize = Racket::blockSize;
        Point position;
    
    public:
        float dir_x=0;
        float dir_y=0; 
        Ball() {}
        Ball(Point initPos, float x, float y) : position{initPos}, dir_x{x}, dir_y{y} {}
        Point getPosition() const { return position; }
        int getDir() const {
            return dir_x >= 0 ? 1 : -1;
        }
        int getX() const { return position.x; }
        int getY() const { return position.y; }
        int nextX();
        int nextY();
        vector<float> calculateDirection(Racket racket);
        void setDirection(vector<float> nextDir);
        void move(); 

};