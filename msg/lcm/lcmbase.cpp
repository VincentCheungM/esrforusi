#include "lcmbase.h"

LcmBase* LcmBase::m_pInstance = NULL;

LcmBase::LcmBase(){
    if(!lcm.good()){
        std::cout<<"error on lcmbase"<<std::endl;
    }
}

LcmBase::~LcmBase(){
    if(LcmBase::m_pInstance)
        delete LcmBase::m_pInstance;
}

LcmBase* LcmBase:: get_instance(){
    if(m_pInstance==NULL){
        m_pInstance = new LcmBase();
    }
    return m_pInstance;
}


lcm::LCM LcmBase::get_lcm(){
    return lcm;
}


