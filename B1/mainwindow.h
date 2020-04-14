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
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    void DDALine(float x1,float y1,float x2,float y2);
    void dottedLine(float x1,float y1,float x2,float y2);
    void dashLine(float x1,float y1,float x2,float y2);
    void dashDotLine(float x1,float y1,float x2,float y2);
};
#endif // MAINWINDOW_H
