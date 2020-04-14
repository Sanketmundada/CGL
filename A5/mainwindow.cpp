#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QDebug>
#include<windows.h>
 static QImage image(600,600,QImage::Format_RGB888);
 QRgb col=qRgb(0,255,0);
 QRgb old=qRgb(0,0,0);
 int a[10][4],sf[8][2],ver=0;
 void clear();
 void delay();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw();
    qDebug()<<"xfsfgdfgdgfdf";
    Sleep(10000);
    image.fill(old);
    rotate();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rotate()
{

        float theta = 3.14 / 4;

        for(int i=0;i<10;i++){
           int x=a[i][0] ;
           int y=a[i][1];
           a[i][0]  = x*cos(theta) -y*sin(theta);
           a[i][1]  = x*sin(theta) +y*cos(theta);

           x=a[i][2] ;
           y=a[i][3];
           a[i][2]  = x*cos(theta) -y*sin(theta);
           a[i][3]  = x*sin(theta) +y*cos(theta);

        }

        for(int i=0;i<=9;i++){
        //draw rotated board
              dda(a[i][0],a[i][1],a[i][2],a[i][3]);
                qDebug()<<a[i][0]<<a[i][1]<<a[i][2]<<a[i][3];
        }
        for(int i=0;i<10;i++){
           int x=sf[i][0] ;
           int y=sf[i][1];
           sf[i][0]  = x*cos(theta) -y*sin(theta);
           sf[i][1]  = x*sin(theta) +y*cos(theta);

        }

        seedfill(200,225,old,col);
        seedfill(200,285,old,col);
        seedfill(200,345,old,col);
        seedfill(200,415,old,col);
        seedfill(130,285,old,col);
        seedfill(270,285,old,col);
        seedfill(130,345,old,col);
        seedfill(270,345,old,col);

        ui->label->setPixmap(QPixmap::fromImage(image));
}

int sign(int a){
    if(a<0)
        return -1;
    else if(a>0)
        return 1;
    else return 0;

}

void MainWindow::dda(int x1, int y1,int x2,int y2){

    int i=1;
    float xi,yi;
 QRgb value = qRgb(0,255,0);


    float length = abs(x2-x1) > abs(y2-y1) ? abs(x2-x1) : abs(y2-y1);
    xi = (x2-x1)/length;
    yi = (y2-y1)/length;


    float x= x1 + 0.5*sign(xi);
    float y= y1 + 0.5*sign(yi);

    while(i<=length)  {

        image.setPixel(floor(x)+200,floor(y)+200,value);
        x = x + xi;
        y = y + yi;

        i++;
    }
}

void MainWindow::draw(){

    int len=200;
    int inc=len/4;

      for(int j=0,i=0;i<=len;i=i+inc,j++){
          a[j][0]=a[j][2]=i; a[j][1]=0; a[j][3]=len;
          j++;
          a[j][1]=a[j][3]=i; a[j][0]=0; a[j][2]=len;
      }

      for(int i=0;i<10;i++){
          //draw chess board
        dda(a[i][0],a[i][1],a[i][2],a[i][3]);
      }

      int j=200,m=inc/2;

      int x=0;

      for(int k=0;k<=1;k++){

       for(int i=j;i<=len+200-m;i=i+len/2){
         sf[x][0]=i+m; sf[x][1]=j+m;
           x++;
         sf[x][0]=i+m; sf[x][1]=j+5*m;
           x++;
        //   qDebug()<<x<<i+m<<j+m<<j+5*m;
       }
         j=j+len/4;
      }

      for(int j=0;j<8;j++){
          seedfill(sf[j][0],sf[j][1],old,col);
         // qDebug()<<sf[j][0]<<sf[j][1];
      }

//     rotate();

ui->label->setPixmap(QPixmap::fromImage(image));

}


void MainWindow::seedfill(int x,int y,QRgb old,QRgb col){

        QRgb curr=image.pixel(x,y);
        if(curr!=old)
            return;
            image.setPixel(x,y,col);
            seedfill(x,y+1,old,col);
            seedfill(x-1,y,old,col);
            seedfill(x,y-1,old,col);
            seedfill(x+1,y,old,col);

}
