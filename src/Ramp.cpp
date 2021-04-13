#include "HEAR_math/Ramp.hpp"


Ramp::Ramp(int dx, int dt_ms, int upper_range, int lower_range){
    _input_port_0 = new InputPort(ports_id::IP_0_TRIGGER, this);
    _output_port_0 = new OutputPort(ports_id::OP_0_DATA, this);
    _ports={_input_port_0, _output_port_0};

    this->destroy_t = false;
    this->trig = false;
    this->sendSignal_thread = std::thread(&Ramp::sendSignal, std::ref(*this), dt_ms, dx, lower_range, upper_range);
}

void Ramp::sendSignal(int dt, int dx, int l_range, int u_range){
    int cur_value = l_range;
    int prev_value = l_range;
    IntegerMsg _msg;
    while(!(this->destroy_t)){
        if(trig){
            cur_value = prev_value + dx;
            if (cur_value > u_range) cur_value = u_range;
            _msg.data = cur_value;
            this->_output_port_0->receiveMsgData((DataMsg*)&_msg);
            prev_value = cur_value;
        }
        else{
            cur_value = l_range;
            prev_value = l_range;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(dt)));
    }
}

void Ramp::process(DataMsg* t_msg, Port* t_port){
    if(t_port->getID() == ports_id::IP_0_TRIGGER){
        if(((BoolMsg*)t_msg)->data){
            this->trig = true;
        }
        else{
            this->trig = false;
        }
    }
}

Ramp::~Ramp(){
    this->destroy_t = true;
    this->sendSignal_thread.join();
}
