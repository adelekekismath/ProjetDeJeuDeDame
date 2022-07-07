#ifndef BOARD_H
#define BOARD_H
#include "square.h"

class board
{
public:
    board();
     QVector<square *> _board;
    square * getActiveSquare() const{
        return _activeSquare;
    }
    playertype getPlayerturn() const{
        return _playerturn;
    }
    GameStatusType getGameStatus() const{
        return _gameStatus;
    }
    void startNewGame(){
        _playerturn = playertype::white; //Le joueur blanc est toujours le premier à jouer
        _gameStatus = GameStatusType::CanKeepPlaying; //Debut de jeu
        _activeSquare = nullptr; // Aucun pion n'est selectionné
    }
    void NextPlayerTakeTurn(){
        _playerturn = ((_playerturn==playertype::white) ? playertype::black : playertype::white);
    }

    void setActiveSquare(square * ActiveSquare) {
        _activeSquare = ActiveSquare;
    }
    void setPlayerturn(playertype Playerturn) {
        _playerturn =Playerturn ;
    }
    void setGameStatus(GameStatusType GameStatus) {
        _gameStatus = GameStatus;}
    void deleteSquaresBoard();
    void incrementCheckersMovesCounter(){
        _checkersMovesWithNoCatchOrCounter++;
    }
public:
    int _checkersMovesWithNoCatchOrCounter;

private:

    square * _activeSquare;
    playertype _playerturn;
    GameStatusType _gameStatus;
};

#endif // BOARD_H
