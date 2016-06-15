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
        actionClose = new QAction(LaserMapClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionExit = new QAction(LaserMapClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionZoom = new QAction(LaserMapClass);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionZoom->setCheckable(true);
        actionDrag = new QAction(LaserMapClass);
        actionDrag->setObjectName(QStringLiteral("actionDrag"));
        actionDrag->setCheckable(true);
        actionHeightColor = new QAction(LaserMapClass);
        actionHeightColor->setObjectName(QStringLiteral("actionHeightColor"));
        actionHeightColor->setCheckable(true);
        actionClassColor = new QAction(LaserMapClass);
        actionClassColor->setObjectName(QStringLiteral("actionClassColor"));
        actionClassColor->setCheckable(true);
        action3D = new QAction(LaserMapClass);
        action3D->setObjectName(QStringLiteral("action3D"));
        action3D->setCheckable(true);
        actionRealColor = new QAction(LaserMapClass);
        actionRealColor->setObjectName(QStringLiteral("actionRealColor"));
        actionRealColor->setCheckable(true);
        actionDistance = new QAction(LaserMapClass);
        actionDistance->setObjectName(QStringLiteral("actionDistance"));
        actionDistance->setCheckable(true);
        actionIntensityColor = new QAction(LaserMapClass);
        actionIntensityColor->setObjectName(QStringLiteral("actionIntensityColor"));
        actionIntensityColor->setCheckable(true);
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
