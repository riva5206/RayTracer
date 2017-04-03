//
//  diffuse.cpp
//  RayTracer
//
//  Created by Pedro Figueirêdo on 24/03/17.
//  Copyright © 2017 Lavid. All rights reserved.
//

#include "diffuse.h"

Diffuse::Diffuse(void)
{}

Diffuse::Diffuse( glm::vec3 color){
    emittance_ = {0,0,0};
    if (color.x > 1 || color.y > 1 || color.z > 1){
        brdf_ = {(color.x/255) / PI, (color.y/255) / PI, (color.z/255) / PI};
    }else
        brdf_ = {color.x / PI, color.y / PI, color.z / PI};
}

glm::vec3 Diffuse::getBRDF() const{
    return brdf_;
}

glm::vec3 Diffuse::getEmittance() const{
    return emittance_;
}