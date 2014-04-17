#include <QtGui>
#include <QtOpenGL>
#include <math.h>
#include <time.h>
#include "myglwidget.h"
#include <QTextStream>
#include <QFile>

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot=0;
    yRot=0;
    zRot=0;
    zoom=1;
    cubeCount=8;
    ycubeCount=8;
    zcubeCount=8;
    space=.5;
    red=1.0;
    green=1.0;
    blue=1.0;
    choose=true;
    cubeSize=1.0;
    shape=1;

    phase=0;
    //timer.start(60, this);
}

MyGLWidget::~MyGLWidget()
{
}

static void qNormalizeAngle(int &angle)
 {
     while (angle < 0)
         angle += 360;
     while (angle > 360)
         angle -= 360;
 }

void MyGLWidget::setXRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != xRot)
     {
         xRot = angle;
         emit xRotationChanged(angle);
         updateGL();
     }
 }

void MyGLWidget::setYRotation(int angle)
  {
      qNormalizeAngle(angle);
      if (angle != yRot)
      {
          yRot = angle;
          emit yRotationChanged(angle);
          updateGL();
      }
  }

void MyGLWidget::setZRotation(int angle)
  {
      qNormalizeAngle(angle);
      if (angle != zRot)
      {
          zRot = angle;
          emit zRotationChanged(angle);
          updateGL();
      }
  }

void MyGLWidget::setZoom(int amount)
  {
      if(amount != zoom)
      {
          zoom = amount;
          updateGL();
      }
  }

void MyGLWidget::setCubeCount(int size)
{
    if(size != cubeCount)
    {
        cubeCount = size;
        updateGL();
    }
}

void MyGLWidget::setyCubeCount(int size)
{
    if(size != ycubeCount)
    {
        ycubeCount = size;
        updateGL();
    }
}

void MyGLWidget::setzCubeCount(int size)
{
    if(size != zcubeCount)
    {
        zcubeCount = size;
        updateGL();
    }
}

void MyGLWidget::setLEDsizeDoubleSpinbox(double sizing)
{
    if(sizing != cubeSize)
    {
        cubeSize = sizing;
        updateGL();
    }
}

void MyGLWidget::setSpacingDoubleSpinbox(double spacing)
{
    if(spacing != (space))
    {
        space = (spacing);
        updateGL();
    }
}

void MyGLWidget::setCubeRed()
{
    red=1.0;green=0.0;blue=0.0;
    updateGL();
}

void MyGLWidget::setCubeGreen()
{
    red=0.0;green=1.0;blue=0.0;
    updateGL();
}

void MyGLWidget::setCubeBlue()
{
    red=0.0;green=0.0;blue=1.0;
    updateGL();
}

void MyGLWidget::setCubeYellow()
{
    red=1.0;green=1.0;blue=0.0;
    updateGL();
}

void MyGLWidget::setCubeWhite()
{
    red=1.0;green=1.0;blue=1.0;
    updateGL();
}

void MyGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

}

void MyGLWidget::setCubesLED()
{
    choose = true;
    updateGL();
}


void MyGLWidget::setPointsLED()
{
    choose = false;
    updateGL();
}

void MyGLWidget::setCubeShape()
{
    shape = 1;
    updateGL();
}

void MyGLWidget::setSineShape()
{
    shape = 2;
    updateGL();
}

void MyGLWidget::setFaceShape()
{
    shape = 3;
    updateGL();
}

void MyGLWidget::resizeGL(int w, int h)
{
       // w=500; h=500;
       glViewport( 0, 0, w, h );
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       glOrtho(-100.0, +100.0, -100.0, +100.0, -500.0, 500.0);//left,right,bottom,top,near,far
       glMatrixMode(GL_MODELVIEW);                            //hint:near & far can never be same value

}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, 0.0f);                 //set cube at origin
    glScalef(zoom,zoom,zoom);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    if(shape == 1)
    createCubesOrPoints();
    else if(shape == 2)
    createSineWave();
    else if(shape == 3)
    createFace();

}

void MyGLWidget::createFace()
{
    QStringList stringList;
    QFile textFile("‪C:\\Users\\Benjamin\\Desktop\\face.txt");
    if (textFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&textFile);
       while (!in.atEnd())
       {
          stringList.append(in.readLine());
       }
    }
       foreach(QString str, stringList)
       {
        double x = str.toDouble();
        double y = str.toDouble();
        double z = str.toDouble();
        plotPoint(x,y,z);
       }

}

void MyGLWidget::plotPoint(double x,double y,double z)
{
    glTranslatef(0.0f, 0.0f, 0.0f);
    glTranslatef(x/20, y/20, z/20);

    if(choose == true)
     drawCube();

    if(choose == false)
     drawPoint();
}
/*void MyGLWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        phase+=10;
        updateGL();
    } else {
        MyGLWidget::timerEvent(event);
    }
}*/

void MyGLWidget::createSineWave()                                           //Sine Wave
{

    for(int i=1; i<=zcubeCount; i++)
    {
        for(int i=1; i<=cubeCount; i++)
        {
            double y=((double)ycubeCount/4)*sin((double)i)+(double)phase;

            if(choose == true)
             drawCube();

            if(choose == false)
             drawPoint();

            glTranslated(space+cubeSize, y, 0.0);
        }
        double y=((double)ycubeCount/4)*sin((double)i)+(double)phase;
        glTranslated(-(cubeCount*(space+cubeSize)), -y, space+cubeSize);
    }

}

void MyGLWidget::createCubesOrPoints()                                     //Cube of Leds
{

        for(int i=1;i<=zcubeCount;i++)
        {
            for(int i=1;i<=ycubeCount;i++)
            {
                for(int i=1;i<=cubeCount;i++)
                {
                   if(choose == true)
                    drawCube();

                   if(choose == false)
                    drawPoint();

                    glTranslatef(space+cubeSize, 0.0f, 0.0f);
                }
               glTranslatef(-(cubeCount*(space+cubeSize)), space+cubeSize, 0.0f);
            }
            glTranslatef(0.0f, -(ycubeCount*(space+cubeSize)), space+cubeSize);
        }

}

void MyGLWidget::drawCube()
{
                                                // create 3D-Cube
glBegin(GL_QUADS);

 //qglColor(Qt::green);                             //front
glColor3d(red/1.5,green/1.5,blue/1.5);

glVertex3f(cubeSize/2,cubeSize/2,cubeSize/2);
glVertex3f(-cubeSize/2,cubeSize/2,cubeSize/2);
glVertex3f(-cubeSize/2,-cubeSize/2,cubeSize/2);
glVertex3f(cubeSize/2,-cubeSize/2,cubeSize/2);


                                                    //back

//glColor3f(0.0,0.7,0.0);

glVertex3f(cubeSize/2,cubeSize/2,-cubeSize/2);
glVertex3f(-cubeSize/2,cubeSize/2,-cubeSize/2);
glVertex3f(-cubeSize/2,-cubeSize/2,-cubeSize/2);
glVertex3f(cubeSize/2,-cubeSize/2,-cubeSize/2);


                                                    //top
glColor3d(red/2,green/2,blue/2);

glVertex3f(-cubeSize/2,cubeSize/2,cubeSize/2);
glVertex3f(cubeSize/2,cubeSize/2,cubeSize/2);
glVertex3f(cubeSize/2,cubeSize/2,-cubeSize/2);
glVertex3f(-cubeSize/2,cubeSize/2,-cubeSize/2);


                                                   //bottom
//glColor3f(0.0,0.5,0.0);

glVertex3f(cubeSize/2,-cubeSize/2,cubeSize/2);
glVertex3f(cubeSize/2,-cubeSize/2,-cubeSize/2);
glVertex3f(-cubeSize/2,-cubeSize/2,-cubeSize/2);
glVertex3f(-cubeSize/2,-cubeSize/2,cubeSize/2);

                                                   //right
glColor3d(red,green,blue);

glVertex3f(cubeSize/2,cubeSize/2,cubeSize/2);
glVertex3f(cubeSize/2,-cubeSize/2,cubeSize/2);
glVertex3f(cubeSize/2,-cubeSize/2,-cubeSize/2);
glVertex3f(cubeSize/2,cubeSize/2,-cubeSize/2);


                                                   //left
//glColor3f(0.0,1.0,0.0);

glVertex3f(-cubeSize/2,cubeSize/2,cubeSize/2);
glVertex3f(-cubeSize/2,-cubeSize/2,cubeSize/2);
glVertex3f(-cubeSize/2,-cubeSize/2,-cubeSize/2);
glVertex3f(-cubeSize/2,cubeSize/2,-cubeSize/2);


glEnd();

}

void MyGLWidget::drawPoint()
{
                                                    // create a single point
glBegin(GL_POINTS);

glColor3d(red/1.5,green/1.5,blue/1.5);

glPointSize(10);
glVertex3f(0.0,0.0,0.0);

glEnd();

}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
 {
     lastPos = event->pos();
 }

 void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton)
          {
              setXRotation(xRot + dy);
              setYRotation(yRot + dx);
          } else if (event->buttons() & Qt::RightButton)
            {
              setXRotation(xRot + dy);
              setZRotation(zRot + dx);
            }
     lastPos = event->pos();
 }
