#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void DDALine(int x1,int y1, int x2, int y2);

    void mousePressEvent(QMouseEvent *event);

    void translatePoints(int x[],int y[], int tx, int ty);

    void rotatePoints(int x[],int y[],float angle);

    void scalePoints(int x[],int y[], float sx, float sy);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    float newpoint[1][3] = {0};
    float dpoints[100][100] = {0};
    int x[100];
    int y[100];
    int flag=0;
    int i=0;
    int cnt=0;
};
#endif // MAINWINDOW_H
