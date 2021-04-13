#pragma once
#include <functional>

#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_msg/FloatMsg.hpp"

/** 
 * Block to hold the value at trigger
 * IP_1_TRIGGER is triggered as a switch to hold value
 * IP_O_DATA will receive the data and forward to OP_O_DATA
 * when not triggered. Once Trigger condition is true,
 * the value will be saved in memory and sent to output
 * when IP_0_DATA receives a value.
 */

class HoldVal : public Block {
private:
    FloatMsg _val;
    std::function<bool(float,float)> _operation;
    float _trigger_value;
    Port* _input_port;
    Port* _trigger_port;
    Port* _output_port_0;
    bool hold = false;
    void triggerCallback(float t_current_value);
public:
    HoldVal(std::function<bool(float,float)> t_operation, float t_trigger_value);
    enum ports_id {IP_0_DATA, IP_1_TRIGGER, OP_0_DATA};
    void process(DataMsg* t_msg, Port* t_port);
    ~HoldVal();
};