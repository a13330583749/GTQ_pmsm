#ifndef CURRENT_CONTROLLER_H
#define CURRENT_CONTROLLER_H

#define ONESTEPFCSMPC true
#include "PMSM.h"
namespace PanJL{
#ifdef ONESTEPFCSMPC
class FCSMPCer: public PMSM
{
private:
    struct PMSM_state_varibles predict_states;
    std::vector<double> predict_i(const double& ud, const double& uq);

public:
    std::vector<int> controller(const double& Id_ref, const double& Iq_ref, const double& theta_ele);
};

#endif
}
#endif