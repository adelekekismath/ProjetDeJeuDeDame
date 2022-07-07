#include "square.h"


square::square(bool disable,position pos, playertype player, bool isqueen):QWidget ()
  ,_pos(pos),_player(player),disable(disable)
{
    queen = isqueen;
    squareStatus  = BoardSquareStatus::NotActive;
    paintOnSquare();
    setMinimumSize(50,50);
}

BoardSquareStatus square::getsquareStatus() const
{
    return squareStatus;
}

void square::setStatus(BoardSquareStatus activeStatus)
{
    squareStatus = activeStatus;
    paintOnSquare();
}


void square::give()
{   //La case libere son pion et le redessine
    _player = playertype::none;
    setStatus(BoardSquareStatus::NotActive);
    queen = false;
    paintOnSquare();
}

void square::receive(playertype player, bool isqueen)
{   //La case recoit un pion et le redessine
    // Si la case est sur la premiere ou la derniere du damier, il est promut reine
    if(_pos.getX() == 9 || _pos.getX() == 0)
        this->queen = true;
    else {
        this->queen = isqueen;
    }
    _player = player;

    paintOnSquare();
}

//Dessine sur la case en fonction de son statut
void square::paintOnSquare()
{   _pixmap =new QPixmap(this->size()) ;
    QPainter painter(_pixmap);
    QRect mesure(0,0,rect().width()-10,rect().height()-10);
    QRect devRect(0, 0, painter.device()->width(), painter.device()->height());
    mesure.moveCenter(devRect.center());
    if (!disable){
        if(squareStatus == BoardSquareStatus::Active ){
           painter.setBrush(QBrush("#0A38D6"));
        }else if (squareStatus == BoardSquareStatus::ReadyToReceive ) {
            painter.setBrush(QBrush("#0AD645"));
        }
        else {
            painter.setBrush(QBrush("#D2691E"));
         }
           painter.drawRect(rect());

           if(_player == playertype::white ){
               QPen pen(Qt::black, 3);
               painter.setPen(pen);
               painter.setBrush(Qt::white);
               painter.drawEllipse(mesure);

           }
           else if(_player == playertype::black ){
               QPen pen(Qt::white, 3);
               painter.setPen(pen);
               painter.setBrush(Qt::black);
               painter.drawEllipse(mesure);

           }
           if(isqueen()){
              QImage source(((get_player()==playertype::white) ? ":/crown_black.png" : ":/crown_white.png"));
              QRect mesure(0,0,rect().width()-20,rect().height()-20);
              QRect devRect(0, 0, painter.device()->width(), painter.device()->height());
              mesure.moveCenter(devRect.center());
              painter.drawImage(mesure, source);

        }}else {
            painter.setBrush(QBrush("#DEB887"));
            painter.drawRect(rect());
        }
    update();

}






void square::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *_pixmap);
}


void square::resizeEvent(QResizeEvent *event)
{
    paintOnSquare();
}



