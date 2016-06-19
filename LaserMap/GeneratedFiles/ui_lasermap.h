/********************************************************************************
** Form generated from reading UI file 'lasermap.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LASERMAP_H
#define UI_LASERMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LaserMapClass
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionZoom;
    QAction *actionDrag;
    QAction *actionHeightColor;
    QAction *actionClassColor;
    QAction *action3D;
    QAction *actionRealColor;
    QAction *actionDistance;
    QAction *actionIntensityColor;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LaserMapClass)
    {
        if (LaserMapClass->objectName().isEmpty())
            LaserMapClass->setObjectName(QStringLiteral("LaserMapClass"));
        LaserMapClass->resize(630, 630);
        LaserMapClass->setMinimumSize(QSize(630, 630));
        actionOpen = new QAction(LaserMapClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/LaserMap/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionClose = new QAction(LaserMapClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/LaserMap/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon1);
        actionExit = new QAction(LaserMapClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionZoom = new QAction(LaserMapClass);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionZoom->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/LaserMap/zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom->setIcon(icon2);
        actionDrag = new QAction(LaserMapClass);
        actionDrag->setObjectName(QStringLiteral("actionDrag"));
        actionDrag->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/LaserMap/drag.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrag->setIcon(icon3);
        actionHeightColor = new QAction(LaserMapClass);
        actionHeightColor->setObjectName(QStringLiteral("actionHeightColor"));
        actionHeightColor->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/LaserMap/heightColor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHeightColor->setIcon(icon4);
        actionClassColor = new QAction(LaserMapClass);
        actionClassColor->setObjectName(QStringLiteral("actionClassColor"));
        actionClassColor->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/LaserMap/classColor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClassColor->setIcon(icon5);
        action3D = new QAction(LaserMapClass);
        action3D->setObjectName(QStringLiteral("action3D"));
        action3D->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/LaserMap/3D.png"), QSize(), QIcon::Normal, QIcon::Off);
        action3D->setIcon(icon6);
        actionRealColor = new QAction(LaserMapClass);
        actionRealColor->setObjectName(QStringLiteral("actionRealColor"));
        actionRealColor->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/LaserMap/realColor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRealColor->setIcon(icon7);
        actionDistance = new QAction(LaserMapClass);
        actionDistance->setObjectName(QStringLiteral("actionDistance"));
        actionDistance->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/LaserMap/distance.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDistance->setIcon(icon8);
        actionIntensityColor = new QAction(LaserMapClass);
        actionIntensityColor->setObjectName(QStringLiteral("actionIntensityColor"));
        actionIntensityColor->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/LaserMap/intensityColor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIntensityColor->setIcon(icon9);
        centralWidget = new QWidget(LaserMapClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        LaserMapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LaserMapClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 630, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        LaserMapClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LaserMapClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LaserMapClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LaserMapClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LaserMapClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionClose);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionZoom);
        mainToolBar->addAction(actionDrag);
        mainToolBar->addAction(actionDistance);
        mainToolBar->addAction(action3D);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionHeightColor);
        mainToolBar->addAction(actionRealColor);
        mainToolBar->addAction(actionClassColor);
        mainToolBar->addAction(actionIntensityColor);

        retranslateUi(LaserMapClass);

        QMetaObject::connectSlotsByName(LaserMapClass);
    } // setupUi

    void retranslateUi(QMainWindow *LaserMapClass)
    {
        LaserMapClass->setWindowTitle(QApplication::translate("LaserMapClass", "LaserMap", 0));
        actionOpen->setText(QApplication::translate("LaserMapClass", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("LaserMapClass", "Open", 0));
#endif // QT_NO_TOOLTIP
        actionClose->setText(QApplication::translate("LaserMapClass", "Close", 0));
        actionExit->setText(QApplication::translate("LaserMapClass", "Exit", 0));
        actionZoom->setText(QApplication::translate("LaserMapClass", "Zoom", 0));
        actionDrag->setText(QApplication::translate("LaserMapClass", "Drag", 0));
        actionHeightColor->setText(QApplication::translate("LaserMapClass", "HeightColor", 0));
        actionClassColor->setText(QApplication::translate("LaserMapClass", "ClassColor", 0));
        action3D->setText(QApplication::translate("LaserMapClass", "3D", 0));
        actionRealColor->setText(QApplication::translate("LaserMapClass", "RealColor", 0));
        actionDistance->setText(QApplication::translate("LaserMapClass", "Distance", 0));
        actionIntensityColor->setText(QApplication::translate("LaserMapClass", "IntensityColor", 0));
        menuFile->setTitle(QApplication::translate("LaserMapClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class LaserMapClass: public Ui_LaserMapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LASERMAP_H
