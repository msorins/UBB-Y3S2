//
// Created by Sorin Sebastian Mircea on 04/03/2019.
//

#ifndef WATERSHEDPROJECT_UTILS_H
#define WATERSHEDPROJECT_UTILS_H

#include <iostream>
#include <vector>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QtGui/QPixmap>
#include "../Filters/NegativeOfImage.h"
#include "../Filters/WaterShedFilter.h"
#include "../Filters/WindowOperation.h"
#include "../Filters/BitExtraction.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

using namespace cv;
using namespace std;

class Utils {
public:
    static QPixmap fromMat(Mat img) {
        Mat imgNew;
        if(img.channels() == 3) {
            cvtColor(img, imgNew, CV_BGR2RGB);
        } else {
            cvtColor(img, imgNew, CV_GRAY2RGB);
        }
        return QPixmap::fromImage(QImage(imgNew.data, imgNew.cols, imgNew.rows, imgNew.step, QImage::Format_RGB888));
    }

    static vector<FilterInterface*> getFilters() {
        vector<FilterInterface*> filters;
        FilterInterface *f0 = new WaterShedFilter();
        FilterInterface *f1 = new ColorFilterL1();
        FilterInterface *f2 = new NegativeOfImage();
        FilterInterface *f3 = new WindowOperation();
        FilterInterface *f4 = new BitExtraction();
        filters.push_back(f1);
        filters.push_back(f0);
        filters.push_back(f2);
        filters.push_back(f3);
        filters.push_back(f4);
        return filters;
    }

    static vector<string> getImages() {
        string path("../images");
        return get_file_list(path);
    }

private:
    static vector<string> get_file_list(const std::string& path)
    {
        vector<string> fileList;
        if (!path.empty())
        {
            namespace fs = boost::filesystem;

            fs::path apk_path(path);
            fs::recursive_directory_iterator end;

            for (fs::recursive_directory_iterator i(apk_path); i != end; ++i)
            {
                const fs::path cp = (*i);
                fileList.push_back(cp.string());
            }
        }
        return fileList;
    }
};

#endif //WATERSHEDPROJECT_UTILS_H
