#include "board.h"



board::board()
{

}

void board::deleteSquaresBoard()
{
    if(_board.size()!=0)
        for(auto item : _board)
            delete item;
}
