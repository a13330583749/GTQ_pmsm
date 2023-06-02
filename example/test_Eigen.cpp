#include <iostream>
#include <fstream>
using namespace std;
#include <ctime>
#include <fcntl.h>
//eigen核心部分
#include <Eigen/Core>
//稠密矩阵的代数运算（逆、特征值等）
#include <Eigen/Dense>
using namespace Eigen;
#define MATRIX_SEZE 110

int main(int argc, char **argv)
{

    //练习求解方程
    //求解Matrix_NN * x = v_NN方程
    Matrix<double, MATRIX_SEZE, MATRIX_SEZE> matrix_NN 
        = MatrixXd::Random(MATRIX_SEZE,MATRIX_SEZE);     //MATRIX_SEZE在前面宏定义中
    matrix_NN = matrix_NN *matrix_NN.transpose();        //此处理可以保证矩阵是半正定的
    clock_t time_stt = clock();                           //用于计时

    time_stt = clock();
    std::ofstream outputFile("../data/cholesky.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }
    outputFile << matrix_NN << endl;
    outputFile.close();

    Eigen::LLT<MatrixXd> lltOfA;
    auto time_stt2 = clock();
    time_stt = clock();
    lltOfA.compute(matrix_NN); // Cholesky分解
    time_stt2 = clock();
    cout << "time of ldlt decomposition is "
       <<  (time_stt2- time_stt) / (double) CLOCKS_PER_SEC << "s" << endl;

    MatrixXd L = lltOfA.matrixL();
    std::ofstream outputFile_res("../data/cholesky_result.txt", std::ios::out | std::ios::binary);
    outputFile_res << L <<  std::endl;
    outputFile_res.close();


    // Eigen::LDLT<Eigen::Matrix<double, MATRIX_SEZE, MATRIX_SEZE>> y = matrix_NN.ldlt();
    // cout << "time of ldlt decomposition is "
    //    <<  (clock() - time_stt) / (double) CLOCKS_PER_SEC << "s" << endl;
    // std::ofstream outputFile_res("cholesky_result.txt", std::ios::out | std::ios::binary);
    // // Format the output using Eigen::IOFormat
    // Eigen::IOFormat format(Eigen::FullPrecision, Eigen::DontAlignCols, "\t", "\n");
    // // Write the formatted output to the file
    // outputFile_res << static_cast<Eigen::Matrix<double, MATRIX_SEZE, MATRIX_SEZE>>(y.matrixU()) <<  std::endl;
    // // outputFile_res << static_cast<Eigen::Matrix<double, MATRIX_SEZE, MATRIX_SEZE>>(y.matrixU()) <<  std::endl;
    // outputFile_res.close();
    return 0;
}