#include "PongWindow.h"


PongWindow::PongWindow():
    AnimationWindow{400,200,pongGridWidth*blockSize,pongGridHeight*blockSize,"Pong Window"},
    playerLeft{Racket{Point{1*blockSize,1*blockSize}}},
    playerRight{Racket{Point{(pongGridWidth-2)*blockSize,(pongGridHeight-6)*blockSize}}},
    ball{Ball{Point{pongGridWidth*blockSize/2,pongGridHeight*blockSize/2},-1,0}},
    startBtn{pongGridWidth*blockSize/2-25,pongGridHeight*blockSize/2-20,50,20,"Start"},
    showPlayerLeftScore{100,20, 50, 20, "Score"},
    showPlayerRightScore{windowWidth-100,20, 50, 20, "Score"}
{ 
    color(0);
    add(startBtn);
    startBtn.callback(cb_start, this);
    add(showPlayerLeftScore);
    add(showPlayerRightScore);
    showPlayerLeftScore.value(to_string(playerLeftScore).c_str());
    showPlayerRightScore.value(to_string(playerRightScore).c_str());
}

void PongWindow::drawPlayers()
{
    draw_rectangle(playerLeft.getPosition(), blockSize, blockSize*Racket::length, Graph_lib::Color::white);
    draw_rectangle(playerRight.getPosition(), blockSize, blockSize*Racket::length, Graph_lib::Color::white);
}

void PongWindow::drawBall() 
{
    draw_rectangle(ball.getPosition(), blockSize, blockSize, Graph_lib::Color::white);
}

void PongWindow::run() 
{

    while(!should_close()) 
    {
        drawPlayers();
        drawBall();

        if (!game_paused) {
            handleCollision();
            ball.move();
            handleInput();
        }
        next_frame();
    }
}


void PongWindow::handleCollision()
{

    //sjekk om ballen har kollidert med venstre racket
    if (ball.dir_x < 0) {
        int pX = playerLeft.getX();
        int pY = playerLeft.getY();
        if (isBetween(ball.nextX(), pX-blockSize, pX)) {
            if (isBetween(ball.nextY(), pY-blockSize, pY+racketLength+blockSize)) {
                vector<float> nextDir = ball.calculateDirection(playerLeft);
                ball.setDirection(nextDir);
            }
        }
    }
    //sjekk om ballen har kollidert med høyre racket
    else if (ball.dir_x > 0) {
        int pX = playerRight.getX();
        int pY = playerRight.getY();
        if (isBetween(ball.nextX(), pX, pX+blockSize)) {
            if (isBetween(ball.nextY(), pY-blockSize, pY+racketLength+blockSize)) {
                vector<float> nextDir = ball.calculateDirection(playerRight);
                ball.setDirection(nextDir);
            }
        }

    }
    //sjekker om ballen har kollidert med taket.
    if ( !isBetween(ball.getY(), 0, windowHeight-blockSize) ) {

        vector<float> nextDir = {ball.dir_x, -ball.dir_y};
        ball.setDirection(nextDir);
    }
    //sjekker om ballen har kollidert med veggen til høyre eller venstre side, og gir poeng
    //til riktig person dersom den har det.
    if ( !isBetween(ball.getX(), 0, windowWidth) ) {
        if (ball.dir_x > 0) {
            playerLeftScore++;
            showPlayerLeftScore.value(to_string(playerLeftScore).c_str());
        } else {
            playerRightScore++;
            showPlayerRightScore.value(to_string(playerRightScore).c_str());
        }
        vector<float> nextDir = {-ball.dir_x, ball.dir_y};
        ball.setDirection(nextDir);
    }
    

}

//håndterer input fra spillere. racketen kan ikke flytte seg utenfor vinduet.
void PongWindow::handleInput()
{
    bool WKeyPressed = is_key_down(KeyboardKey::W);
    bool SKeyPressed = is_key_down(KeyboardKey::S);
    bool UpKeyPressed = is_key_down(KeyboardKey::UP);
    bool DownKeyPressed = is_key_down(KeyboardKey::DOWN);

    if (WKeyPressed) {
        if (playerLeft.getPosition().y > 0) {
            playerLeft.moveUp();
        }
    }
    if (SKeyPressed) {
        if (playerLeft.getPosition().y < windowHeight-racketLength)
        {
            playerLeft.moveDown();
        }
    }
    if (UpKeyPressed) {
        if (playerRight.getPosition().y > 0) {
           playerRight.moveUp(); 
        }
    }
    if (DownKeyPressed) {
        if (playerRight.getPosition().y < windowHeight-racketLength) {
            playerRight.moveDown();  
        }
        
    }
}

void PongWindow::startGame() {
    game_paused = false;
    startBtn.hide();
}