

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initLabels();
    void keyPressEvent(QKeyEvent*) override;

private slots:

    void on_onePlayer_clicked();

    void on_twoPlayer_clicked();

    void on_levelOne_clicked();

    void on_levelTwo_clicked();

    void on_levelThree_clicked();

    void on_levelFour_clicked();

    void on_levelFive_clicked();

    void on_boss_clicked();

    void beginGame(int);

private:
    Ui::MainWindow *ui;
    QLabel *score_title, *score;
    QLabel *win_label, *lose_label;
    QTimer *score_timer;
    Game *game;
};
#endif // MAINWINDOW_H
