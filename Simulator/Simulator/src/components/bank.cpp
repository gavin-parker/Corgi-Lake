//
// Created by gavin on 24/11/17.
//
#include "../../include/bank.h"


bool Bank<ALU>::isHazard(const Instruction other) {
    bool isHazard = false;
    for(auto &member : members){
        isHazard |= member.isHazard(other);
    }
    return false;
}
