//
// Created by vremyavnikuda on 02.09.24.
//

#include "update_light.h"

#include <iostream>

std::string update_light(const std::string &current) {
    if (current == "green") {
        std::cout<<"yellow"<<std::endl;
        return "yellow";
    }else if (current=="yellow") {
        std::cout<<"red"<<std::endl;
        return "red";
    }else if (current=="red") {
        std::cout<<"green"<<std::endl;
        return "green";
    }
    return nullptr;
}
