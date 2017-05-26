#ifndef lcmbase_h
#define lcmbase_h

#include <iostream>
#include <lcm/lcm-cpp.hpp>

class LcmBase{
public:
    static  LcmBase * get_instance();
    ~LcmBase();
    lcm::LCM get_lcm();
private:
    LcmBase();
    lcm::LCM lcm;
    static LcmBase* m_pInstance;
};

#endif
