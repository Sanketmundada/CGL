#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include "QMouseEvent"
#include "QColorDialog"
#include <cmath>
#include<bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
QImage image(700,700,QImage::Format_RGB888);
QRgb value = qRgb(0,255,0);
QColor value2;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
value2=QColorDialog::getColor();
ui->label->show();

}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
if(ev->button() == Qt::LeftButton && flag == 0)
{
     x[i]=ev->pos().x()-200 ;
     y[i]=ev->pos().y() +130;

     if(i != 0)
        DDALine(x[i-1],y[i-1],x[i],y[i]);
   // image.setPixel(x[i],y[i],value);
    i++;
}

if(ev->button() == Qt::RightButton)
    flag=1;

}


void MainWindow::DDALine(int x1,int y1, int x2, int y2)
{
    float x,y;
    float dx,dy;

    dx=x2-x1;     // Calculating dx
    dy=y2-y1;     // Calculating dy

    int steps=(abs(dx)>abs(dy))?abs(dx):abs(dy);

    float xinc,yinc;

    if(steps != 0)          // Calculating Xinc and Yinc
    {
         xinc= dx/ steps;
         yinc= dy/ steps;
    }

    x=x1+0.5;
    y=y1+0.5;
    while(steps--)
    {
        image.setPixel(x,y,value2.rgb());  //draws pixel with value
        //print pixel
        x+= xinc;
        y+= yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    //
}
