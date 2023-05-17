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


public:
    std::vector<int> controller(const double& Id_ref, const double& Iq_ref, const double& theta_ele);
};

#endif
}
#endif