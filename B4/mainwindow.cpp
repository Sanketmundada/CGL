#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<QtMath>
QRgb newc = qRgb(100,100,255);
QImage image(600,600,QImage::Format_RGB888);
QRgb value = qRgb(255,128,56);
QRgb white = qRgb(255,255,255);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<3;j++)
        {
            matrix[i][j]=0;
        }
        matrix[i][2]=1;
    }
    ver=0;
    flag=true;
    edges=0;
    ui->setupUi(this);
    dda(300,0,300,600,white);
    dda(0,300,600,300,white);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dda(float x1, float y1, float x2, float y2,QRgb value)
{

    float dx=x2-x1;
    float dy=y2-y1;
    float step,Xinc,Yinc;
    if(abs(dx)>abs(dy)){
        step=abs(dx);
    }
    else{
        step=abs(dy);
    }
    Xinc=dx/step;
    Yinc=dy/step;
    for(int i=1;i<=step;i++){
        image.setPixel(x1,y1,value);
        x1=x1+Xinc;
        y1=y1+Yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(flag)
    {
        if(ev->button()==Qt::RightButton)
        {
            x=ev->pos().x();
            y=ev->pos().y();
            flag=false;
            edges=ver;
            dda(a[ver-1],b[ver-1],a[0],b[0],value);
        }
        else if(ev->button()==Qt::LeftButton)
        {
            int p=ev->pos().x();
                        int q=ev->pos().y()-25;
                        image.setPixel(p,q,value);
                        a[ver]=p;
                        b[ver]=q;
                        matrix[ver][0]=p;
                        matrix[ver][1]=q;
                        if(ver>=1)
                        {
                            dda(a[ver],b[ver],a[ver-1],b[ver-1],value);

                        }
                        ver++;
        }
    }
}

void MainWindow::on_rotate_clicked()
{
    float angle = ui->textEdit->toPlainText().toFloat();
    angle = qDegreesToRadians(angle);
    float transformation[3][3];

        float ans[edges][3];
        transformation[0][0]=1.0;   transformation[0][1]=0.0;  transformation[0][2]=0.0;
        transformation[1][0]=0.0;   transformation[1][1]=1.0;  transformation[1][2]=0.0;
        transformation[2][0]=-(float)x;  transformation[2][1]=-(float)y; transformation[2][2]=1.0;
        double sum;
        float rot[3][3];
        rot[0][0]=cos(angle);   rot[0][1]=sin(angle);  rot[0][2]=0;
        rot[1][0]=-sin(angle);  rot[1][1]=cos(angle);  rot[1][2]=0;
        rot[2][0]=0;            rot[2][1]=0;           rot[2][2]=1;
        for(int i=0;i<edges;i++)
        {
            for(int j=0;j<3;j++)
            {
                sum=0;
                for(int k=0;k<3;k++)
                {
                    sum+=((float)transformation[i][k])*rot[k][j];
                 }
                 ans[i][j]=sum;
             }
         }
           transformation[0][0]=1.0;   transformation[0][1]=0.0;  transformation[0][2]=0.0;
           transformation[1][0]=0.0;   transformation[1][1]=1.0;  transformation[1][2]=0.0;
           transformation[2][0]=(float)x;  transformation[2][1]=(float)y; transformation[2][2]=1.0;
           float intermediate[edges][3];
           for(int i=0;i<edges;i++)
              {
                  for(int j=0;j<3;j++)
                  {sum=0;
                      for(int k=0;k<3;k++)
                      {
                          sum+=((float)ans[i][k])*transformation[k][j];
                      }
                      intermediate[i][j]=sum;
                  }
              }
           float final[edges][3];
           for(int i=0;i<edges;i++)
              {
                  for(int j=0;j<3;j++)
                  {sum=0;
                      for(int k=0;k<3;k++)
                      {
                          sum+=((float)matrix[i][k])*intermediate[k][j];
                      }
                      final[i][j]=sum;
                  }
              }

           for(int i=1;i<edges;++i) {
               dda(final[i][0],final[i][1],final[i-1][0],final[i-1][1],newc);
                          if(i==edges-1) {
                              dda(final[i][0],final[i][1],final[0][0],final[0][1],newc);
                              break;
               }
           }
}

void MainWindow::on_Yaxis_clicked()
{
    int reflection[3][3];
        for(int i=0;i<edges;i++)
        {
            matrix[i][0]-=300;
            matrix[i][1]-=300;
        }
        reflection[0][0]=-1;    reflection[0][1]=0;     reflection[0][2]=0;
        reflection[1][0]=0;     reflection[1][1]=1;     reflection[1][2]=0;
        reflection[2][0]=0;     reflection[2][1]=0;     reflection[2][2]=0;
        int final[edges][3];
        int sum=0;
        for(int i=0;i<edges;++i)
        {
            for(int j=0;j<3;j++)
            {
                sum=0;
                for(int k=0;k<3;k++)
                {
                    sum+=matrix[i][k]*reflection[k][j];
                }
                final[i][j]=sum;
            }
        }
        for(int i=1;i<edges;++i)
         {
                dda(final[i][0]+300,final[i][1]+300,final[i-1][0]+300,final[i-1][1]+300,newc);
                if(i==edges-1) {
                    dda(final[i][0]+300,final[i][1]+300,final[0][0]+300,final[0][1]+300,newc);
                    break;
                }
            }
}

void MainWindow::on_Xaxis_clicked()
{
    int reflection[3][3];
        for(int i=0;i<edges;i++)
        {
            matrix[i][0]-=300;
            matrix[i][1]-=300;
        }
        reflection[0][0]=1;    reflection[0][1]=0;     reflection[0][2]=0;
        reflection[1][0]=0;     reflection[1][1]=-1;     reflection[1][2]=0;
        reflection[2][0]=0;     reflection[2][1]=0;     reflection[2][2]=0;
        int final[edges][3];
        int sum=0;
        for(int i=0;i<edges;++i)
        {
            for(int j=0;j<3;j++)
            {
                sum=0;
                for(int k=0;k<3;k++)
                {
                    sum+=matrix[i][k]*reflection[k][j];
                }
                final[i][j]=sum;
            }
        }
        for(int i=1;i<edges;++i)
         {
                dda(final[i][0]+300,final[i][1]+300,final[i-1][0]+300,final[i-1][1]+300,newc);
                if(i==edges-1) {
                    dda(final[i][0]+300,final[i][1]+300,final[0][0]+300,final[0][1]+300,newc);
                    break;
                }
            }
}

void MainWindow::on_line_clicked()
{
    QRgb linec = qRgb(55,55,0);
        dda(1,599,599,1,linec);
        int reflection[3][3];
        for(int i=0;i<edges;i++)
        {
            matrix[i][0]-=300;
            matrix[i][1]-=300;
        }
        reflection[0][0]=0;    reflection[0][1]=-1;     reflection[0][2]=0;
        reflection[1][0]=-1;     reflection[1][1]=0;     reflection[1][2]=0;
        reflection[2][0]=0;     reflection[2][1]=0;     reflection[2][2]=0;
        int final[edges][3];
        int sum=0;
        for(int i=0;i<edges;++i)
        {
            for(int j=0;j<3;j++)
            {
                sum=0;
                for(int k=0;k<3;k++)
                {
                    sum+=matrix[i][k]*reflection[k][j];
                }
                final[i][j]=sum;
            }
        }
        for(int i=1;i<edges;++i)
         {
                dda(final[i][0]+300,final[i][1]+300,final[i-1][0]+300,final[i-1][1]+300,newc);
                if(i==edges-1) {
                    dda(final[i][0]+300,final[i][1]+300,final[0][0]+300,final[0][1]+300,newc);
                    break;
                }
            }

}
