#pragma once

#include <vector>
#include "HEAR_actuation/ActuationSystem.hpp"
#include "HEAR_msg/BoolMsg.hpp"
#include "HEAR_msg/FloatMsg.hpp"
#include "HEAR_msg/VectorDoubleMsg.hpp"

// Using ENU Reference Frame
// GEOMETRY
//      CW(3) (5)CCW                x
//          \ /                     ↑
// CCW(2) -- X -- (1)CW             |
//          / \              y <----+ 
//      CW(6) (4)CCW               z up
//
// For Positive Pitch, all motors with negative X should be increased
// For Negative Roll, all motors with negative Y should be increased
// For Positive Yaw, all motors with CW should be increased
// Mx = [x, y, direction, thottle]
// POSITIVE PITCH result in moving in the direction of POSITIVE X
// NEGATIVE ROLL result in moving in the direction of POSITIVE Y
// Using YPR rotation sequence in the construction of the Rotation Matrix

class HexaActuationSystem : public ActuationSystem {
private: 
    std::vector<Actuator*> _actuators;
    int _escMin = 1000;
    int _escMin_armed = 1150;
    int _escMax = 2000;
    bool _armed = false;
    float _u[4]; //[roll, pitch, yaw, throttle]
    std::vector<double> _commands {0,0,0,0,0,0};
    float _geometry[6][4] = {{-1,    0,          1,     1},
                             { 1,    0,         -1,     1},
                             { 0.5, -0.866025,   1,     1},
                             {-0.5,  0.866025,  -1,     1},
                             {-0.5, -0.866025,  -1,     1},
                             { 0.5,  0.866025,   1,     1}};
    Port* _input_port_0;
    Port* _input_port_1;
    Port* _input_port_2;
    Port* _input_port_3;
    Port* _input_port_4;
    Port* _output_port_0;
    Port* _output_port_1;
public:
    enum ports_id {IP_0_DATA_ROLL, IP_1_DATA_PITCH, IP_2_DATA_YAW, IP_3_DATA_Z, IP_4_ARM, OP_0_CMD, OP_1_ARM};
    void process(DataMsg* t_msg, Port* t_port);
    void setESCValues(int, int, int);
    void command();
    int constrain(float value, int min_value, int max_value);
    HexaActuationSystem(std::vector<Actuator*>);
    ~HexaActuationSystem();
};
