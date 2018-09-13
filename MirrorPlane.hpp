/*
 * David Salac
 */

#ifndef MIRRORPLANE_HPP
#define MIRRORPLANE_HPP

#include "Mirror.hpp"
#include <vector>
#include <memory>

/**
 * Represents the sets of mirror
 */
class MirrorPlane {
private:
    std::vector<Mirror> m_mirrors;
    double m_angle;
    
    int m_ray_size;
    
    double m_ray_x;
    double m_ray_y;
    
    double m_total_offset_x;
    double m_total_offset_y;
    
    double m_max_dist;
    
    Mirror * m_nearest_mirror;
    Mirror * m_current_mirror;
    
    void setNewCenter();
    void rotateMirrors();
    void findNearestPoint();
    
public:
    /**
     * Create new instance with parameters of the ray
     * @param ray_x_start horizontal start position of ray
     * @param ray_x_end horizontal end position of ray
     * @param ray_y_start vertical start position of ray
     * @param ray_y_end vertical end position of ray
     */
    MirrorPlane(double ray_x_start, double ray_x_end, double ray_y_start, double ray_y_end);
    
    /**
     * Add the mirror in 2D space
     * @param x_start Horizontal position of start
     * @param x_end Horizontal position of end
     * @param y_start Vertical position of start
     * @param y_end Vertical position of end
     */
    void addMirror(double x_start, double x_end, double y_start, double y_end);
    
    /**
     * Find the path of ray
     */
    void findWay();
    
};

#endif /* MIRRORPLANE_HPP */

