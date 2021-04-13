#include "HEAR_math/KalmanFilter.hpp"

KalmanFilter::KalmanFilter(float t_u_scale) {
    _input_port_0 = new InputPort(ports_id::IP_0_ACC, this);
    _input_port_1 = new InputPort(ports_id::IP_1_POS, this);
    _input_port_2 = new InputPort(ports_id::IP_2_RESET, this);
    _output_port_0 = new OutputPort(ports_id::OP_0_POS, this);
    _output_port_1 = new OutputPort(ports_id::OP_1_VEL, this);
    _output_port_2 = new OutputPort(ports_id::OP_2_BIAS, this);
    _ports = {_input_port_0, _input_port_1, _input_port_2, _output_port_0, _output_port_1, _output_port_2};
    resetFilter();
}

KalmanFilter::~KalmanFilter() {

}

void KalmanFilter::resetFilter() {
    _x << _pos_val,
          0,
          0;
    _P << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    _F << 1, _dt, -1*_dt*_dt*0.5,
         0, 1,   -1*_dt,
         0, 0,   1;
    _G << _dt*_dt*0.5,
          _dt,
          0;
    _Q = _G*_war_w*_G.transpose();
    _Q(2,2)=_war_w*0.000010;
    _H_pos << 1, 0, 0;
     std::cout<<"RESETTING KALMAN FILTER\n";
}

void KalmanFilter::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_ACC) {
        doPredictionStep(((FloatMsg*)t_msg)->data);
            if(std::isnan(_x(0,0)) || std::isnan(_x(1,0))){
                resetFilter();
            }
            else {
                FloatMsg position_data, velocity_data, bias_data;
                position_data.data=_x(0,0);
                velocity_data.data=_x(1,0);
                bias_data.data=_x(2,0);
                this->_output_port_0->receiveMsgData((DataMsg*) &position_data);
                this->_output_port_1->receiveMsgData((DataMsg*) &velocity_data);
                this->_output_port_2->receiveMsgData((DataMsg*) &bias_data);
            }
    }
    else if(t_port->getID() == ports_id::IP_1_POS) {
        _pos_val = ((FloatMsg*)t_msg)->data;
        doMeasurementStep(((FloatMsg*)t_msg)->data);
    }
    else if(t_port->getID() == ports_id::IP_2_RESET) {
        this->resetFilter();
    }
}

void KalmanFilter::setTimeStep(float t_dt) {
    _dt = t_dt;
}

void KalmanFilter::doPredictionStep(float t_u) {
    _x = _F*_x + _G*t_u;
    _P = _F*_P*_F.transpose()+_Q;
}

void KalmanFilter::doMeasurementStep(float t_z) {
    float t_S = _H_pos*_P*_H_pos.transpose() + _R_pos;
    Eigen::Matrix<float, 3, 1> t_K = (_P*_H_pos.transpose())/t_S;
    _x = _x + t_K*(t_z - _H_pos*_x);
    _P = (Eigen::Matrix3f::Identity() - t_K*_H_pos)*_P;
}
