#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QtDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRgb val=qRgb(255,0,255);
    start=true;
    ver=0;
    dda(200, 200, 400, 200, val);
    dda(200, 200, 200, 400, val);
    dda(400, 200, 400, 400, val);
    dda(200, 400, 400, 400, val);

}

QImage img=QImage(500, 500,QImage::Format_RGB888);
const int Left=1, Right=2, Bottom=4, Top=8, inside=0;

const int xmin=200, ymin=200, xmax=400, ymax=400;

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRgb val=qRgb(0, 255, 0);
    int p=event->pos().x()-26;
    int q=event->pos().y()-11;

    a[ver]=p;
    b[ver]=q;

    if(start){

        if(event->button()==Qt::RightButton)
        {
            dda(a[ver],a[ver],a[0],b[0],val);
            start=false;
        }
        else{

            if(ver>0){
                dda(a[ver],b[ver],a[ver-1],b[ver-1],val);
            }


        }
        ver++;


    }

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: dda(double x1, double y1, double x2, double y2, QRgb val)
{
    double dx=x2-x1;
    double dy=y2-y1;
    double x=x1, y=y1;
    double steps=abs(dx)>abs(dy) ? abs(dx):abs(dy);

    double xinc=dx/steps;
    double yinc=dy/steps;
    for(int i=1;i<=steps;i++){

        img.setPixel(x,y,val);
        x+=xinc;
        y+=yinc;


    }

    ui->label->setPixmap(QPixmap::fromImage(img));

}


int MainWindow::code(int x1, int y1){

    int c=inside;
    if(x1<xmin){
        c=c | Left;
    }

    if(x1>xmax){
        c=c |  Right;
    }

    if(y1<ymin){
        c=c | Bottom;
    }

    if(y1>ymax){
        c=c | Top;
    }

    return c;


}


void MainWindow::cohen(int x1, int y1, int x2, int y2)
{

    int code1=code(x1,y1);
    int code2=code(x2,y2);

    int a=x1, b=y1, c=x2, d=y2;
    bool accept=false;

    while(true){

        if(code1==0 && code2==0){
            accept=true;
            break;
        }
        else if(code1 & code2){
            break;
        }
        else{

            int codeout;
            if(code1!=0){
                codeout=code1;
            }
            else{
                codeout=code2;
            }
            double x,y;

            if(codeout & Top){
                y=ymax;
                x=x1+ double((x2-x1)*(ymax-y1)/(y2-y1));
            }
            else if(codeout & Bottom){
                y=ymin;
                x=x1 + double((ymin-y1)*(x2-x1)/(y2-y1));
            }
            else if(codeout & Left){
                x=xmin;
                y=y1 + double((xmin-x1)*(y2-y1)/(x2-x1));
            }
            else if(codeout & Right){
                x=xmax;
                y=y1 + double((xmax-x1)*(y2-y1)/(x2-x1));
            }

            if(codeout==code1){
                x1=x;
                y1=y;
                code1=code(x1,y1);
            }
            else{
                x2=x;
                y2=y;
                code2=code(x2,y2);
            }


        }




    }

    if(accept){
        QRgb old=qRgb(0, 0, 0);
        dda(a,b,c,d,old);
        QRgb ne=qRgb(0,0,255);
        dda(x1,y1,x2,y2,ne);
    }


}




void MainWindow::on_pushButton_clicked()
{
    for(int i=1;i<ver;i++){
        cohen(a[i],b[i],a[i-1],b[i-1]);
    }
    cohen(a[ver-1],b[ver-1],a[0],b[0]);
}
