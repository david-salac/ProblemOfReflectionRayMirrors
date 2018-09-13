#include "Mirror.hpp"
#include <cmath>
#include <limits>

#define M_PI (3.14159265358979323846)

void Mirror::setTempCoordinates(const double & x_start, const double & x_end, const double & y_start, const double & y_end) {
    this->m_x_start_temp = x_start;
    this->m_y_start_temp = y_start;
    this->m_x_end_temp = x_end;
    this->m_y_end_temp = y_end;
}   
double Mirror::getXStart() { 
    return m_x_start;
}
double Mirror::getYStart() { 
    return m_y_start;
}
double Mirror::getXEnd() { 
    return m_x_end;
}
double Mirror::getYEnd() { 
    return m_y_end;
}

double Mirror::getXStartTemp() { 
    return m_x_start_temp;
}
double Mirror::getYStartTemp() { 
    return m_y_start_temp;
}
double Mirror::getXEndTemp() { 
    return m_x_end_temp;
}
double Mirror::getYEndTemp() { 
    return m_y_end_temp;
}

double Mirror::computeXAxisIntersection(bool & exists) {
    //Check whether the intersection with x axis exists
    exists = ( (this->m_y_start_temp > 0 && this->m_y_end_temp < 0) || (this->m_y_start_temp < 0 && this->m_y_end_temp > 0) );
    
    if(!exists) {
        return 0.0;
    }

    //Compute coefficients of equation: y = ax + b
    double a = (m_y_start_temp - m_y_end_temp) / (m_x_start_temp - m_x_end_temp);
    double b = m_y_start_temp - a*m_x_start_temp;
    
    this->m_intersection_dist_x = (-1.0)*(b/a);
    if(this->m_intersection_dist_x <= 0) {
        exists = false;
        return 0.0;
    } 
    return this->m_intersection_dist_x;
}

std::string Mirror::toString() {
    std::string res = "x_start: ";
    res += std::to_string(this->m_x_start);
    res += ", x_end: ";
    res += std::to_string(this->m_x_end);
    res += ", y_start: ";
    res += std::to_string(this->m_y_start);
    res += ", y_end: ";
    res += std::to_string(this->m_y_end);
    res += "\nx_start_temp: ";
    res += std::to_string(this->m_x_start_temp);
    res += ", x_end_temp: ";
    res += std::to_string(this->m_x_end_temp);
    res += ", y_start_temp: ";
    res += std::to_string(this->m_y_start_temp);
    res += ", y_end_temp: ";
    res += std::to_string(this->m_y_end_temp);
    return res;
}
MirrorIntersectionParameters Mirror::getIntersectionParameters() {
    double vertical_dist = m_y_start_temp;
    double horizontal_dist = (m_intersection_dist_x - m_x_start_temp);
    
    double circle_radius = std::sqrt(vertical_dist*vertical_dist + horizontal_dist*horizontal_dist);
    
    //Substitution to: x_coord = x_start (+/-) pm_part
    double linear_coef = (m_y_end - m_y_start) / (m_x_end - m_x_start);
    if((m_x_end - m_x_start) == 0) {
        linear_coef = std::numeric_limits<double>::max();
    }
    double abs_coef = m_y_start - linear_coef*m_x_start;
    
    double x_coord = m_x_start;
    double pm_part = circle_radius / std::sqrt(1 + linear_coef*linear_coef);
    if(m_x_start < m_x_end) {
        x_coord += pm_part;
    } else {
        x_coord -= pm_part;
    }
    double y_coord = x_coord*linear_coef + abs_coef;
    
    double angle =  std::atan(y_coord / x_coord) + 2.0*std::atan( (abs_coef - y_coord) / x_coord );
    
    return MirrorIntersectionParameters{x_coord, y_coord, angle};
}