/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *_line;
    QLabel *firstImageLabel;
    QLabel *secondImageLabel;
    QPushButton *processImagePushButton;
    QComboBox *filterComboBox;
    QComboBox *imageComboBox;
    QMenuBar *menuBar;
    QMenu *menuImage_Processing_Pipeline;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1476, 830);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        _line = new QFrame(centralWidget);
        _line->setObjectName(QString::fromUtf8("_line"));
        _line->setGeometry(QRect(730, 20, 20, 671));
        _line->setFrameShape(QFrame::VLine);
        _line->setFrameShadow(QFrame::Sunken);
        firstImageLabel = new QLabel(centralWidget);
        firstImageLabel->setObjectName(QString::fromUtf8("firstImageLabel"));
        firstImageLabel->setGeometry(QRect(10, 10, 701, 641));
        secondImageLabel = new QLabel(centralWidget);
        secondImageLabel->setObjectName(QString::fromUtf8("secondImageLabel"));
        secondImageLabel->setGeometry(QRect(760, 10, 701, 651));
        processImagePushButton = new QPushButton(centralWidget);
        processImagePushButton->setObjectName(QString::fromUtf8("processImagePushButton"));
        processImagePushButton->setGeometry(QRect(0, 730, 1471, 41));
        filterComboBox = new QComboBox(centralWidget);
        filterComboBox->setObjectName(QString::fromUtf8("filterComboBox"));
        filterComboBox->setGeometry(QRect(750, 690, 711, 31));
        imageComboBox = new QComboBox(centralWidget);
        imageComboBox->setObjectName(QString::fromUtf8("imageComboBox"));
        imageComboBox->setGeometry(QRect(20, 690, 711, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1476, 22));
        menuImage_Processing_Pipeline = new QMenu(menuBar);
        menuImage_Processing_Pipeline->setObjectName(QString::fromUtf8("menuImage_Processing_Pipeline"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuImage_Processing_Pipeline->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        firstImageLabel->setText(QApplication::translate("MainWindow", "FirstImageLabel", nullptr));
        secondImageLabel->setText(QApplication::translate("MainWindow", "secondImageLabel", nullptr));
        processImagePushButton->setText(QApplication::translate("MainWindow", "Process Image", nullptr));
        menuImage_Processing_Pipeline->setTitle(QApplication::translate("MainWindow", "Image Processing Pipeline", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
