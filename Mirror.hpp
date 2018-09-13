/*
 * David Salac
 */

#ifndef MIRROR_HPP
#define MIRROR_HPP

#include <string>
#include <tuple>

#include "MirrorIntersectionParameters.h"

/**
 * Represents one mirror in 2D space
 */
class Mirror {
private:
    const double m_x_start;
    const double m_x_end;
    const double m_y_start;
    const double m_y_end;
    
    double m_x_start_temp;
    double m_x_end_temp;
    double m_y_start_temp;
    double m_y_end_temp;
    
    double m_intersection_dist_x;
public:
    /**
     * Init instance
     * @param x_start Horizontal position of start point
     * @param x_end Horizontal position of end point
     * @param y_start Vertical position of start point
     * @param y_end Vertical position of end point
     */
    Mirror(const double & x_start, const double & x_end, const double & y_start, const double & y_end) : 
        m_x_start(x_start), m_x_end(x_end), m_y_start(y_start), m_y_end(y_end),
        m_x_start_temp(x_start), m_x_end_temp(x_end), m_y_start_temp(y_start), m_y_end_temp(y_end) 
    {}
    
    /**
     * Set temporary coordinates (for the purposes of rotation)
     * @param x_start Horizontal position of start point
     * @param x_end Horizontal position of end point
     * @param y_start Vertical position of start point
     * @param y_end Vertical position of end point
     */
    void setTempCoordinates(const double & x_start, const double & x_end, const double & y_start, const double & y_end);
    
    /**
     * @return Horizontal position of start point
     */
    double getXStart();
    /**
     * @return Vertical position of start point
     */
    double getYStart();
    /**
     * @return Horizontal position of end point
     */
    double getXEnd();
    /**
     * @return Vertical position of end point
     */
    double getYEnd();
    
    //Get coordinates after rotation
    /**
     * @return Horizontal position of start point after rotation
     */
    double getXStartTemp();
    /**
     * @return Vertical position of start point after rotation
     */
    double getYStartTemp();
    /**
     * @return Horizontal position of end point after rotation
     */
    double getXEndTemp();
    /**
     * @return Vertical position of end point after rotation
     */
    double getYEndTemp();
    
    /**
     * Compute the distance of the intersection point from beginning (after rotation)
     * @param exists return whether intersection with any mirror exists
     * @return distance of intersection point from beginning
     */
    double computeXAxisIntersection(bool & exists);
    
    /**
     * Compute parameters of intersection point
     * @return Parameters of intersection
     */
    MirrorIntersectionParameters getIntersectionParameters();

    /**
     * Nice output
     * @return String that represents mirror parameters
     */
    std::string toString();
};

#endif /* MIRROR_HPP */

