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
#include "OpenGLplot.h"

QT_BEGIN_NAMESPACE

class Ui_LaserMapClass
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    OpenGLplot *openGLplot;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LaserMapClass)
    {
        if (LaserMapClass->objectName().isEmpty())
            LaserMapClass->setObjectName(QStringLiteral("LaserMapClass"));
        LaserMapClass->resize(168, 221);
        actionOpen = new QAction(LaserMapClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(LaserMapClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionExit = new QAction(LaserMapClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(LaserMapClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLplot = new OpenGLplot(centralWidget);
        openGLplot->setObjectName(QStringLiteral("openGLplot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLplot->sizePolicy().hasHeightForWidth());
        openGLplot->setSizePolicy(sizePolicy);
        openGLplot->setMinimumSize(QSize(150, 150));

        gridLayout->addWidget(openGLplot, 0, 0, 1, 1);

        LaserMapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LaserMapClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 168, 21));
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

        retranslateUi(LaserMapClass);

        QMetaObject::connectSlotsByName(LaserMapClass);
    } // setupUi

    void retranslateUi(QMainWindow *LaserMapClass)
    {
        LaserMapClass->setWindowTitle(QApplication::translate("LaserMapClass", "LaserMap", 0));
        actionOpen->setText(QApplication::translate("LaserMapClass", "Open", 0));
        actionClose->setText(QApplication::translate("LaserMapClass", "Close", 0));
        actionExit->setText(QApplication::translate("LaserMapClass", "Exit", 0));
        menuFile->setTitle(QApplication::translate("LaserMapClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class LaserMapClass: public Ui_LaserMapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LASERMAP_H
