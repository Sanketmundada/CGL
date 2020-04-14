#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "linedrawing.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
float x1,x2,y1,y2;
x1=ui->textEdit->toPlainText().toFloat();
y1=ui->textEdit_2->toPlainText().toFloat();
x2=ui->textEdit_3->toPlainText().toFloat();
y2=ui->textEdit_4->toPlainText().toFloat();
LineDrawing l;
l.bres(x1,y1,x1,y2);
l.bres(x1,y2,x2,y2);
l.bres(x2,y2,x2,y1);
l.bres(x2,y1,x1,y1);
float y=(y1+y2)/2,x=(x1+x2)/2;
l.dda(x1,y,x,y1);
l.dda(x,y1,x2,y);
l.dda(x2,y,x,y2);
l.dda(x,y2,x1,y);
float xa=(3*x1 +x2)/4,xb=(x1+3*x2)/4,ya=(3*y1+y2)/4,yb=(y1+3*y2)/4;
l.bres(xa,ya,xb,ya);
l.bres(xb,ya,xb,yb);
l.bres(xa,yb,xb,yb);
l.bres(xa,ya,xa,yb);

ui->label->setPixmap(QPixmap::fromImage(l.getimage()));

}
