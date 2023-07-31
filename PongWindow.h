#pragma once
#include "AnimationWindow.h"
#include "Pong.h"
#include "GUI.h"

class PongWindow: public AnimationWindow {

public:
    PongWindow();
    void run();

private:

    //height and width of window in blocks.
    static constexpr int pongGridWidth  = 50;
    static constexpr int pongGridHeight = 30;

    static constexpr int blockSize = 10;
    static constexpr int racketLength = Racket::length*blockSize;

    static constexpr int windowHeight = pongGridHeight*blockSize;
    static constexpr int windowWidth = pongGridWidth*blockSize;

    bool game_paused = true;

    Racket playerLeft;
    Racket playerRight;
    Ball ball;

    int playerLeftScore = 0;
    int playerRightScore = 0;


    void handleInput();
    void drawGrid();
    void drawBall();
    void drawPlayers();
    void handleCollision();

    Fl_Button startBtn;
    Fl_Output showPlayerLeftScore;
    Fl_Output showPlayerRightScore;

    static void cb_start(Fl_Widget*, void *pw) {static_cast<PongWindow*>(pw)->startGame();}

    void startGame();

};