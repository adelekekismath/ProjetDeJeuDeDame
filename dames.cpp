#include "dames.h"
#include "ui_dames.h"
#include <QtWidgets>


Dames::Dames(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dames),
    _gameController()
{
   ui->setupUi(this);

    setWindowIcon(QIcon(":/crown_white.png"));
    ui->menuA_propos->setIcon(QIcon::fromTheme("system-help"));
    ui->action_propos_de_Dames->setIcon(QIcon::fromTheme("dialog-warning"));
    ui->action_propos_de_Qt->setIcon(QIcon::fromTheme("dialog-warning"));


    connect(ui->action_propos_de_Dames,&QAction::triggered, &_gameController, &checkersController::aboutDames);
    connect(ui->action_propos_de_Qt, &QAction::triggered, &_gameController, &checkersController::aboutQt);
    connect(ui->actionNouvelle_partie, &QAction::triggered, this, &Dames::newGame);
    connect(ui->actionCharger_une_partie, &QAction::triggered, this, &Dames::loadGame);
    connect(ui->actionSauvegarder_la_partie, &QAction::triggered,this, &Dames::saveGame);
    connect(ui->actionQuitter, &QAction::triggered, this, &Dames::close);


    ui->actionNouvelle_partie->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    ui->actionSauvegarder_la_partie->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->actionCharger_une_partie->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    ui->actionQuitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    initializeCheckers();
    ui->statusbar->showMessage("Joueur actif: 1");
}

Dames::~Dames()
{
    delete ui;
}

//La methode newGame permet de charger un nouvelle partie
/* Elle initialise le tableau de jeu*/
void Dames::newGame()
{
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, tr("Abandonner la partie"), tr("Etes-vous sur de vouloir abandonner cette partie pour en commencer une nouvelle"),
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
         _gameController.initializeCheckers(ui->gridBoard);
}

//La methode loadGame permet de charger un jeu déjà sauvegarder antérieurement
void Dames::loadGame()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Charger une partie?"), tr("Abandonner la partie actuelle pour en charger une nouvelle?"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //Chargement du fichier de jeu
        auto fileName = QFileDialog::getOpenFileName(this,
            tr("Charger un fichier de jeu"), "/", tr("Fichier de jeu (*.save)"));
        qDebug() << fileName;

    ui->statusbar->showMessage(_gameController.loadGame(fileName,ui->gridBoard));
    ui->gridBoard->setSpacing(0);
    }
 }

void Dames::saveGame()
{
    auto fileName = QFileDialog::getSaveFileName(this,
        tr("Sauvegarder la partie"), QDir::homePath(), tr("Fichier de jeu (*.save)"));
    fileName = fileName+".save";
    _gameController.saveGame(fileName);
    ui->statusbar->showMessage("Partie Sauvegardée");
}


void Dames::mousePressEvent(QMouseEvent *event)
{    
    QWidget * const widget = childAt(event->pos());
    if (widget) {
        square * selected_square = qobject_cast<square *>(widget);
        if (selected_square )
            ui->statusbar->showMessage(_gameController.OnclickOnBoardSquare(selected_square));
}

}
void Dames::initializeCheckers()
{
    _gameController.initializeCheckers(ui->gridBoard);
    ui->gridBoard->setSpacing(0);
     ui->statusbar->showMessage("Debut d'une nouvelle partie! Joueur actif :1");
}

void Dames::GameOver()
{
    ui->statusbar->showMessage(_gameController.GameOver());

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Nouvelle partie"), tr("Voulez-vous commencer une nouvelle partie"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
       _gameController.initializeCheckers(ui->gridBoard);
        ui->statusbar->showMessage("Debut d'une nouvelle partie! Joueur actif :1");
    }

}

void Dames::createLanguageMenu()
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
