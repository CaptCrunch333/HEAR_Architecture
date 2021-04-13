#include "HEAR_math/InverseRotateVec.hpp"

InverseRotateVec::InverseRotateVec() {
    this->_input_port_0 = new InputPort(ports_id::IP_0_VEC, this);
    this->_input_port_1 = new InputPort(ports_id::IP_1_ROLL, this);
    this->_input_port_2 = new InputPort(ports_id::IP_2_PITCH, this);
    this->_input_port_3 = new InputPort(ports_id::IP_3_YAW, this);
    this->_output_port = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port_0, _input_port_1,_input_port_2,_input_port_3, _output_port};
}

InverseRotateVec::~InverseRotateVec(){

}

void InverseRotateVec::process(DataMsg* t_msg, Port* t_port) {
    Vector3DMsg *provider = (Vector3DMsg *)t_msg;
    if(t_port->getID() == ports_id::IP_0_VEC) {
        _vec_data.x = provider->data.x;
        _vec_data.y = provider->data.y;
        _vec_data.z = provider->data.z;
    }
    else if(t_port->getID() == ports_id::IP_1_ROLL) { 
        _body_orientation.x =provider->data.x;
    }
    else if(t_port->getID() == ports_id::IP_2_PITCH) { 
        _body_orientation.y =provider->data.x;
        updateRotationMatrix();
    }
    else if(t_port->getID() == ports_id::IP_3_YAW) { 
        _body_orientation.z =provider->data.x;
    }
}

void InverseRotateVec::updateRotationMatrix() {
    Eigen::Matrix<float, 3, 3> R_inertia;
    _body_rotation_matrix.Update(_body_orientation);
    _body_rotation_matrix.Transpose();
    rotateVector(R_inertia);
}

void InverseRotateVec::rotateVector(Eigen::Matrix<float, 3, 3> R_inertia) {
    // _rotated_vec.x = _vec_data.x * R_inertia(0, 0) + _vec_data.y * R_inertia(0, 1) + _vec_data.z * R_inertia(0, 2);
    // _rotated_vec.y = _vec_data.x * R_inertia(1, 0) + _vec_data.y * R_inertia(1, 1) + _vec_data.z * R_inertia(1, 2);
    // _rotated_vec.z = _vec_data.x * R_inertia(2, 0) + _vec_data.y * R_inertia(2, 1) + _vec_data.z * R_inertia(2, 2);
    
    Vector3DMsg point_msg;
    point_msg.data = _body_rotation_matrix.TransformVector(_vec_data);
    this->_output_port->receiveMsgData(&point_msg);
}

