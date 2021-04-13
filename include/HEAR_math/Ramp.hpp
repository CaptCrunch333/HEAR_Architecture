#pragma once

#include <thread>
#include <atomic>
#include <chrono>

#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_msg/BoolMsg.hpp"
#include "HEAR_msg/IntegerMsg.hpp"


class Ramp : public Block {
private:
    Port* _input_port_0;
    Port* _output_port_0;
    
    std::atomic<bool> destroy_t;
    std::atomic<bool> trig;    
    void sendSignal(int dt, int dx, int l_range, int u_range);
    std::thread sendSignal_thread;
public:
    enum ports_id{IP_0_TRIGGER, OP_0_DATA};
    Ramp(int dx, int dt, int upper_range, int lower_range = 0);
    void process(DataMsg* t_msg, Port* t_port);
    ~Ramp();
};
