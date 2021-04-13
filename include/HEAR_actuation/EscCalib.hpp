#pragma once

#include <iostream>
#include <vector>

#include "HEAR_actuation/Actuator.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_msg/Int8Msg.hpp"
#include "HEAR_msg/BoolMsg.hpp"
#include "HEAR_msg/IntegerMsg.hpp"


class EscCalib : public Block {
private:
    int _esc_min = 1000, _esc_max = 2000, _esc_armed = 1150;
    std::vector<Actuator*> _actuators;
    uint8_t mode = 0;
    const uint8_t MODES[4] = {modes::ALL, modes::SINGLE, modes::CHECK_ALL, modes::CHECK_SINGLE};
    uint8_t _selected_chan = 0; 
    Port* _input_port_0;
    Port* _input_port_1;
    Port* _input_port_2;
    Port* _input_port_3;
    void actuate(int signal, int chan=999);
public:
    enum modes{ALL = 0, SINGLE = 1, CHECK_ALL=2, CHECK_SINGLE=3};
    enum ports_id{IP_0_MODE, IP_1_TRIGGER, IP_2_SIGNAL, IP_3_CHANNEL};
    void process(DataMsg* t_msg, Port* t_port);
    void setEscValues(int min, int max, int armed = 1150);
    void setChannel(uint8_t);
    EscCalib(std::vector<Actuator*>);
    ~EscCalib();
};