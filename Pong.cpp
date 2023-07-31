#include "Pong.h"


bool isBetween(int x, int lower, int upper) {
    return (x >= lower) && (x <= upper);
}

void Racket::moveDown() {
    position.y += velocity;
}

void Racket::moveUp() {
    position.y -= velocity;
}

void Ball::move() {
    cout << "\nX: " << position.x;
    position.x = nextX();
    position.y = nextY();
}

int Ball::nextX() { 
    return position.x + ((int) dir_x)*velocity;
}
int Ball::nextY() {
    return position.y + ((int) dir_y)*velocity;
}


vector<float> Ball::calculateDirection(Racket racket) {
    float x = -dir_x; 
    float y = dir_y;
    //beveg nedover.
    if (isBetween(position.y, racket.getY()+Racket::length*Racket::blockSize*3/4,
                            racket.getY()+(Racket::length+1)*Racket::blockSize)) {
        y = 1;
    }
    //beveg bortover
    if (isBetween(position.y, racket.getY() - Racket::blockSize,
                            racket.getY() + Racket::blockSize)) {
        y =-1;
    }
    //beveg horisontalt
    else if (isBetween(position.y, racket.getY() + Racket::blockSize, racket.getY()+Racket::length*Racket::blockSize*3/4)) {
        y = 0;
    }
    vector<float> ret = {x, y};
    return ret;
} 

void Ball::setDirection(vector<float> nextDir) {
    dir_x = nextDir.at(0);
    dir_y = nextDir.at(1);
}

