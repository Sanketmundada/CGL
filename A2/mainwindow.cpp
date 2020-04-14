#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

QImage image(800, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString str = ui->textEdit->toPlainText();
    int x = str.toInt();
    str = ui->textEdit_2->toPlainText();
    int y = str.toInt();
    str = ui->textEdit_3->toPlainText();
    int r = str.toInt();
    BresenhamCircle(x,y,r);
}

void MainWindow::BresenhamCircle(int x,int y,int r) {
    int x1=0;
    int y1=r;
    int S = 3 - (2*r);
    drawCircle(x,y,x1,y1);
    while(y1>=x1) {
        x1++;
        if(S>=0) {
            y1--;
            S = S + 4*(x1-y1) + 10;
        }
        else {
            S = S + 4*x1 + 6;
        }
        drawCircle(x,y,x1,y1);
    }
    ui->label_4->setPixmap(QPixmap::fromImage(image));
    ui->label_4->show();
}

void MainWindow::drawCircle(int xc,int yc,int x,int y) {
    QRgb value;
    value=qRgb(0,255,0);
    image.setPixel(xc+x, yc+y,value);
    image.setPixel(xc-x, yc+y,value);
    image.setPixel(xc+x, yc-y,value);
    image.setPixel(xc-x, yc-y,value);
    image.setPixel(xc+y, yc+x,value);
    image.setPixel(xc-y, yc+x,value);
    image.setPixel(xc+y, yc-x,value);
    image.setPixel(xc-y, yc-x,value);
}

void MainWindow::DDACircle(float x1,float y1,float r1) {
    float xc1,xc2,yc1,yc2,eps,sx,sy;
        int i, val;
        xc1=r1;
        yc1=0;
        sx=xc1;
        sy=yc1;
        i=0;
        do
        {
            val=pow(2, i);
            i++;
        }while(val<r1);
        eps = 1/pow(2,i-1);
        do
        {
            xc2 = xc1 + yc1*eps;
            yc2 = yc1 - eps*xc2;
            image.setPixel(x1+xc2,y1-yc2, qRgb(0, 255, 0));
            xc1=xc2;
            yc1=yc2;
        }while((yc1-sy)<eps || (sx-xc1)>eps);
        ui->label_4->setPixmap(QPixmap::fromImage(image));
        ui->label_4->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    QString str = ui->textEdit->toPlainText();
    float x = str.toFloat();
    str = ui->textEdit_2->toPlainText();
    float y = str.toFloat();
    str = ui->textEdit_3->toPlainText();
    float r = str.toFloat();
    DDACircle(x,y,r);
}

void MainWindow::drawLine(float u1,float v1,float u2,float v2) {
    int steps;
    float dx,dy;
    dx=u2-u1;
    dy=v2-v1;
    if(abs(dx)>abs(dy))
            steps=abs(dx);
        else
            steps=abs(dy);

        QRgb value;
        int i;
        float x=u1;
        float y=v1;
        value=qRgb(0,255,0);
        float xinc,yinc;

        xinc=dx/steps;
        yinc=dy/steps;

        for(i=0;i<steps;i++)
        {
            x=x+xinc;
            y=y+yinc;
            image.setPixel(x,y,value);
        }
        ui->label_4->setPixmap(QPixmap::fromImage(image));
        ui->label_4->show();

}




void MainWindow::on_pushButton_3_clicked()
{
    QString str = ui->textEdit->toPlainText();
    float x = str.toFloat();
    str = ui->textEdit_2->toPlainText();
    float y = str.toFloat();
    str = ui->textEdit_3->toPlainText();
    float r = str.toFloat();
    DDACircle(x,y,r);
    float r2 = r/2;
    BresenhamCircle(x,y,r2);
    float x1 = x;
    float y1 = y-r;
    float x2 = x + (0.866*r);
    float y2 = y + (r/2);
    float x3 = x - (0.866*r);
    float y3 = y2;
    drawLine(x1,y1,x2,y2);
    drawLine(x1,y1,x3,y3);
    drawLine(x2,y2,x3,y3);
}
