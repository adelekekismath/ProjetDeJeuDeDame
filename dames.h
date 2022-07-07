#ifndef DAMES_H
#define DAMES_H

#include <QMainWindow>
#include "square.h"
#include "checkerscontroller.h"

namespace Ui {
class Dames;
}

class Dames : public QMainWindow
{
    Q_OBJECT

public:

    explicit Dames(QWidget *parent = nullptr);
    ~Dames();
    void initializeCheckers();
    void GameOver();
    void createLanguageMenu();


protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void newGame();
    void loadGame();
    void saveGame();


private:
    Ui::Dames *ui;
    QMenu languageMenu;
    checkersController _gameController;
};

#endif // DAMES_H
