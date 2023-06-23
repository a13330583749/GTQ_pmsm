// 本测试用例用于计算：sphere decoding algorithm所需要的矩阵
// eigen核心部分
#include <iostream>
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆、特征值等）
#include <Eigen/Dense>
#include <functional>
#include "../PMSM_sim.h"
const static int predictive_N = 5;
const static int rank_abc     = 3;
// const static int rankA = 2;

// 打算这个类作为SDA的电流控制器的友元类提高计算上的帮助
// 这个类主要采用Eigen作为运算单元，而不是使用一般的计算方式
class myClass
{
public:
    // 这种就直接暴露出来就好了
    double a; // a := state_varibles.wr
    double c; // b := state_varibles.theta_ele
    double Id;
    double Iq;
    const double Id_ref = 0;
    double Iq_ref;
    Eigen::Matrix<int, rank_abc * predictive_N, 1> Uopts;
    // std::vector<int> Uopts;
    // 考虑到FCSMPCer使用的是vector容器作为输入，因此在此处vector将这个类最终计算的结果输出，
    // 同时保留该状态下的输入，以便下一个时刻的使用
    std::vector<int> virtual_outpus;
    

    // 保留的接口
    // 更改为：
    // mutual double Id_ref = 0;
    // const void inline set_Id_ref(const double& Id){Id_ref = Id;}
    std::function<Eigen::Vector<double, rankA * predictive_N>()> Vector_Iref;
    std::function<Eigen::Vector<double, rankA * predictive_N>()> Vector_Idq;
    std::function<Eigen::Vector<double, rankA * predictive_N>()> Vector_D;
    std::function<Eigen::Vector<double, rank_abc>()> Vector_v_abc;

    const Eigen::Matrix<double, rankA, rankA> B = 
     Eigen::Matrix<double, rankA, rankA>{{PanJL::Ts/Ld_, 0}, {0, PanJL::Ts/Lq_}};

    // Clarke变换所需要的矩阵
    const Eigen::Matrix<double, 2, 3> Clarke_Matrix
     = 2 / 3.0 * Eigen::Matrix<double, 2, 3>{{1, -0.5, -0.5}, {0, std::sqrt(3)/2.0, -std::sqrt(3)/2.0}};
    
    // 端电压变换为相电压：
    const Eigen::Matrix<double, 3, 3> T_ground2phase 
     =  Eigen::Matrix<double, 3, 3>{{2, -1, -1}, {-1, 2, -1}, {-1, -1, 2}} / 3.0;

    // 想了想还是得返回矩阵，进行坐标变换还是得使用原来的那些办法
    // 见readme中的方法二
    // 因为park矩阵需要实时获得
    // 而clack矩阵是不会变的

protected:
    // MPCC中用于表示位移的矩阵
    // 有一个问题就是const矩阵的初始怎么设置
    // 因为使用的是可以变预测时域的方式，所以S和E的大小其实是不一样的
    // 或者说因为S和E在编译期不能确定大小，所以不能使用const的属性
    // 因此为了简化编程，在这里不加入const进行修饰，虽然在初始化之后这个矩阵就不会在变化
    Eigen::Matrix<double, rank_abc * predictive_N, rank_abc * predictive_N> S; 
    Eigen::Matrix<double, rank_abc * predictive_N, rank_abc > E;
public: 
    // Park变换所需要的矩阵
    std::function<Eigen::Matrix<double, 2, 2>()> Park_Matrix;
    
    std::function<Eigen::Matrix<double, rankA, rankA>()> A;
    // Γ
    std::function<Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>()> get_Gamma;
    // Φ
    std::function<Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>()> get_Phi;
    // γ  3代表abc三相电的输入
    std::function<Eigen::Matrix<double, rankA * predictive_N, rank_abc * predictive_N>()> get_gamma;
    //Θ： 一次矩阵
    std::function<Eigen::Matrix<double, rank_abc*predictive_N, 1>()> get_Theta;
    //R： 二次矩阵
    std::function<Eigen::Matrix<double, rank_abc*predictive_N, rank_abc*predictive_N>()> get_R;

    myClass() = default;
    myClass(double A_, double C) : a(A_), c(C)
    {
        virtual_outpus = {0,0,0};
        virtual_outpus.resize(3);
        Uopts.setZero();
        // Uopts = std::vector<int>{9, 0};
        // 获得I_ref向量：
        this->Vector_Iref = [this]() -> Eigen::Vector<double, rankA * predictive_N>
        {
            return Eigen::Vector2d(this->Id_ref, this->Iq_ref).replicate(predictive_N, 1);
        };

        // 获得Idq向量：
        this->Vector_Idq = [this]() -> Eigen::Vector<double, rankA * predictive_N>
        {
            return Eigen::Vector2d(this->Id, this->Iq).replicate(predictive_N, 1);
        };

        // 获得D向量：
        this->Vector_D = [this]() -> Eigen::Vector<double, rankA * predictive_N>
        {
            // 这里的常数处理要注意，因为转速和磁链都是不一定相同的，移植的时候要注意正确性
            return Eigen::Vector2d(0, -a * PanJL::Ts * F_).replicate(predictive_N, 1);
        };

        // 获得Vector_v_abc向量：
        this->Vector_v_abc = [this]() -> Eigen::Vector<double, rank_abc>
        {
            // 这里的常数处理要注意，因为转速和磁链都是不一定相同的，移植的时候要注意正确性
            return Eigen::Vector3d(static_cast<double>(virtual_outpus[0]), static_cast<double>(virtual_outpus[1]),
                    static_cast<double>(virtual_outpus[2]));
        };


        // 注意这里的B矩阵是对于SPMSM的，对于有凸性的电机来说。这里的B矩阵需要变换
        this->Park_Matrix = [this]() -> Eigen::Matrix<double, 2, 2>
        {
            Eigen::Matrix<double, 2, 2> T;
            T << std::cos(this->c), std::sin(this->c), -std::sin(this->c), std::cos(this->c);
            return T;
        };

        this->A = [this]() -> Eigen::Matrix<double, 2, 2>
        {
            double A11 = 1 - Rs_ * PanJL::Ts / Ld_;
            double A12 = Pn_ * a * PanJL::Ts;
            double A21 = -a * Pn_ * PanJL::Ts;
            double A22 = 1 - Rs_ * PanJL::Ts / Lq_;
            Eigen::Matrix<double, rankA, rankA> result;
            result << A11, A12, A21, A22;
            return result;
        };
        // 得到：Γ
        this->get_Gamma = [this]() -> Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>
        {
            Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> result;
            result.setZero();
            for (int i = 0; i < predictive_N; i++)
            {
                result.block(i * rankA, i * rankA, rankA, rankA) = this->MatrixPower(this->A(), i);
            }
            return result;
        };
        // 得到Φ：
        this->get_Phi = [this]() -> Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>
        {
            Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> rhi;
            rhi.setZero();
            for (int i = 0; i < predictive_N; i++){ // 行
                for (int j = 0; j <= i; j++){ // 列
                    rhi.block(i * rankA, j * rankA, rankA, rankA) =
                        Eigen::Matrix<double, rankA, rankA>::Identity() * this->MatrixPower(this->A(), i - j);
                }
            }
            return rhi;
        };
        // 得到γ：
        this->get_gamma = [this]() -> Eigen::Matrix<double, rankA * predictive_N, rank_abc * predictive_N>
        {
            Eigen::Matrix<double, rankA * predictive_N, rank_abc * predictive_N> gamma;
            gamma.setZero();
            for (int i = 0; i < predictive_N; i++){ // 行
                for (int j = 0; j <= i; j++){ // 列
                    gamma.block(i * rankA, j * rank_abc, rankA, rank_abc) =
                        PanJL::Vdc / 2.0 *
                        B * this->MatrixPower(this->A(), i - j - 1) * (this->Park_Matrix() * this->Clarke_Matrix )  * T_ground2phase;
                }
            }
            return gamma;
        };
        S.setZero();
        E.setZero();
        // 初始化S和E矩阵：
        for(int i_=0; i_<predictive_N; i_++){
            if(i_ == 0){
                S.block(i_, i_, rank_abc, rank_abc) = Eigen::Matrix<double, rank_abc, rank_abc>::Identity();
                E.block(i_, i_, rank_abc, rank_abc) = Eigen::Matrix<double, rank_abc, rank_abc>::Identity();
            }else{
                S.block(i_ * rank_abc, i_ * rank_abc, rank_abc, rank_abc) = Eigen::Matrix<double, rank_abc, rank_abc>::Identity();
                S.block(i_ * rank_abc, (i_-1) * rank_abc, rank_abc, rank_abc) = -1 * Eigen::Matrix<double, rank_abc, rank_abc>::Identity();
            }
        }
        // R和Θ矩阵需要通过S和E来获取，所以放在后面来写
        // std::function<Eigen::Matrix<double, rank_abc*predictive_N, rank_abc*predictive_N>()> get_R;
        // 二次项系数：R
        this -> get_R = [this]() -> Eigen::Matrix<double, rank_abc*predictive_N, rank_abc*predictive_N>
        {
            // 这里还没有引入权重矩阵，所以就先放在这里测试，之后再正式的写友元类的时候再考虑加入
            Eigen::Matrix<double, rank_abc*predictive_N, rank_abc*predictive_N> result = (this->get_gamma()).transpose() * this->get_gamma() + (this->S).transpose() * (this->S);
            return result;
        };
        // std::function<Eigen::Matrix<double, rank_abc*predictive_N, rank_abc*predictive_N>()> get_Theta;
        // 一次项系数：Θ
        this -> get_Theta = [this]() -> Eigen::Matrix<double, rank_abc*predictive_N, 1>
        {
            Eigen::Matrix<double, rank_abc*predictive_N, 1> result;
            // 这里的P权重矩阵也还是没有放进入一起计算！！！Γ
            result = (((this -> get_Gamma() * (this->Vector_Idq())) + (this->get_Phi() * (this->Vector_D())) - this->Vector_Iref()).transpose()
                     * (this->get_gamma())).transpose() - ((-this->E * this->Vector_v_abc()).transpose() * this->S).transpose();
            return result;
        };


    }

    Eigen::Matrix<double, rankA, rankA> MatrixPower(const Eigen::Matrix<double, rankA, rankA> &matrix, const int &n)
    {
        if(n <= 0)
            return Eigen::Matrix<double, rankA, rankA>::Identity();
        Eigen::Matrix<double, rankA, rankA> result = Eigen::Matrix<double, rankA, rankA>::Identity();
        for (int i = 0; i < n; ++i)
            result *= matrix;
        return result;
    }

    // 递归SDA算法
    // 应该把ρ（rho）设置为无限大 ：
    // double rho = std::numeric_limits<double>::max(); // Initialize rho with a large value
    // Eigen::VectorXd Uopt(UoptSize);
    // Uopt.setZero(); // Initialize Uopt with zeros
    
    void MSPHDEC_Recursion(const Eigen::Matrix<double, rank_abc * predictive_N, 1>& U_hat_unc, 
            const Eigen::Matrix<double, rank_abc * predictive_N, rank_abc * predictive_N>& H,
             int i, double d2, double& rho, Eigen::Matrix<int, rank_abc * predictive_N, 1> &Uopts,
             Eigen::Matrix<int, rank_abc * predictive_N, 1> U)
    {
        // Base case: i reaches the maximum value
        if (i >= rank_abc * predictive_N) {
            Uopts = U;
            std::cout << Uopts.transpose() << std::endl;
            rho = d2;
            return;
        }
    // Iterate over the candidate input values
        for (int u = -1; u <= 1; u++) {
            U(i) = u;
            auto scalar_product = (H.row(i).head(i).cast<double>() * U.segment(0, i).cast<double>()).sum();
            double d2_new = (U_hat_unc(i) - scalar_product) * (U_hat_unc(i) - scalar_product) + d2;
            // double d2_new = (U_hat_unc(i) - (H.row(i).head(i) * U.segment(0, i).transpose())) + d2;
            if (d2_new < rho) {
                int previousUi = U(i);
                MSPHDEC_Recursion(U_hat_unc, H, i + 1, d2_new, rho, Uopts, U);
                // std::cout << U.transpose() << std::endl;
                U(i) = previousUi;
            }
        }        
    }
    

//    std::tuple<std::vector<int>, double> MSPHDEC_Recursion(const Eigen::Matrix<double, rank_abc * predictive_N, 1>& U_hat_unc, 
//             const Eigen::Matrix<double, rank_abc * predictive_N, rank_abc * predictive_N>& H, int i, double d2,
//             double rho, std::vector<int> U, std::vector<int> Uopt)
//     {
//         for(int j=-1; j<=1; j++){
//             U.push_back(j);
//             double d2_new = (U_hat_unc.segment(0, i).transpose() * H.block(i, 0, 1, i).transpose()).norm() + d2;
//             if (d2_new < rho){
//                 if(i < predictive_N* rank_abc)
//                     std::tie(Uopt, rho) = MSPHDEC_Recursion(U_hat_unc, H, i+1, d2_new, rho, U, Uopt);
//                 else{
//                     Uopt = U;
//                     rho = d2_new;
//                 }
//             }
//         }
//         return std::make_tuple(Uopt, rho);
//     }

    // 实现完成的SDA和矩阵变换接口的实现，需要将虚拟输入送出去
    // 按理来说这里的传入参数应该是系统的参数更新情况
    // 也是等到最后正式写入友元类的时候在做完善
    std::vector<int> updata()
    {
        double rho = std::numeric_limits<double>::max();
        Eigen::Matrix<double, rank_abc*predictive_N, 1> U_hat_unc = -1 * this->get_R().inverse() * this->get_Theta();
        Eigen::LLT<Eigen::Matrix<double, rank_abc*predictive_N, rank_abc*predictive_N>> llt;
        llt.compute(this->get_R());
        Eigen::Matrix<double, rank_abc*predictive_N, rank_abc*predictive_N> H = llt.matrixL();
        Eigen::Matrix<int, rank_abc*predictive_N, 1> U;
        U.setZero();
        // std::vector<int> U;
        // U.resize(0);
        // Uopts:保留上一次优化的最优值
        MSPHDEC_Recursion(U_hat_unc, H, 0, 0.0, rho, Uopts, U);
        
        std::vector<int> result;
        result.resize(3);
        result[0] = Uopts[0];
        result[1] = Uopts[1];
        result[2] = Uopts[2];
        std::cout << result[0] << "  " << result[1] << "  " << result[2]<< std::endl;
        // std::cout <<U_hat_unc.transpose() << std::endl;
        // Uopts.segment(0, rank_abc*(predictive_N - 1)) = Uopts.segment(rank_abc, rank_abc*(predictive_N - 1));
        // Uopts.segment(rank_abc*(predictive_N - 1), rank_abc) = Uopts.segment(rank_abc*(predictive_N - 2), rank_abc);
        return result;
    }
};

void test1()
{
    myClass obj(2.0, 1.2);
    std::cout << obj.A() << std::endl;
    std::cout << obj.A() * obj.A() << std::endl;
    std::cout << "--------------------" << std::endl;
}

// 用于测试矩阵的连乘
void test2()
{
    myClass obj(2.0, 1.2);
    std::cout << obj.MatrixPower(obj.A(), 2) << std::endl;
    std::cout << "--------------------" << std::endl;
}

void test3()
{
    myClass x(2.0, 1.2);
    Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> rhi;
    rhi.setZero();
    for (int i = 0; i < predictive_N; i++)
    { // 行
        for (int j = 0; j <= i; j++)
        { // 列
            rhi.block(i * rankA, j * rankA, rankA, rankA) =
                Eigen::Matrix<double, rankA, rankA>::Identity() * x.MatrixPower(x.A(), i - j);
        }
    }
    std::cout << rhi << std::endl;
    std::cout << "--------------------" << std::endl;
}

// test4说明算法的矩阵支持已经完成，现在还需要的就是SDA迭代本身计算的过程
void test4()
{
    myClass x(2.0, 1.2);
    // std::cout << x.Park_Matrix() << std::endl;
    // std::cout << "*********************" << std::endl;
    // std::cout << x.get_Gamma() << std::endl;
    // std::cout << "*********************" << std::endl;
    // std::cout << x.get_Phi() << std::endl;
    // std::cout << "*********************" << std::endl;
    // std::cout << x.get_gamma() << std::endl;
    // std::cout << "*********************" << std::endl;
    x.a = 1.0;
    x.c = 3.4;
    x.Id = 0.1;
    x.Iq = 4;
    x.Iq_ref = 5;
    std::cout << x.get_gamma() << std::endl;
    std::cout << "*********************" << std::endl;
    std::cout << "二次型矩阵：" << std::endl;
    std::cout << x.get_R() << std::endl;
    std::cout << "*********************" << std::endl;
    std::cout << "一次型矩阵：" << std::endl;
    std::cout << x.get_Theta() << std::endl;
    std::cout << "*********************" << std::endl;
    std::cout << "无约束的最优解为：" << std::endl; 
    std::cout << -1 * x.get_R().inverse() * x.get_Theta() << std::endl;
}

void test5()
{
    myClass x(2.0, 1.2);
    x.a = 1.0;
    x.c = 3.4;
    x.Id = 0.1;
    x.Iq = 4;
    x.Iq_ref = 5;
    auto y = x.updata();
    for (double j=2; j< 10; j=j+0.1){
        x.a = 1.0 * j;
        x.c = -0.4 * j;
        x.Id = 0;
        x.Iq = j;
        x.Iq_ref = 7;
        auto y = x.updata();
    }
}

int main(int argc, char **argv)
{
    test5();
    return 0;
}