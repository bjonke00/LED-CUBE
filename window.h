#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class QGroupBox;
class QSlider;
class QSpinBox;
class QDoubleSpinBox;
class QRadioButton;
class MyGLWidget;
class QScrollArea;
class QPushButton;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

private:
    MyGLWidget *myglWidget;



    QGroupBox *createTransformsGroup();
    QGroupBox *createResolutionGroup();
    QGroupBox *createLEDColorGroup();
    QGroupBox *createLEDAppearanceGroup();                              //cubes or points
    QGroupBox *createLEDShapeGroup();                                   //shape:cube, sinewave, etc.

    QWidget *centralWidget;
    QScrollArea *myglWidgetArea;

    QSlider *createSlider();                                            //sliders
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *zoomSlider;

    QSpinBox *createSpinbox();                                          //spinboxes
    QSpinBox *CubeCountSpinbox;
    QSpinBox *yCubeCountSpinbox;
    QSpinBox *zCubeCountSpinbox;

    QDoubleSpinBox *LEDsizeDoubleSpinbox;

    QDoubleSpinBox *createDoubleSpinbox();                       //spacing
    QDoubleSpinBox *spacingDoubleSpinbox;

    //QRadioButton *createColorRadiobuttons();
    //QRadioButton *cubeColor();
    QRadioButton *createredRadiobutton();                               //color radiobuttons
    QRadioButton *creategreenRadiobutton();
    QRadioButton *createblueRadiobutton();
    QRadioButton *createyellowRadiobutton();
    QRadioButton *createwhiteRadiobutton();
    QRadioButton *redRadiobutton;
    QRadioButton *greenRadiobutton;
    QRadioButton *blueRadiobutton;
    QRadioButton *yellowRadiobutton;
    QRadioButton *whiteRadiobutton;

    QRadioButton *createcubeLEDRadiobutton();                           //radio buttons for appearance
    QRadioButton *createpointLEDRadiobutton();                          //cubes or points
    QRadioButton *cubeLEDRadiobutton;
    QRadioButton *pointLEDRadiobutton;

    QRadioButton *createcubeRadioButton();
    QRadioButton *createsineRadioButton();
    QRadioButton *createfaceRadioButton();
    QRadioButton *cubeRadiobutton;
    QRadioButton *sineRadiobutton;
    QRadioButton *faceRadiobutton;


};

#endif // WINDOW_H
