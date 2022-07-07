#ifndef CHECKERSCONTROLLER_H
#define CHECKERSCONTROLLER_H

#include <QMainWindow>
#include "square.h"
#include "board.h"

class checkersController: public QObject
{
    Q_OBJECT

public:
    checkersController();
    int index(int x, int y) const;
    std::vector<position> possiblePawnMoves(square const & selected_square) const;
    std::vector<position> possibleQueenMoves(square const & selected_square) const;
    std::vector<position> searchRemainingPawns(const playertype player);
    void movePawnTo( position const  positionTo);
    GameStatusType checkWinStatus();
    bool IsThereAnyValidMoves(playertype player);
    void initializeCheckers(QGridLayout * gridBoard);
    QString OnclickOnBoardSquare(square * selected_square);
    bool IsAValidSquare(position p);
    QString GameOver();
    void createLanguageMenu();

public slots:
    void aboutDames();
    void aboutQt();
    QString loadGame(QString fileName, QGridLayout * gridBoard);
    void saveGame(QString fileName);

private:
    board _checkersBoard;
};

#endif // CHECKERSCONTROLLER_H
