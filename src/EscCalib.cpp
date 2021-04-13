#include "HEAR_actuation/EscCalib.hpp"

EscCalib::EscCalib(std::vector<Actuator*> t_actuators){
    _actuators = t_actuators;
    _input_port_0 = new InputPort(ports_id::IP_0_MODE, this);
    _input_port_1 = new InputPort(ports_id::IP_1_TRIGGER, this);
    _input_port_2 = new InputPort(ports_id::IP_2_SIGNAL, this);
    _input_port_3 = new InputPort(ports_id::IP_3_CHANNEL, this);
    _ports = {_input_port_0, _input_port_1, _input_port_2, _input_port_3};
}

void EscCalib::setEscValues(int min, int max, int armed){
    _esc_min = min;
    _esc_max = max;
    _esc_armed = armed;
}

void EscCalib::setChannel(uint8_t chan){
    _selected_chan = chan;
}

void EscCalib::process(DataMsg* t_msg, Port* t_port){
    if(t_port->getID() == ports_id::IP_0_MODE){
        uint8_t ind = ((Int8Msg*)t_msg)->data;
        this->mode = MODES[ind];

        switch(ind){
            case modes::ALL:
                std::cout << "ALL calibration mode selected\n";
                break;
            case modes::SINGLE:
                std::cout << "SINGLE calibration mode selected\n";
                break;
            case modes::CHECK_ALL:
                std::cout << "CHECK_ALL mode selected\n";
                break;
            case modes::CHECK_SINGLE:
                std::cout << "CHECK_SINGLE mode selected\n";
                break;
        }
    }
    else if(t_port->getID() == ports_id::IP_1_TRIGGER){
        if(((BoolMsg*)t_msg)->data){

            if(this->mode == modes::ALL){
                this->actuate(_esc_max);
            }
            else if(this->mode == modes::SINGLE){
                this->actuate(_esc_max, this->_selected_chan);
            }
            std::cout << "\n ***Calibration started*** \n Max throttle sent\n";
        }
        else{
            this->actuate(_esc_min);
            std::cout << "\n ***Calibration done*** \n Min throttle sent\n";
        }
    }
    else if(t_port->getID() == ports_id::IP_2_SIGNAL){
        int sig = ((IntegerMsg*)t_msg)->data;
        if(this->mode == modes::CHECK_ALL){
            this->actuate(sig);
        }
        else if(this->mode == modes::CHECK_SINGLE){
            this->actuate(sig, this->_selected_chan);
        }
    }
    else if(t_port->getID() == ports_id::IP_3_CHANNEL){
        uint8_t Chan = ((Int8Msg*)t_msg)->data;
        this->setChannel(Chan);
        std::cout << "Channel " << (int)Chan << " is selected \n";
    }
}

void EscCalib::actuate(int t_signal, int t_chan){
    if (t_chan==999){
        for(int i =0; i<_actuators.size(); i++) _actuators[i]->applyCommand(t_signal);
    }
    else{
        _actuators[t_chan]->applyCommand(t_signal);
    }

}
