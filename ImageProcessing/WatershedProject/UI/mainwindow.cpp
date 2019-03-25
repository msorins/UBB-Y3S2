#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "../Filters/ColorFilterL1.h"
#include "../Utils/Utils.h"

using namespace cv;
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setupSignalsAndSlots();


    // Populate filters combo box
    QStringList filtersList;
    for(auto elem: Utils::getFilters()) {
        filtersList.push_back( QString::fromStdString(elem->getName()) );
    }
    this->ui->filterComboBox->addItems(filtersList);

    // Populate images combo box
    QStringList imagesList;
    for(auto image: Utils::getImages()) {
        imagesList.push_back( QString::fromStdString(image) );
    }
    this->ui->imageComboBox->addItems(imagesList);

    // Process initial image & filter
    processImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processImage() {
    // Get data from qt
    string imagePath = this->ui->imageComboBox->currentText().toStdString();
    string filterName    =  this->ui->filterComboBox->currentText().toStdString();

    // Read Image
    Mat img =  imread(imagePath,     CV_LOAD_IMAGE_COLOR);
    cout << "Processing image: " << imagePath << " with function: " <<  filterName << "\n";

    // Show Initial image
    QPixmap pixImg = Utils::fromMat(img);
    pixImg = pixImg.scaled(this->ui->firstImageLabel->width(), this->ui->firstImageLabel->height(), Qt::KeepAspectRatio);
    this->ui->firstImageLabel->setPixmap(pixImg);
    this->ui->firstImageLabel->show();

    // Process Image
    Mat resultImage;
    for(auto filter: Utils::getFilters()) {
        if(filter->getName() == filterName) {
            resultImage = filter->processImage(img);
        }
    }

    // Show Result Image
    QPixmap pixResultImg = Utils::fromMat(resultImage);
    pixResultImg = pixResultImg.scaled(this->ui->secondImageLabel->width(), this->ui->secondImageLabel->height(), Qt::KeepAspectRatio);
    this->ui->secondImageLabel->setPixmap(pixResultImg);
    this->ui->secondImageLabel->show();

    // Save Result Image to disk
    string outImageName = "out.jpg";
    imwrite(outImageName, resultImage);
}

void MainWindow::setupSignalsAndSlots() {
    QObject::connect(this->ui->imageComboBox, SIGNAL(activated(int)), this, SLOT(processImage()));
    QObject::connect(this->ui->filterComboBox, SIGNAL(activated(int)), this, SLOT(processImage()));
}
