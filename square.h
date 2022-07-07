#ifndef SQUARE_H
#define SQUARE_H

#include <QtWidgets>
typedef enum GameStatusType{
    CanKeepPlaying,
    WhiteWin,
    BlackWin,
    NoWinner
}Move_State;

typedef enum BoardSquareStatus{
    NotActive,
    Active,
    ReadyToReceive
}BoardSquareStatus;

class position{
public:
    position(int i, int j):x(i),y(j){}

    bool isvalide() const
    {
        return (x<=9) && (x>=0) && (y<=9) && (y>=0) ;
    }
    bool isequal(position const & pos) const{
        return  x==pos.x && y==pos.y;
    }
    int getX() const{return x;}
    int getY() const{return y;}
    bool IsADisabledPosition()const{
        return !(x%2!=y%2);
    }
    std::vector<position> pawnPositionsToCatch;
private:
    int x;
    int y;

};


enum playertype{
    black =2,
    white =1,
    none =0
};


class square : public QWidget
{
    Q_OBJECT
    Q_ENUM(playertype)
    Q_ENUM(BoardSquareStatus)
public:
    square(bool disable,position pos, playertype player=playertype::none, bool isqueen=false);
    void give();
    void receive(playertype player,bool isqueen);
    void paintOnSquare();
    bool isqueen() const{ return  queen;}
    playertype get_player() const{return _player;}
    BoardSquareStatus getsquareStatus() const;
    void setStatus(BoardSquareStatus activeStatus);
    position const & get_pos() const{return _pos;}
    void set_pos(position const & p){_pos = p;}

protected:
     void paintEvent(QPaintEvent *) override;
     void resizeEvent(QResizeEvent *event) override;

private:
    position _pos;
    playertype _player;
    QPixmap *_pixmap;
    BoardSquareStatus squareStatus;
    bool disable;
    bool queen;
};

#endif // SQUARE_H
