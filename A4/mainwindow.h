#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent *ev);
    void DDALine(int x1,int y1,int x2,int y2);

private:
    Ui::MainWindow *ui;
    int x[100];
    int y[100];
    int flag=0;
    int i=0;
};

#endif // MAINWINDOW_H
