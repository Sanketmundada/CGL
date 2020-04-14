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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void mousePressEvent(QMouseEvent *ev);

    void dda(float,float,float,float,QRgb);
    void on_rotate_clicked();

    void on_Yaxis_clicked();

    void on_Xaxis_clicked();

    void on_line_clicked();

private:

    Ui::MainWindow *ui;
    int a[10],b[10],ver,x,y,edges;
    int matrix[10][3];
    bool flag;
};

#endif // MAINWINDOW_H
