// 这个类用于继承辨识器具体算法，将测试程序的接口和实际辨识算法结合
// 属于是胶水类
#ifndef Identifier_h
#define Identifier_h
#include <./IRLS.h>
namespace PanJL{
class Identifier: public IRLS_parameter_identify
{

};
}


#endif