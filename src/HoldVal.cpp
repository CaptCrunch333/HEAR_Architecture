#include "HEAR_math/HoldVal.hpp"

HoldVal::HoldVal(std::function<bool(float,float)> t_operation, float t_trigger_value) {
    this->_operation = t_operation;
    this->_trigger_value = t_trigger_value;
    this->_input_port = new InputPort(ports_id::IP_0_DATA, this);
    this->_trigger_port = new InputPort(ports_id::IP_1_TRIGGER, this);
    this->_output_port_0 = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port, _trigger_port, _output_port_0};
}

HoldVal::~HoldVal() {

}

void HoldVal::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_DATA){
        if(!(this->hold)){
           _val.data = ((FloatMsg*)t_msg)->data;
        }
        _output_port_0->receiveMsgData(&_val);    
    }
    else if(t_port->getID() == ports_id::IP_1_TRIGGER){
        this->triggerCallback(((FloatMsg*)t_msg)->data);
    }
}

void HoldVal::triggerCallback(float t_current_value) {
    if (this->_operation(t_current_value, _trigger_value)){
        this->hold = true;
    }else{
        this->hold = false;

    }
}


