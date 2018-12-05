#include "datamatrix.h"

DataMatrix::DataMatrix()
{

}

int DataMatrix::data_matrix_encoder(const std::string &str , const std::string &save_address)
{
    DmtxEncode* enc = dmtxEncodeCreate();
    assert(enc != NULL);//如果它的条件返回错误，则终止程序执行
    int ret = dmtxEncodeDataMatrix(enc , strlen(str.c_str()) , (unsigned char*)str.c_str());
    assert(ret == 1);

    int width = dmtxImageGetProp(enc->image , DmtxPropWidth);
    int height = dmtxImageGetProp(enc->image , DmtxPropHeight);
    int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);
    printf("image width: %d, image height: %d, channels: %d\n", width, height, bytesPerPixel);
    assert(bytesPerPixel == 1 || bytesPerPixel == 3 || bytesPerPixel == 4);

    cv::Mat mat;
    if (bytesPerPixel == 1)
        mat = cv::Mat(height, width, CV_8UC1);
    else if (bytesPerPixel == 3)
        mat = cv::Mat(height, width, CV_8UC3);
    else
        mat = cv::Mat(height, width, CV_8UC4);

    mat.data = enc->image->pxl;
    std::string image_name = save_address + str + ".jpg";
    cv::imwrite(image_name , mat);
    dmtxEncodeDestroy(&enc);
    return 0;
}

// "3600000005" 三行六列 tag编号为5, rows and cols是一张标签上的二维码矩阵的行和列
int DataMatrix::pgv100_dm_creator(const int &tag_numbers, const int &rows , const int &cols, const std::__cxx11::string &save_address)
{
    int width , height , bytesPerPixel;
    std::string context_str;
    int tag;
    if(tag_numbers < 1 || rows != cols)
    {
        printf("The params error , tag_numbers : %i , rows: %i , cols: %i \r\n",tag_numbers , rows , cols);
        return 0;
    }
    cv::namedWindow("s");
    for(int i = 0 ; i < tag_numbers ; i++)
    {
        image_vector.clear();
        tag = i;

        for(int j = 0 ; j < cols ; j ++)
        {
            for(int k = 0 ; k < rows ; k++)
            {
                uint32_t x = 3 + j;
                uint32_t left = (3 + k) * 100000000 + i;
                std::stringstream ss;
                ss << x << left;
                context_str = ss.str();
                std::cout << context_str << " " << i << std::endl;
                DmtxEncode* enc = dmtxEncodeCreate();
                assert(enc != NULL);//如果它的条件返回错误，则终止程序执行
                int ret = dmtxEncodeDataMatrix(enc , strlen(context_str.c_str()) , (unsigned char*)context_str.c_str());
                assert(ret == 1);

                width = dmtxImageGetProp(enc->image , DmtxPropWidth);
                height = dmtxImageGetProp(enc->image , DmtxPropHeight);
                bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);
                assert(width == height);
                printf("image width: %d, image height: %d, channels: %d\n", width, height, bytesPerPixel);
                assert(bytesPerPixel == 1 || bytesPerPixel == 3 || bytesPerPixel == 4);

                cv::Mat mat;
                if (bytesPerPixel == 1)
                    mat = cv::Mat(height, width, CV_8UC1);
                else if (bytesPerPixel == 3)
                    mat = cv::Mat(height, width, CV_8UC3);
                else
                    mat = cv::Mat(height, width, CV_8UC4);

                mat.data = enc->image->pxl;
                // 转化成灰度图
                cv::Mat grayImage = cv::Mat(height, width, CV_8UC1);
                cv::cvtColor(mat , grayImage , CV_RGB2GRAY);
                image_vector.push_back(grayImage);

//                std::string image_name = save_address + context_str + ".jpg";
//                cv::imwrite(image_name , grayImage);

//                cv::imshow("s" , grayImage);
//                cv::waitKey(100);
                dmtxEncodeDestroy(&enc);
            }
        }
        // 将多张图片合并成一张
        cv::Mat matt = cv::Mat(height * rows, width * cols, CV_8UC1);
        int dimension = width;
        // 第一列
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 3 + j,i) = image_vector[0].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 2 + j,i) = image_vector[1].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 1 + j,i) = image_vector[2].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 0 + j,i) = image_vector[3].at<uchar>(j,i);
            }
        }
        // 第二列
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 3 + j,dimension + i) = image_vector[4].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 2 + j,dimension + i) = image_vector[5].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 1 + j,dimension + i) = image_vector[6].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>(j,dimension + i) = image_vector[7].at<uchar>(j,i);
            }
        }
        // 第三列
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 3 + j,dimension * 2 + i) = image_vector[8].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 2 + j,dimension * 2 + i) = image_vector[9].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 1 + j,dimension * 2 + i) = image_vector[10].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>(j,dimension * 2 + i) = image_vector[11].at<uchar>(j,i);
            }
        }
        // 第四列
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 3 + j,dimension * 3 + i) = image_vector[12].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 2 + j,dimension * 3 + i) = image_vector[13].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>( dimension * 1 + j,dimension * 3 + i) = image_vector[14].at<uchar>(j,i);
            }
        }
        for(int i = 0 ; i < dimension ; i++)
        {
            for(int j = 0 ; j < dimension ; j++)
            {
                matt.at<uchar>(j,dimension * 3 + i) = image_vector[15].at<uchar>(j,i);
            }
        }
        std::stringstream ss;
        ss << tag;
        std::string tag_str = ss.str();
        std::string image_name = save_address + tag_str + ".jpg";
        std::cout << "************|||||************" << std::endl;
        std::cout << "tag: " << image_name << std::endl;
        std::cout << "************|||||************" << std::endl;
        cv::imwrite(image_name , matt);
    }
    return 0;
}
