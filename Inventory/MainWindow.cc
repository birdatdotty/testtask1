#include "MainWindow.h"
#include "Game.h"

#include "Db.h"



MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  game = new Game();


  setCentralWidget(game);
  resize(1900,700);
}

MainWindow::~MainWindow()
{

}
