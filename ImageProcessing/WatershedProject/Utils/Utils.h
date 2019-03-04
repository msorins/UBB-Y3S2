//
// Created by Sorin Sebastian Mircea on 04/03/2019.
//

#ifndef WATERSHEDPROJECT_UTILS_H
#define WATERSHEDPROJECT_UTILS_H

#endif //WATERSHEDPROJECT_UTILS_H

#include <iostream>
#include <vector>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QtGui/QPixmap>
#include "../Filters/ColorFilterL1V2.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

using namespace cv;
using namespace std;

class Utils {
public:
    static QPixmap fromMat(Mat img) {
        cvtColor(img, img, CV_BGR2RGB);
        return QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888));
    }

    static vector<FilterInterface*> getFilters() {
        vector<FilterInterface*> filters;
        FilterInterface *f1 = new ColorFilterL1();
        FilterInterface *f2 = new ColorFilterL1V2();
        filters.push_back(f1);
        filters.push_back(f2);
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