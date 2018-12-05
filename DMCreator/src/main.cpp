#include <iostream>
#include "datamatrix.h"

using namespace std;

int main(int argc, char *argv[])
{
    DataMatrix datamatrix;
    // 生成一个二维码
//    int ret = datamatrix.data_matrix_encoder("3600000005" , "/home/youibot/DMImage/");
    // 批量生成二维码，适配倍加副PGV100 , 第2,3参数只能是4
    int re = datamatrix.pgv100_dm_creator(20,4,4,"/home/youibot/DMImage/");
    cout << "Hello World!" << endl;
    return 0;
}
