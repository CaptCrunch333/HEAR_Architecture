#pragma once
#include <functional>
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_msg/FloatMsg.hpp"

class NegateFloat : public Block {
private:
    Port* _input_port;
    Port* _output_port;
    FloatMsg _float_msg;
    int _num_samples = 0;
public:
    enum ports_id {IP_0_DATA, OP_0_DATA};
    void process(DataMsg* t_msg, Port* t_port);
    NegateFloat();
    ~NegateFloat();
};