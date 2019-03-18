#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Inventory;
class Game;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Inventory* inventory;
  Game* game;
};

#endif // MAINWINDOW_H
