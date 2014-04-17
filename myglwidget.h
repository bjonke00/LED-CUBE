#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
//#include <QBasicTimer>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setZoom(int amount);
    void setCubeCount(int size);
    void setyCubeCount(int size);
    void setzCubeCount(int size);
    void setLEDsizeDoubleSpinbox(double sizing);
    void setSpacingDoubleSpinbox(double spacing);
    void setCubeRed();
    void setCubeGreen();
    void setCubeBlue();
    void setCubeYellow();
    void setCubeWhite();
    void setCubesLED();
    void setPointsLED();
    void setCubeShape();
    void setSineShape();
    void setFaceShape();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //void timerEvent(QTimerEvent *event);              //attempt at animation

private:
    void createSineWave();
    void createCubesOrPoints();                         //draws many cubes or points in shape of cube
    void drawCube();                                    //draws a single cube
    void drawPoint();                                   //draws a single point
    void createFace();                                  //draws face
    void plotPoint(double x, double y, double z);                //plot each point in face
    bool choose;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    int zoom;
    int cubeCount;
    int ycubeCount;
    int zcubeCount;
    double space;
    double red;
    double green;
    double blue;
    double cubeSize;
    int shape;
    int phase;

    //QBasicTimer timer;

};

#endif // MYGLWIDGET_H
