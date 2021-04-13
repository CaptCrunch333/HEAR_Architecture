#include "HEAR_mission/SendBoolSignal.hpp"

SendBoolSignal::SendBoolSignal(bool t_val) {
    _val = t_val;
    _output_port_0 = new OutputPort(ports_id::OP_0, this);
    _ports = {_output_port_0};
}

void SendBoolSignal::perform(){
    BoolMsg bool_msg;
    bool_msg.data = _val;
    this->_output_port_0->receiveMsgData(&bool_msg);
}
