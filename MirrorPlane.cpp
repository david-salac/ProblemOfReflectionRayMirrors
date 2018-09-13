#include "MirrorPlane.hpp"
#include "MirrorIntersectionParameters.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <complex>
#include "Point.h"

void MirrorPlane::addMirror(double x_start, double x_end, double y_start, double y_end) {
    this->m_mirrors.push_back(Mirror(x_start, x_end, y_start, y_end));
}

MirrorPlane::MirrorPlane(double ray_x_start, double ray_x_end, double ray_y_start, double ray_y_end) {
    //Compute offset
    this->m_ray_x = ray_x_start;
    this->m_ray_y = ray_y_start;
    
    //Compute ray size
    double ray_size = std::sqrt( (ray_y_start - ray_y_end)*(ray_y_start - ray_y_end) + (ray_x_start - ray_x_end)*(ray_x_start - ray_x_end) );
    this->m_ray_size = (int)ray_size;
    
    //Find angle
    this->m_angle = std::atan(  (ray_y_end - ray_y_start) / (ray_x_end - ray_x_start)  );
    
    this->m_max_dist = std::sqrt((ray_x_start-ray_x_end)*(ray_x_start-ray_x_end) + (ray_y_start-ray_y_end)*(ray_y_start-ray_y_end));
    
    this->m_nearest_mirror = nullptr;
    this->m_current_mirror = nullptr;
}

void MirrorPlane::setNewCenter() {
    for(auto & mirror : this->m_mirrors) {
        double new_x_start = mirror.getXStart() - this->m_total_offset_x;
        double new_x_end = mirror.getXEnd() - this->m_total_offset_x;
        
        double new_y_start = mirror.getYStart() - this->m_total_offset_y;
        double new_y_end = mirror.getYEnd() - this->m_total_offset_y;
        
        mirror.setTempCoordinates(new_x_start, new_x_end, new_y_start, new_y_end);
    }
}

void MirrorPlane::rotateMirrors() {
    double sin_angle = std::sin((-1.0)*this->m_angle);
    double cos_angle = std::cos((-1.0)*this->m_angle);
    
    for(auto & mirror : this->m_mirrors) {
        double new_x_start = mirror.getXStartTemp() * cos_angle - mirror.getYStartTemp() * sin_angle;
        double new_y_start = mirror.getXStartTemp() * sin_angle + mirror.getYStartTemp() * cos_angle;
        
        double new_x_end = mirror.getXEndTemp() * cos_angle - mirror.getYEndTemp() * sin_angle;
        double new_y_end = mirror.getXEndTemp() * sin_angle + mirror.getYEndTemp() * cos_angle;
        
        mirror.setTempCoordinates(new_x_start, new_x_end, new_y_start, new_y_end);
    }
}

void MirrorPlane::findNearestPoint() {
    this->m_nearest_mirror = nullptr;
    if(this->m_mirrors.empty()) {
        return;
    }
    double min_ref = 0.0;
    bool start = true;
    
    for (auto & mirror : this->m_mirrors) { 
        if(this->m_current_mirror == &mirror) {
            continue;
        } 
        
        bool intersection_exists = false;
        double mirror_min = mirror.computeXAxisIntersection(intersection_exists);
        if(intersection_exists) {
            if(start) {
                min_ref = mirror_min;
                this->m_nearest_mirror = &mirror;
                continue;
            }
            if(mirror_min < min_ref) {
                min_ref = mirror_min;
                this->m_nearest_mirror = &mirror;
            }
        }
    }
}

void MirrorPlane::findWay() {
    this->m_total_offset_x = m_ray_x;
    this->m_total_offset_y = m_ray_y;
    this->setNewCenter();
    this->rotateMirrors();
    this->findNearestPoint();
    this->m_current_mirror = this->m_nearest_mirror;
    
    std::vector<Point> ray_path;
    ray_path.push_back(Point {this->m_total_offset_x, this->m_total_offset_y});
    
    while(this->m_nearest_mirror != nullptr) {
        MirrorIntersectionParameters intersect = this->m_nearest_mirror->getIntersectionParameters();;
        this->m_total_offset_x = intersect.x_coord;
        this->m_total_offset_y = intersect.y_coord;
        this->m_angle = (-1.0)*intersect.angle_of_impact;
        
        this->m_current_mirror = this->m_nearest_mirror;
        
        this->setNewCenter();
        this->rotateMirrors();
        this->findNearestPoint();
        
        ray_path.push_back(Point {this->m_total_offset_x, this->m_total_offset_y});
    } 
    
    
    if(ray_path.size() > 1) {
        double max_dist = this->m_max_dist;
        for(int i = 1; i < ray_path.size(); i++) {
            double step_dist = std::sqrt( (ray_path[i-1].x - ray_path[i].x)*(ray_path[i-1].x - ray_path[i].x) + (ray_path[i-1].y - ray_path[i].y)*(ray_path[i-1].y - ray_path[i].y) );
            max_dist -= step_dist;
            if(max_dist < 0) {
                break;
            }
            std::cout << "Ray" << i <<"," << (int)std::round(ray_path[i-1].x) << "," << (int)std::round(ray_path[i-1].y)<<",";
            std::cout << (int)std::round(ray_path[i].x) << ","<<(int)std::round(ray_path[i].y)<<std::endl;
        }
        
    }
    
}



