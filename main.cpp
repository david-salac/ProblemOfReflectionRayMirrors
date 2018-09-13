/*
 * Application for solving of reflection in hypothetical room of mirrors
 * @author David Salac <info@davidsalac.eu>
 */

#include <cstdlib>
#include "MirrorPlane.hpp"
#include "MirrorIntersectionParameters.h"
#include <iostream>

using namespace std;

/**
 * Starting point of application
 * @param argc Number of arguments of command line
 * @param argv Arguments of command line
 * @return -
 */
int main(int argc, char** argv) {
    //Random pool of mirrors
    MirrorPlane mirrors(25.0,5000.0,25.0,5000.0);
    mirrors.addMirror(0,600,0,6);
    mirrors.addMirror(600,595,5,600);
    mirrors.addMirror(595,0,600,595);
    mirrors.addMirror(0,0,595,0);
    mirrors.addMirror(312,327,252,151);
    mirrors.addMirror(73,35,516,324);
    mirrors.addMirror(130,195,279,398);
    mirrors.addMirror(301,205,230,144);
    mirrors.addMirror(442,368,25,181);
    mirrors.addMirror(557,414,477,497);
    mirrors.addMirror(252,214,396,498);
    mirrors.addMirror(199,347,347,390);
    mirrors.addMirror(172,59,157,140);
    mirrors.addMirror(460,362,411,502);
    
    mirrors.findWay();
    
    return 0;
}

