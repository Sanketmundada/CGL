#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include "QMouseEvent"
#include "QColorDialog"
#include <cmath>
#include<bits/stdc++.h>
using namespace std;

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

QImage image(700,700,QImage::Format_RGB888);
QRgb value = qRgb(0,255,0);


void MainWindow:: mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton && flag == 0 )
    {
        x[i]=event->pos().x() - 360;
        y[i]=event->pos().y() - 50 ;

        if(i != 0)
           DDALine(x[i-1],y[i-1],x[i],y[i]);
      // image.setPixel(x[i],y[i],value);
       i++;
    }
    if(event->button() == Qt::RightButton && flag == 0)
    {
        flag=1;
        DDALine(x[i-1],y[i-1],x[0],y[0]);

    }
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
        image.setPixel(x,y,value);  //draws pixel with value
        //print pixel
        x+= xinc;
        y+= yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{

    // TRANSLATION
    cnt=0;
    int tx,ty;
    tx= ui->textEdit->toPlainText().toInt();
    ty= ui->textEdit_2->toPlainText().toInt();

    ty = ty*-1;
    //for(int j=0;j<i;j++)
    //    cout<<x[j]<<"\t"<<y[j]<<endl;

    translatePoints(x,y,tx,ty);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::translatePoints(int x[],int y[], int tx, int ty)
{
    //int dx[100],dy[100];
    int tm[3][3] ={0};
    tm[0][0]= tm[1][1]= tm[2][2]=1;
    tm[0][1]=0;
    tm[0][2]=0;
    tm[1][0]=0;
    tm[1][2]=0;

    int a,b;
    for(a=0;a<i;a++)
    {
            newpoint[0][0]=x[a];
            newpoint[0][1]=y[a];
            newpoint[0][2]=1;

        tm[2][0]=tx;
        tm[2][1]=ty;

        for(int p=0;p<3;p++)
        {
            int temp = 0;
            for(int q=0;q<3;q++)
                temp = temp + (newpoint[0][q]*tm[q][p]);

            dpoints[cnt][p]=temp;
        }
        cnt++;
    }
//    for(int j=0;j<i;j++)
//    {
//        dx[j]= x[j]+ tx;
//        dy[j]= y[j]+ ty;

//        if(j >=1)
//        {
//            DDALine(dx[j],dy[j],dx[j-1],dy[j-1]);
//        }
//    }

    for(int p = 0;p<i;p++)
    {
        if(p>=1)
            DDALine(dpoints[p-1][0],dpoints[p-1][1],dpoints[p][0],dpoints[p][1]);
    }
    DDALine(dpoints[i-1][0],dpoints[i-1][1],dpoints[0][0],dpoints[0][1]);

}

void MainWindow::rotatePoints(int x[],int y[],float angle)
{
    cnt= 0;
    cout<<angle<<"\t"<<i<<endl;


    float tm[3][3] ={0};
     tm[2][2]=1;

    tm[0][2]=0;
    tm[1][2]=0;
    tm[2][0]=0;
    tm[2][1]=0;

    tm[0][0]=tm[1][1] = cos(angle);

    tm[0][1] = sin(angle);
    tm[1][0] = -1 * sin(angle);

    int a,b;
    for(a=0;a<i;a++)
    {
            newpoint[0][0]=x[a];
            newpoint[0][1]=y[a];
            newpoint[0][2]=1;

        for(int p=0;p<3;p++)
        {
            int temp = 0;
            for(int q=0;q<3;q++)
                temp = temp + (newpoint[0][q]*tm[q][p]);

            dpoints[cnt][p]=temp;
        }
        cnt++;
    }
    for(int p = 0;p<i;p++)
    {
        if(p>=1)
            DDALine(dpoints[p-1][0],dpoints[p-1][1],dpoints[p][0],dpoints[p][1]);
    }
    DDALine(dpoints[i-1][0],dpoints[i-1][1],dpoints[0][0],dpoints[0][1]);


}

void MainWindow::scalePoints(int x[],int y[], float sx, float sy)
{
    cnt =0 ;

    float tm[3][3] ={0};

    tm[0][0]=sx;
    tm[1][1]=sy;
    tm[2][2]=1;

    tm[0][1]=tm[0][2]=0;
    tm[1][0]=tm[2][0]=0;
    tm[2][1]=tm[1][2]=0;

    int a,b;
    for(a=0;a<i;a++)
    {
            newpoint[0][0]=x[a];
            newpoint[0][1]=y[a];
            newpoint[0][2]=1;

        for(int p=0;p<3;p++)
        {
            int temp = 0;
            for(int q=0;q<3;q++)
                temp = temp + (newpoint[0][q]*tm[q][p]);

            dpoints[cnt][p]=temp;
        }
        cnt++;
    }
    for(int p = 0;p<i;p++)
    {
        if(p>=1)
            DDALine(dpoints[p-1][0],dpoints[p-1][1],dpoints[p][0],dpoints[p][1]);
    }
    DDALine(dpoints[i-1][0],dpoints[i-1][1],dpoints[0][0],dpoints[0][1]);
}

void MainWindow::on_pushButton_2_clicked()
{
    cnt=0;
    int angle= ui->textEdit_3->toPlainText().toInt();

    float a = angle * 3.142 / 180;

    rotatePoints(x,y,a);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    float sx,sy;
    sx= ui->textEdit_4->toPlainText().toFloat();
    sy= ui->textEdit_5->toPlainText().toFloat();


    //for(int j=0;j<i;j++)
    //    cout<<x[j]<<"\t"<<y[j]<<endl;

    scalePoints(x,y,sx,sy);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
