#pragma once
#include <functional>
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_msg/FloatMsg.hpp"

class Sum : public Block {
private:
    std::function<float(float,float)> _operation;
    Port* _input_port_0;
    Port* _input_port_1;
    Port* _output_port;
    float _v1=0.0, _v2=0.0;
    uint8_t _p1=0 , _p2=0;
public:
    enum ports_id {IP_0_DATA, IP_1_DATA, OP_0_DATA};
    void runTask();
    void process(DataMsg* t_msg, Port* t_port);
    Sum(std::function<float(float,float)> t_operation);
    ~Sum();
};