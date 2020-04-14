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
    void dda(double x1, double y1, double x2, double y2, QRgb val);
    void mousePressEvent(QMouseEvent *event);
    void cohen(int x1,int y1,int x2,int y2);
    int code(int x1,int y1);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool start;
    int ver,a[100],b[100];
};
#endif // MAINWINDOW_H
