#include "checkerscontroller.h"
#include <QtWidgets>

checkersController::checkersController()
{

}

//La methode aboutDames permet d'afficher un petit message d'information sur le jeu de dame
void checkersController::aboutDames()
{
     QMessageBox msgBox;
     msgBox.setText("Cette application a été réalisé par ADELEKE Kismath dans le cadre du projet de L3 Informatique du cours de Qt.");
     msgBox.setStandardButtons(QMessageBox::Ok );
     msgBox.setWindowTitle("A propos de dames");
     QIcon icon(":/crown_white.png");
     msgBox.setWindowIcon(icon);
     QPixmap pixmap(":/crown_white.png");
     msgBox.setIconPixmap(pixmap.scaled(80,80));
     msgBox.exec();
}

//La methode aboutQt permet d'afficher un petit message d'information sur Qt
void checkersController::aboutQt()
{
    QFile file(":/AproposQt.txt");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream filecontent(&file);
    QMessageBox msgBox;
    msgBox.setText(filecontent.readAll());
    file.close();
    msgBox.setStandardButtons(QMessageBox::Ok );
    msgBox.setWindowTitle("À propos de Qt");
    QIcon icon(":/crown_white.png");
    msgBox.setWindowIcon(icon);
    QPixmap pixmap(":/Qt_Creator_Icon_Web.png");
    msgBox.setIconPixmap(pixmap.scaled(80,80));
    msgBox.exec();
}



//La methode loadGame permet de charger un jeu déjà sauvegarder antérieurement
QString checkersController::loadGame(QString fileName, QGridLayout * gridBoard )
{
        //Lecture du fichier
        QFile file(fileName);
        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            qDebug() << "File not exists";
        } else {
            //Si le fichier existe ,
            _checkersBoard.deleteSquaresBoard();
           _checkersBoard._board = QVector<square*>(100,nullptr);
            int x=-1;
            QTextStream filecontent(&file);
            while (!filecontent.atEnd())
            {   QString line = filecontent.readLine();
                if (x==-1)
                _checkersBoard.setPlayerturn((line=="2")? playertype::black : playertype::white);
                else {
                    int y =0;
                    for (QString item : line.split(" ")) {
                       if(item!="") {
                           position p(x,y);
                           if(item=="1")
                               _checkersBoard._board[index(x,y)] = new square(p.IsADisabledPosition(),position(x,y),playertype::white);
                           else if (item=="2")
                               _checkersBoard._board[index(x,y)] = new square(p.IsADisabledPosition(),position(x,y),playertype::black);
                           else if (item=="10")
                               _checkersBoard._board[index(x,y)] = new square(p.IsADisabledPosition(),position(x,y),playertype::black,true);
                           else if (item=="20")
                               _checkersBoard._board[index(x,y)] = new square(p.IsADisabledPosition(),position(x,y),playertype::black,true);
                           else
                               _checkersBoard._board[index(x,y)] = new square(p.IsADisabledPosition(),position(x,y),playertype::none);
                           gridBoard->addWidget(_checkersBoard._board[index(x,y)],x,y);
                       }

                        y++;
                    }
                }
                x++;
            }
            file.close();
        }
       return "Debut d'une nouvelle partie! Joueur actif :"+ (_checkersBoard.getPlayerturn() ==playertype::black)? "Noir" : "Blanc" ;
 }


//La methode saveGame permet de sauvegarder un jeu en cours
void checkersController::saveGame(QString fileName)
{
    QFile file(fileName);
    qDebug() << fileName;
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QTextStream stream(&file);
    stream << ((_checkersBoard.getPlayerturn() == playertype::black)? 2 :1) << endl;
    QString separator(" ");
    //Parcours des cases du damier
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j <10; ++j)
        {//Recuperation du prochain joueur et du type de pion
            auto player = _checkersBoard._board[index(i,j)]->get_player();
            bool isqueen = _checkersBoard._board[index(i,j)]->isqueen();
            switch (player) {
                //Sauvegarde du pion en fonction de son type
                case playertype::none:
                    stream << "0" << separator;
                break;
                case playertype::white:
                    if (isqueen)
                        stream << "10" << separator;
                    else
                        stream << "1" << separator;
                    break;
                case playertype::black:
                    if (isqueen)
                        stream << "20" << separator;
                    else
                        stream << "2" << separator;

            }
        }
        stream << endl;
    }

    stream.flush();
    file.close();

}
// la methode index permet de convertir une position en index pour le vecteur de carré
int checkersController::index (int x, int y)const {
    return x + 10 * y;
}

//Recherche les pions restants d'un joueur donné
std::vector<position> checkersController::searchRemainingPawns(const playertype player) {
    std::vector<position> tokens;
    for (auto el : _checkersBoard._board) {
        if (el->get_player() == player)
            tokens.push_back(el->get_pos());
    }
    return tokens;
}

//Recupère les positions  de deplacements possibles d'un pion donné
std::vector<position> checkersController::possiblePawnMoves(square const & selected_square) const
{    std::vector<position> v;
    //si c'est un simple pion
    if(!selected_square.isqueen()) {
        auto x = selected_square.get_pos().getX();
        auto y = selected_square.get_pos().getY();

           if (selected_square.get_player() == playertype::black){
              if (position(x-1,y+1).isvalide()){
                  if(_checkersBoard._board[index(x-1,y+1)]->get_player() == playertype::none)
                      v.push_back(position(x-1,y+1));
                  if(_checkersBoard._board[index(x-1,y+1)]->get_player() == playertype::white && position(x-2,y+2).isvalide() && _checkersBoard._board[index(x-2,y+2)]->get_player() == playertype::none)
                    {  //v.push_back(position(x-1,y+1));
                       position jumpPosition(x-2,y+2);
                       jumpPosition.pawnPositionsToCatch.push_back(position(x-1,y+1));
                       v.push_back(jumpPosition);}
               }
              if (position(x -1,y-1).isvalide()){
                  if(_checkersBoard._board[index(x-1,y-1)]->get_player() == playertype::none)
                      v.push_back(position(x-1,y-1));

                  if(_checkersBoard._board[index(x-1,y-1)]->get_player() == playertype::white && position(x -2,y-2).isvalide()
                          && _checkersBoard._board[index(x-2,y-2)]->get_player() == playertype::none )
                     {
                      //v.push_back(position(x-1,y-1));
                      position jumpPosition(x-2,y-2);
                      jumpPosition.pawnPositionsToCatch.push_back(position(x-1,y-1));
                      v.push_back(jumpPosition);}
               }
           }
           else if (selected_square.get_player() == playertype::white){
               if (position(x+1,y+1).isvalide()){
                   if(_checkersBoard._board[index(x+1,y+1)]->get_player() == playertype::none)
                       v.push_back(position(x+1,y+1));

                   if(_checkersBoard._board[index(x+1,y+1)]->get_player() == playertype::black && position(x+2,y+2).isvalide()
                           && _checkersBoard._board[index(x+2,y+2)]->get_player() == playertype::none )
                       { //v.push_back(position(x+1,y+1));
                           position jumpPosition(x+2,y+2);
                           jumpPosition.pawnPositionsToCatch.push_back(position(x+1,y+1));
                           v.push_back(jumpPosition);
                       }

                }
               if (position(x+1,y-1).isvalide()){
                   if(_checkersBoard._board[index(x+1,y-1)]->get_player() == playertype::none)
                       v.push_back(position(x+1,y-1));

                   if(_checkersBoard._board[index(x+1,y-1)]->get_player() == playertype::black && position(x+2,y-2).isvalide()
                           && _checkersBoard._board[index(x+2,y-2)]->get_player() == playertype::none )
                       {
                        position jumpPosition(x+2,y-2);
                        jumpPosition.pawnPositionsToCatch.push_back(position(x+1,y-1));
                        v.push_back(jumpPosition);}

                }
           }
    } else{
        //si c'est une reine
        return possibleQueenMoves(selected_square);
    }

    return v;
}

std::vector<position> checkersController::possibleQueenMoves(const square &selected_square) const
{
    std::vector<position> v;
    auto player = selected_square.get_player();
    for (int i = -1; i <= +1; i+=2) {
        for (int j = -1; j <= +1; j+=2) {
            std::vector<position> pawnPositionsToCatchInDiagonal = {};

            auto x = selected_square.get_pos().getX();
            auto y = selected_square.get_pos().getY();
            bool endsearch= false;
            do {
                if (position(x+i,y+j).isvalide()){
                    if(_checkersBoard._board[index(x+i,y+j)]->get_player() == playertype::none){
                        position p(x+i,y+j);
                        p.pawnPositionsToCatch.insert(p.pawnPositionsToCatch.end(), pawnPositionsToCatchInDiagonal.begin(),pawnPositionsToCatchInDiagonal.end());
                        v.push_back(p);
                        x= x+i;
                        y= y+j;
                    }
                   else if(_checkersBoard._board[index(x+i,y+j)]->get_player() != player  )
                      {
                        if(position(x+(2*i),y+(2*j)).isvalide() ){

                            if(_checkersBoard._board[index(x+(2*i),y+(2*j))]->get_player() == playertype::none){
                                position jumpPosition(x+(2*i),y+(2*j));
                                pawnPositionsToCatchInDiagonal.push_back(position(x+i,y+j));
                                jumpPosition.pawnPositionsToCatch.insert(jumpPosition.pawnPositionsToCatch.end(), pawnPositionsToCatchInDiagonal.begin(),pawnPositionsToCatchInDiagonal.end());
                                v.push_back(jumpPosition);
                                x= x+(2*i);
                                y= y+(2*j);
                            }else if(_checkersBoard._board[index(x+(2*i),y+(2*j))]->get_player()!= player){
                                x= x+(2*i);
                                y= y+(2*j);
                                position p(x,y);
                                pawnPositionsToCatchInDiagonal.push_back(position(x+i,y+j));
                                pawnPositionsToCatchInDiagonal.push_back(p);

                            }else
                               endsearch = true;
                        }else
                            endsearch = true;
                      }else
                        endsearch = true;
                 }else
                    endsearch = true;
            } while (!endsearch);
        }
    }
    return v;
}

// Déplace un pion d'une case à une autre;
void checkersController::movePawnTo(position const  positionTo)
{   auto xTo = positionTo.getX();
    auto yTo = positionTo.getY();

    //Verifie si aucun pion n'est sur la case où deplacement sera éffectue
    if(_checkersBoard._board[index(xTo,yTo)]->get_player()== playertype::none){

        auto player = _checkersBoard.getActiveSquare()->get_player();
        auto isqueen =  _checkersBoard.getActiveSquare()->isqueen();
        //Fais les prises qui doivent etes faites
        for (auto pos : positionTo.pawnPositionsToCatch)
            _checkersBoard._board[index(pos.getX(),pos.getY())]->give();

        /*Recuperer les positions possibles de deplacement et les parcours pour passer de
        pret à recevoir à non actif */
         auto positions = possiblePawnMoves(*_checkersBoard.getActiveSquare());
         std::for_each(positions.begin(),positions.end(),[this,xTo,yTo](position const & p){
             if(!position(xTo,yTo).isequal(_checkersBoard._board[index(p.getX(),p.getY())]->get_pos()))
                _checkersBoard._board[index(p.getX(),p.getY())]->setStatus(BoardSquareStatus::NotActive);
         });

        //Passer le tour au joueur suivant, la case du pion libere le pion et
         //la case de deplacement la recupere

       _checkersBoard.NextPlayerTakeTurn();
        _checkersBoard.getActiveSquare()->give();
        _checkersBoard._board[index(xTo,yTo)]->setStatus(BoardSquareStatus::NotActive);
        _checkersBoard._board[index(xTo,yTo)]->receive(player,isqueen);
       _checkersBoard.setActiveSquare(nullptr);}
}

//Verifie si il y un joueur peut encore effectué des deplacements
bool checkersController::IsThereAnyValidMoves(playertype player) {
    auto playerPieces = searchRemainingPawns(player);
    bool moveFound = false;
    for(auto el : playerPieces){
     //Verifie Si au moins un des pions du joueur peut au moins effectuer un deplacement
        if( possiblePawnMoves(*_checkersBoard._board[index(el.getX(),el.getY())]).size() !=0){
            moveFound = true;
            break;
        }
    }
    return moveFound;
}

// initialise le damier
void checkersController::initializeCheckers(QGridLayout * gridBoard)
{

    _checkersBoard.startNewGame();
    _checkersBoard.deleteSquaresBoard();
    _checkersBoard._board =  QVector<square*>(100,nullptr);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            position squarePositionOnBoard(i,j);
            if(i>=0 && i<=3){
                if(!squarePositionOnBoard.IsADisabledPosition())
                    _checkersBoard._board[index(i,j)] = new square(false,squarePositionOnBoard,playertype::white);
                else
                    _checkersBoard._board[index(i,j)] = new square(true,squarePositionOnBoard,playertype::none);
            }else if (i>=6 && i<=9){
                if(!squarePositionOnBoard.IsADisabledPosition())
                    _checkersBoard._board[index(i,j)] = new square(false,squarePositionOnBoard,playertype::black);
                else
                    _checkersBoard._board[index(i,j)] = new square(true,squarePositionOnBoard,playertype::none);
            }else
                _checkersBoard._board[index(i,j)] = new square(squarePositionOnBoard.IsADisabledPosition(),squarePositionOnBoard,playertype::none);
            gridBoard->addWidget(_checkersBoard._board[index(i,j)],i,j);

        }
    }

}

// est appeler suite au clic d'une case
QString checkersController::OnclickOnBoardSquare(square * selected_square)
{   QString playerTurnMessage = "Joueur actif: "+ (_checkersBoard.getPlayerturn() ==playertype::black)? "Noir" : "Blanc" ;
    //Verifie s'il le jeu n'est pas terminé
    if(_checkersBoard.getGameStatus()== GameStatusType::CanKeepPlaying){
                //Verifie si la case selectionner n'est pas active et que c'est le bon joueur qui à le tour qui joue
              if (selected_square->getsquareStatus() == BoardSquareStatus::NotActive && _checkersBoard.getPlayerturn() == selected_square->get_player()){
                  bool can_activate=true;

                  for (int i = 0; i < _checkersBoard._board.size(); ++i) {
                      //Verifie en parcourant le damier s'il y a déjà un joueur active, si oui il ne fait rien
                      if(_checkersBoard._board[i]->getsquareStatus()==BoardSquareStatus::Active && !(_checkersBoard._board[i]->get_pos().isequal(selected_square->get_pos())) ){
                          can_activate = false;
                      }
                  }
                  if(can_activate){
                      //SI la case choisi n'est pas activé on l'active et on montre les deplacements possibles
                      selected_square->setStatus(BoardSquareStatus::Active);
                     _checkersBoard.setActiveSquare(selected_square);
                      auto positions = possiblePawnMoves(*selected_square);
                      std::for_each(positions.begin(),positions.end(),[this](position const & p){
                          _checkersBoard._board[index(p.getX(),p.getY())]->setStatus(BoardSquareStatus::ReadyToReceive);
                          _checkersBoard._board[index(p.getX(),p.getY())]->set_pos(p);
                      });
                  }

              }// Verifie si la case est un deplacement possible et deplace le pion
              else if (selected_square->getsquareStatus() == BoardSquareStatus::ReadyToReceive) {
                  movePawnTo(selected_square->get_pos() );

                  playerTurnMessage = "Joueur actif: "+QString::number( (_checkersBoard.getPlayerturn() ==playertype::black)? 2 : 1 );
                  _checkersBoard.setGameStatus(checkWinStatus());
                  if(_checkersBoard.getGameStatus()!= GameStatusType::CanKeepPlaying)
                      GameOver();
              }
              else {
                  //Si la case etait deja active, elle est deselectionné ainsi que les mouvements possibles
                  selected_square->setStatus(BoardSquareStatus::NotActive);
                  auto positions = possiblePawnMoves(*selected_square);
                  std::for_each(positions.begin(),positions.end(),[this](position const & p){
                      _checkersBoard._board[index(p.getX(),p.getY())]->setStatus(BoardSquareStatus::NotActive);
                  });
              }
          }
    return playerTurnMessage;
}

// est declenché lorque le jeu est terminé pour afficher le joueur gagnant
QString checkersController::GameOver()
{   QString gameOverMessage = "";

    switch (_checkersBoard.getGameStatus()) {
        case BlackWin:
            gameOverMessage = "Le joueur 2 a gagné!";
        break;
        case WhiteWin:
            gameOverMessage = "Le joueur 1 a gagné!";
        break;
        default:
           gameOverMessage = "Il n'y a pas de gagnant!";
    }
    QMessageBox msgBox;
    msgBox.setText(gameOverMessage);
    msgBox.setStandardButtons(QMessageBox::Ok );
    msgBox.setWindowTitle("GameOver");
    QIcon icon(":/crown_white.png");
    msgBox.setWindowIcon(icon);
    QPixmap pixmap(":/gameover.jpg");
    msgBox.setIconPixmap(pixmap.scaled(80,80));
    msgBox.exec();
    return gameOverMessage;

}

// Verifier le status du jeu
GameStatusType checkersController::checkWinStatus(){
    /* Si le joueur blanc ne peut plus deplacer de pion et si c'est le cas du noir aussi
     il n'y a pas de gagnant sinon c'est le noir qui gagne dans le cas contraire le blanc gagne */
    if ((searchRemainingPawns(playertype::white)).size() == 0) {
        if ((searchRemainingPawns(playertype::black)).size() == 0){
            return NoWinner;
        }else{
            return BlackWin;
        }
    }
    else if ((searchRemainingPawns(playertype::black)).size() == 0) {
        return WhiteWin;
    }
    //Si le prochain joueur n'a plus de dplacement possible, c'est le joueur actuelle qui gagne
    else if (!IsThereAnyValidMoves(_checkersBoard.getPlayerturn())) {
        if(!IsThereAnyValidMoves((_checkersBoard.getPlayerturn() == playertype::black) ? playertype::white : playertype::black))
            return NoWinner;

        return ((_checkersBoard.getPlayerturn() == playertype::black) ? WhiteWin : BlackWin);
    }
    else{
        return CanKeepPlaying;
    }
}

void checkersController::createLanguageMenu()
{
   /* languageMenu = new QMenu(this);

    languageActionGroup = new QActionGroup(this);
    connect(languageActionGroup, SIGNAL(triggered(QAction *)),
            this, SLOT(switchLanguage(QAction *)));

    QDir qmDir = directoryOf("translations");
    QStringList fileNames =
            qmDir.entryList(QStringList("callcenter_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.chop(3);

        QTranslator translator;
        translator.load(fileNames[i], qmDir.absolutePath());
        QString language = translator.translate("MainWindow",
                                                "English");

        QAction *action = new QAction(tr("&%1 %2")
                                      .arg(i + 1).arg(language), this);
        action->setCheckable(true);
        action->setData(locale);

        languageMenu->addAction(action);
        languageActionGroup->addAction(action);

        if (language == "English")
            action->setChecked(true);
    }*/
}

