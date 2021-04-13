// Version: 1.0
// Author: Mohamad Chehadeh
// Date: 20 Jan 2021
// Revision Notes: Notion and working based on https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection#:~:text=In%20analytic%20geometry%2C%20the%20intersection,the%20plane%20but%20outside%20it.
#pragma once 
template  <class L> class Vector2D;
template  <class L> class Vector3D;
#include <cstdint>
#include <math.h>
#include <initializer_list>
#include "HEAR_math/Vector3D.hpp"

template <class T>  
class Plane3D {
        public:
                Vector3D<double> p0 ;
                Vector3D<double> p1 ;
                Vector3D<double> p2 ;
                Plane3D<T>(){};
                Plane3D<T>(std::initializer_list<T> tmp){this->x->x = *tmp.begin();this->x->y = *tmp.begin()+1;this->x->z = *tmp.begin()+2;
                this->y->x = *tmp.begin()+3;this->y->y = *tmp.begin()+4;this->y->z = *tmp.begin()+5;this->z->x = *tmp.begin()+6; this->z->y = *(tmp.begin()+7);
                this->z->z = *(tmp.begin()+8);};

                template <typename M>
                operator Plane3D<M>() {
                        Plane3D<M> tmp;
                        tmp.p0 = M(this->p0);
                        tmp.p1 = M(this->p1);
                        tmp.p2 = M(this->p2);

                        return tmp;
                }
                Vector3D<double> getIntersectingLine(Vector3D<double> line_p1,Vector3D<double> line_p2) {
                    Vector3D<double> res,p01,p02,l12;
                    double t;
                    p01=p1-p0;
                    p02=p2-p0;
                    l12=line_p2-line_p1;   
                    
                    t=Vector3D<double>::dot(Vector3D<double>::cross(p01,p02),line_p1-p0)/Vector3D<double>::dot(l12*-1.0,Vector3D<double>::cross(p01,p02));
                    Vector3D<double> tmp1, tmp2;
                    tmp1=Vector3D<double>::cross(p01,p02);

                //     std::cout<<"Vector3D<double>::cross(p01,p02)= "<<tmp1.x<<", "<<tmp1.y<<", "<<tmp1.z<<"\n";

                //     std::cout<<"line_p2= "<<line_p2.x<<", "<<line_p2.y<<", "<<line_p2.z<<"\n";

                //     std::cout<<"l12= "<<l12.x<<", "<<l12.y<<", "<<l12.z<<"\n";

                //     std::cout<<"t= "<<t<<"\n";

                    res=line_p1+l12*t;
                    return res;
                }
};