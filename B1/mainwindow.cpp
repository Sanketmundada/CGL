#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage img(600,600, QImage::Format_RGB888);

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

void MainWindow::DDALine(float x1, float y1, float x2, float y2) {
    float dx,dy,x,y,xInc,yInc,len;
    int i=0;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(x2-x1)>abs(y2-y1)) {
        len = abs(x2-x1);
    }
    else {
        len = abs(y2-y1);
    }
    xInc = dx/len;
    yInc = dy/len;
    x=x1;
    y=y1;
    while(i<len) {
        img.setPixel((int)x, (int)y,qRgb(0,255,0));
        x += xInc;
        y += yInc;
        i++;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(img));
    ui->label_5->show();

}

void MainWindow::on_pushButton_clicked()
{
    QString str;
    str = ui->textEdit->toPlainText();
    float x1 = str.toFloat();
    str = ui->textEdit_2->toPlainText();
    float y1 = str.toFloat();
    str = ui->textEdit_3->toPlainText();
    float x2 = str.toFloat();
    str = ui->textEdit_4->toPlainText();
    float y2 = str.toFloat();
    DDALine(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString str;
    str = ui->textEdit->toPlainText();
    float x1 = str.toFloat();
    str = ui->textEdit_2->toPlainText();
    float y1 = str.toFloat();
    str = ui->textEdit_3->toPlainText();
    float x2 = str.toFloat();
    str = ui->textEdit_4->toPlainText();
    float y2 = str.toFloat();
    dottedLine(x1,y1,x2,y2);
}

void MainWindow::dottedLine(float x1, float y1, float x2, float y2) {
    float dx,dy,x,y,xInc,yInc,len;
    int i=0;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(x2-x1)>abs(y2-y1)) {
        len = abs(x2-x1);
    }
    else {
        len = abs(y2-y1);
    }
    xInc = dx/len;
    yInc = dy/len;
    x=x1;
    y=y1;
    while(i<len) {
        if(i%5==0) {
            img.setPixel((int)x, (int)y,qRgb(0,255,0));
        }
        x += xInc;
        y += yInc;
        i++;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(img));
    ui->label_5->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str;
    str = ui->textEdit->toPlainText();
    float x1 = str.toFloat();
    str = ui->textEdit_2->toPlainText();
    float y1 = str.toFloat();
    str = ui->textEdit_3->toPlainText();
    float x2 = str.toFloat();
    str = ui->textEdit_4->toPlainText();
    float y2 = str.toFloat();
    dashLine(x1,y1,x2,y2);
}

void MainWindow::dashLine(float x1, float y1, float x2, float y2) {
    float dx,dy,x,y,xInc,yInc,len;
    int i=0;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(x2-x1)>abs(y2-y1)) {
        len = abs(x2-x1);
    }
    else {
        len = abs(y2-y1);
    }
    xInc = dx/len;
    yInc = dy/len;
    x=x1;
    y=y1;
    while(i<len) {
        if(i%10==0) {
            x+=5*xInc;
            y+=5*yInc;
        }
        img.setPixel((int)x, (int)y,qRgb(0,255,0));
        x += xInc;
        y += yInc;
        i++;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(img));
    ui->label_5->show();
}



void MainWindow::on_pushButton_4_clicked()
{
    QString str;
    str = ui->textEdit->toPlainText();
    float x1 = str.toFloat();
    str = ui->textEdit_2->toPlainText();
    float y1 = str.toFloat();
    str = ui->textEdit_3->toPlainText();
    float x2 = str.toFloat();
    str = ui->textEdit_4->toPlainText();
    float y2 = str.toFloat();
    dashDotLine(x1,y1,x2,y2);
}

void MainWindow::dashDotLine(float x1, float y1, float x2, float y2) {
    float dx,dy,x,y,xInc,yInc,len;
    int i=0;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(x2-x1)>abs(y2-y1)) {
        len = abs(x2-x1);
    }
    else {
        len = abs(y2-y1);
    }
    xInc = dx/len;
    yInc = dy/len;
    x=x1;
    y=y1;
    while(i<len) {
        if(i!=0) {
            if(i%10==0) {
              x+=5*xInc;
              y+=5*yInc;
              img.setPixel((int)x, (int)y,qRgb(0,255,0));
              x+=5*xInc;
              y+=5*yInc;
            }
        }
        img.setPixel((int)x, (int)y,qRgb(0,255,0));
        x += xInc;
        y += yInc;
        i++;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(img));
    ui->label_5->show();
}


