#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "linedrawing.h"

LineDrawing::LineDrawing()
{

}
QImage img=QImage(500,500,QImage::Format_RGB888);


QImage LineDrawing::getimage()
{
    return img;
}

void LineDrawing::dda(float x1,float y1,float x2,float y2)
{
    QRgb val=qRgb(0,255,0);
    float dx=x2-x1,dy=y2-y1;
    float steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    float xinc=dx/steps,yinc=dy/steps;
    float x=x1-(0.5*sign(dx)),y=y1-0.5*sign(dy);
    for(int i=0;i<=steps;i++)
    {
       img.setPixel(x,y,val);
       x+=xinc;
       y+=yinc;
    }

}
void LineDrawing::bres(int x1,int y1,int x2,int y2)
{
    QRgb val=qRgb(0,0,255);
    int interchange,sx,sy,dx,dy,e;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    sx=sign(x2-x1);
    sy=sign(y2-y1);
    if(dy>dx)

    {
        int temp=dy;
        dy=dx;
        dx=temp;
        interchange=1;
    }
    else
    {
        interchange=0;
    }
    e=2*dy-dx;
    int x=x1,y=y1;

    for(int i=0;i<dx;i++)
    {
    img.setPixel(x,y,val);
while(e>=0)
{
if(interchange)
{
x+=sx;
    }
else
{
    y+=sy;
}
e-=2*dx;
}
if(interchange)
{
    y+=sy;
}
else
{
    x+=sx;

}
e+=2*dy;
    }
}


int LineDrawing::sign(int x)
{
    if(x==0)
    {
        return 0;

    }
    if(x>0)
    {
        return 1;

    }
    return -1;
}
