#include "HEAR_math/NegateFloat.hpp"

NegateFloat::NegateFloat() {
    _input_port = new InputPort(ports_id::IP_0_DATA, this);
    _output_port = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port, _output_port};
}

NegateFloat::~NegateFloat() {

}

void NegateFloat::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_DATA) {
        float data = ((FloatMsg*)t_msg)->data;
        _float_msg.data = data * -1.f;
        _output_port->receiveMsgData((DataMsg*)&_float_msg);
    }
}