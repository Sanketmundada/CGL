#ifndef LINEDRAWING_H
#define LINEDRAWING_H


class LineDrawing
{
public:
    LineDrawing();
    void dda(float x1,float y1,float x2,float y2);
    int sign(int x);
    QImage getimage();
    void bres(int x1,int y1,int x2,int y2);
};

#endif // LINEDRAWING_H
