#include <QtGui>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
//#include <QLineEdit>
#include <QtWidgets>
#include <QMainWindow>
#include "window.h"
#include "myglwidget.h"

Window::Window()
     {
        MyGLWidget *myglWidget = new MyGLWidget;
                                                                                            //Create sliders
        xSlider = createSlider();
        ySlider = createSlider();
        zSlider = createSlider();
        zoomSlider = createSlider();

        CubeCountSpinbox = createSpinbox();
        yCubeCountSpinbox = createSpinbox();
        zCubeCountSpinbox = createSpinbox();

        LEDsizeDoubleSpinbox = createDoubleSpinbox();
        spacingDoubleSpinbox = createDoubleSpinbox();

        redRadiobutton = createredRadiobutton();
        greenRadiobutton = creategreenRadiobutton();
        blueRadiobutton = createblueRadiobutton();
        yellowRadiobutton = createyellowRadiobutton();
        whiteRadiobutton = createwhiteRadiobutton();

        cubeLEDRadiobutton = createcubeLEDRadiobutton();
        pointLEDRadiobutton = createpointLEDRadiobutton();

        cubeRadiobutton = createcubeRadioButton();
        sineRadiobutton = createsineRadioButton();
        faceRadiobutton = createfaceRadioButton();

                                                                                                                         //Connect sliders to rotations
        connect(xSlider, SIGNAL(valueChanged(int)), myglWidget, SLOT(setXRotation(int)));
        connect(myglWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
        connect(ySlider, SIGNAL(valueChanged(int)), myglWidget, SLOT(setYRotation(int)));
        connect(myglWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
        connect(zSlider, SIGNAL(valueChanged(int)), myglWidget, SLOT(setZRotation(int)));
        connect(myglWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

        connect(zoomSlider, SIGNAL(valueChanged(int)), myglWidget, SLOT(setZoom(int)));
        //connect(myglWidget, SIGNAL(ZoomChanged(int)), zoomSlider, SLOT(setValue(int)));

        connect(CubeCountSpinbox, SIGNAL(valueChanged(int)), myglWidget, SLOT(setCubeCount(int)));                      //Connect (number of led cubes) spinbox with cube
        connect(yCubeCountSpinbox, SIGNAL(valueChanged(int)), myglWidget, SLOT(setyCubeCount(int)));
        connect(zCubeCountSpinbox, SIGNAL(valueChanged(int)), myglWidget, SLOT(setzCubeCount(int)));
        //connect(myglWidget, SIGNAL(CubeCountChanged(int)), CubeCountSpinbox, SLOT(setValue(int)));

        connect(LEDsizeDoubleSpinbox,SIGNAL(valueChanged(double)), myglWidget, SLOT(setLEDsizeDoubleSpinbox(double)));
        connect(spacingDoubleSpinbox, SIGNAL(valueChanged(double)), myglWidget, SLOT(setSpacingDoubleSpinbox(double))); //Connect spacing doublespinbox with cube
        //connect(myglWidget, SIGNAL(spacingDoubleSpinboxChanged(double)), spacingDoubleSpinbox, SLOT(setValue(double)));

        connect(redRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setCubeRed()));                                     //Connect color radiobuttons
        connect(greenRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setCubeGreen()));
        connect(blueRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setCubeBlue()));
        connect(yellowRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setCubeYellow()));
        connect(whiteRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setCubeWhite()));

        connect(cubeLEDRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setCubesLED()));
        connect(pointLEDRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setPointsLED()));

        connect(cubeRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setCubeShape()));
        connect(sineRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setSineShape()));
        connect(faceRadiobutton, SIGNAL(pressed()), myglWidget, SLOT(setFaceShape()));


        centralWidget = new QWidget;
        setCentralWidget(centralWidget);
        myglWidgetArea = new QScrollArea;
        myglWidgetArea->setWidget(myglWidget);
        myglWidgetArea->setWidgetResizable(true);
        myglWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myglWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myglWidgetArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        myglWidgetArea->setMinimumSize(500, 500);
                                                                                            //Layout
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(createTransformsGroup());
        mainLayout->addWidget(createResolutionGroup());
        mainLayout->addWidget(createLEDColorGroup());
        mainLayout->addWidget(createLEDAppearanceGroup());
        mainLayout->addWidget(createLEDShapeGroup());
        setLayout(mainLayout);
        setMaximumSize(860,549);
        //resize(300,400);

        QHBoxLayout *centralLayout = new QHBoxLayout;
        centralLayout->addWidget(myglWidgetArea);
        centralLayout->addStretch();
        centralLayout->addSpacing(35);
        centralLayout->addLayout(mainLayout);
        centralWidget->setLayout(centralLayout);

        setWindowTitle("Cube");
       // resize(500, 400);

     }

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360);
    return slider;
}

                                                                    // Transforms
QGroupBox *Window::createTransformsGroup()
 {
     QGroupBox *groupBox = new QGroupBox("Transforms");

     QLabel *label1 = new QLabel("X Rotation");
     QLabel *label2 = new QLabel("Y Rotation");
     QLabel *label3 = new QLabel("Z Rotation");
     QLabel *label4 = new QLabel("   Zoom   ");

     QSpinBox *spinbox1 = new QSpinBox;
     QSpinBox *spinbox2 = new QSpinBox;
     QSpinBox *spinbox3 = new QSpinBox;
     QSpinBox *spinbox4 = new QSpinBox;

                                                                   //Set Ranges

     zoomSlider->setRange(1, 15);

     spinbox1->setRange(0, 360);
     spinbox2->setRange(0, 360);
     spinbox3->setRange(0, 360);

                                                                    //Connect sliders to spinboxes

     QObject::connect(xSlider,SIGNAL(valueChanged(int)),
                      spinbox1, SLOT(setValue(int)));
     QObject::connect(spinbox1,SIGNAL(valueChanged(int)),
                      xSlider, SLOT(setValue(int)));
     QObject::connect(ySlider,SIGNAL(valueChanged(int)),
                      spinbox2, SLOT(setValue(int)));
     QObject::connect(spinbox2,SIGNAL(valueChanged(int)),
                      ySlider, SLOT(setValue(int)));
     QObject::connect(zSlider,SIGNAL(valueChanged(int)),
                      spinbox3, SLOT(setValue(int)));
     QObject::connect(spinbox3,SIGNAL(valueChanged(int)),
                      zSlider, SLOT(setValue(int)));
     QObject::connect(zoomSlider,SIGNAL(valueChanged(int)),
                      spinbox4, SLOT(setValue(int)));
     QObject::connect(spinbox4,SIGNAL(valueChanged(int)),
                      zoomSlider, SLOT(setValue(int)));

                                                                    //Set values

     xSlider->setValue(30);
     ySlider->setValue(330);
     zSlider->setValue(0);
     zoomSlider->setValue(5);

                                                                    //Layout

     QHBoxLayout *UpperTopLayout = new QHBoxLayout;
     UpperTopLayout->addWidget(label1);
     UpperTopLayout->addWidget(xSlider);
     UpperTopLayout->addWidget(spinbox1);

     QHBoxLayout *LowerTopLayout = new QHBoxLayout;
     LowerTopLayout->addWidget(label2);
     LowerTopLayout->addWidget(ySlider);
     LowerTopLayout->addWidget(spinbox2);

     QHBoxLayout *UpperBottomLayout = new QHBoxLayout;
     UpperBottomLayout->addWidget(label3);
     UpperBottomLayout->addWidget(zSlider);
     UpperBottomLayout->addWidget(spinbox3);

     QHBoxLayout *LowerBottomLayout = new QHBoxLayout;
     LowerBottomLayout->addWidget(label4);
     LowerBottomLayout->addWidget(zoomSlider);
     LowerBottomLayout->addWidget(spinbox4);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(UpperTopLayout);
     mainLayout->addLayout(LowerTopLayout);
     mainLayout->addLayout(UpperBottomLayout);
     mainLayout->addLayout(LowerBottomLayout);

     groupBox->setLayout(mainLayout);

     return groupBox;
 }


QSpinBox *Window::createSpinbox()
{
    QSpinBox *spinbox = new QSpinBox;
    spinbox->setRange(0, 100);
    spinbox->setValue(8);
    return spinbox;
}

QDoubleSpinBox *Window::createDoubleSpinbox()
{
    QDoubleSpinBox *doubleSpinbox = new QDoubleSpinBox;

    //spacingLineEdit->setValidator(new QDoubleValidator(0,.01,10.0,this));
    //spacingLineEdit->setText("enter spacing");
    doubleSpinbox->setRange(0.1, 10.0);
    doubleSpinbox->setValue(0.5);
    return doubleSpinbox;
}

                                                                    //Resolution aka led count
QGroupBox *Window::createResolutionGroup()
{

    QGroupBox *groupBox = new QGroupBox("LED Count");

    QLabel *label1 = new QLabel("X");
    QLabel *label2 = new QLabel("Y");
    QLabel *label3 = new QLabel("Z");
    QLabel *label4 = new QLabel("Spacing");
    QLabel *label5 = new QLabel("inches");
    QLabel *label6 = new QLabel("LED Size");

    LEDsizeDoubleSpinbox->setValue(1);

    //QLineEdit *lineEdit = new QLineEdit;

    //QSpinBox *spinbox2 = new QSpinBox;
    //QSpinBox *spinbox3 = new QSpinBox;

                                                                    //Connect spinboxes

    /*QObject::connect(CubeCountSpinbox,SIGNAL(valueChanged(int)),
                     spinbox2, SLOT(setValue(int)));
    QObject::connect(CubeCountSpinbox,SIGNAL(valueChanged(int)),
                     spinbox3, SLOT(setValue(int)));
    QObject::connect(spinbox2,SIGNAL(valueChanged(int)),
                     CubeCountSpinbox, SLOT(setValue(int)));
    QObject::connect(spinbox2,SIGNAL(valueChanged(int)),
                     spinbox3, SLOT(setValue(int)));
    QObject::connect(spinbox3,SIGNAL(valueChanged(int)),
                     CubeCountSpinbox, SLOT(setValue(int)));
    QObject::connect(spinbox3,SIGNAL(valueChanged(int)),
                     spinbox2, SLOT(setValue(int))); */

                                                                    //Set ranges and values

    /*CubeCountSpinbox->setRange(0,100);
    yCubeCountSpinbox->setRange(0,100);
    zCubeCountSpinbox->setRange(0,100);

    CubeCountSpinbox->setValue(8);
    yCubeCountSpinbox->setValue(8);
    zCubeCountSpinbox->setValue(8);*/

                                                                        //Layout

    QHBoxLayout *Top = new QHBoxLayout;
    Top->addWidget(label1);
    Top->addWidget(CubeCountSpinbox);
    Top->addStretch();
    Top->addWidget(label2);
    Top->addWidget(yCubeCountSpinbox);
    Top->addStretch();
    Top->addWidget(label3);
    Top->addWidget(zCubeCountSpinbox);
    Top->addStretch();

    QHBoxLayout *Bottom = new QHBoxLayout;
    Bottom->addWidget(label4);
    Bottom->addWidget(spacingDoubleSpinbox);
    Bottom->addWidget(label5);
    Bottom->addStretch();

    QHBoxLayout *Under = new QHBoxLayout;
    Under->addWidget(label6);
    Under->addWidget(LEDsizeDoubleSpinbox);
    Under->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(Top);
    mainLayout->addLayout(Bottom);
    mainLayout->addLayout(Under);

    groupBox->setLayout(mainLayout);

    return groupBox;
}

QRadioButton *Window::createredRadiobutton()
{
    QRadioButton *redRadiobutton = new QRadioButton("Red");

    return redRadiobutton;
}

QRadioButton *Window::creategreenRadiobutton()
{
    QRadioButton *greenRadiobutton = new QRadioButton("Green");

    return greenRadiobutton;
}

QRadioButton *Window::createblueRadiobutton()
{
    QRadioButton *blueRadiobutton = new QRadioButton("Blue");

    return blueRadiobutton;
}

QRadioButton *Window::createyellowRadiobutton()
{
    QRadioButton *yellowRadiobutton = new QRadioButton("Yellow");

    return yellowRadiobutton;
}

QRadioButton *Window::createwhiteRadiobutton()
{
    QRadioButton *whiteRadiobutton = new QRadioButton("White");
    whiteRadiobutton->setChecked(true);

    return whiteRadiobutton;
}
QGroupBox *Window::createLEDColorGroup()
 {
     QGroupBox *groupBox = new QGroupBox("LED Colors");

     //QRadioButton *radio1 = new QRadioButton("Red");
     //QRadioButton *radio2 = new QRadioButton("Blue");
     //QRadioButton *radio3 = new QRadioButton("Green");
     //QRadioButton *radio4 = new QRadioButton("Yellow");
     //QRadioButton *radio5 = new QRadioButton("White");

     //greenRadiobutton->setChecked(true);
     //radio3->setChecked(true);
                                                                                        //Layout

     QHBoxLayout *TopLayout = new QHBoxLayout;
     TopLayout->addWidget(redRadiobutton);
     TopLayout->addWidget(blueRadiobutton);
     TopLayout->addWidget(greenRadiobutton);
     TopLayout->addStretch();

     QHBoxLayout *BottomLayout = new QHBoxLayout;
     BottomLayout->addWidget(yellowRadiobutton);
     BottomLayout->addWidget(whiteRadiobutton);
     BottomLayout->addStretch();

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(TopLayout);
     mainLayout->addLayout(BottomLayout);
     //mainLayout->addStretch();

     groupBox->setLayout(mainLayout);

     return groupBox;
 }

QRadioButton *Window::createcubeLEDRadiobutton()
{
    QRadioButton *cubeLEDRadiobutton = new QRadioButton("Cubes");
    cubeLEDRadiobutton->setChecked(true);

    return cubeLEDRadiobutton;
}

QRadioButton *Window::createpointLEDRadiobutton()
{
    QRadioButton *pointLEDRadiobutton = new QRadioButton("Points");

    return pointLEDRadiobutton;
}

QGroupBox *Window::createLEDAppearanceGroup()
 {
     QGroupBox *groupBox = new QGroupBox("LED Appearance");
                                                                                        //Layout

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(cubeLEDRadiobutton);
     mainLayout->addWidget(pointLEDRadiobutton);
    // mainLayout->addStretch();

     groupBox->setLayout(mainLayout);

     return groupBox;
 }

QRadioButton *Window::createcubeRadioButton()
{
    QRadioButton *radiobutton = new QRadioButton();

    radiobutton->setChecked(true);
    return radiobutton;
}

QRadioButton *Window::createsineRadioButton()
{
    QRadioButton *radiobutton = new QRadioButton();

    return radiobutton;
}

QRadioButton *Window::createfaceRadioButton()
{
    QRadioButton *radiobutton = new QRadioButton();

    return radiobutton;
}

QGroupBox *Window::createLEDShapeGroup()
 {
     QGroupBox *groupBox = new QGroupBox("LED Shape");
     //QRadioButton *cubeRadioButton = new QRadioButton();
     //QRadioButton *sineRadioButton = new QRadioButton("sine");
     QLabel *cubeLabel = new QLabel("Rectangular Prism/Cube");
     QLabel *sineLabel = new QLabel("Sine");
     QLabel *faceLabel = new QLabel("Face");


     //cubeRadioButton->setChecked(true);
                                                                                            //Layout

     QHBoxLayout *mainLayout = new QHBoxLayout;
     mainLayout->addWidget(cubeLabel);
     mainLayout->addWidget(cubeRadiobutton);
     mainLayout->addWidget(sineLabel);
     mainLayout->addWidget(sineRadiobutton);
     mainLayout->addWidget(faceLabel);
     mainLayout->addWidget(faceRadiobutton);
     mainLayout->addStretch();

     groupBox->setLayout(mainLayout);

     return groupBox;
 }
