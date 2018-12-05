#ifndef DATAMATRIX_H
#define DATAMATRIX_H

/**********************************
 * Include
 *********************************/
/*******************
 * data matrix
 ******************/
#include <dmtx.h>
/*******************
 * system
 ******************/
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
/*******************
 * opencv
 ******************/
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
/*******************
 * GTK+
 ******************/

class DataMatrix
{
public:
    DataMatrix();
    // DM ECC200 数据编码
    int data_matrix_encoder(const std::__cxx11::string &str, const std::__cxx11::string &save_address);
    // DM ECC200 批量生成
    int pgv100_dm_creator(const int &tag_numbers , const int &rows  , const int &cols , const std::__cxx11::string &save_address);

    std::vector<cv::Mat> image_vector;
};

#endif // DATAMATRIX_H
