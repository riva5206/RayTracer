//
//  bvh.h
//  RayTracer
//
//  Created by Pedro Figueirêdo on 12/05/17.
//  Copyright © 2017 Lavid. All rights reserved.
//

#ifndef bvh_h
#define bvh_h

#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <iterator>
#include "primitive.h"
#include "ray.h"
#include "intersection_record.h"
#include "bbox.h"

/* TODO
 *  - Lembrar de fazer método para destruir a porra toda no final.
 *
 */

class BVH
{
public:
    
    enum SplitMethod {CenterSorting , SAH};
    
    BVH(const std::vector< Primitive::PrimitiveUniquePtr > &primitives);
    
    double constructTree(const SplitMethod& splitMethod);
    
    bool intersect( const Ray &ray,
                   IntersectionRecord &intersection_record ) const;
    
private:
    void recursiveConstruct(Bbox* node, int min, int max);
    void SAH_recursiveConstruct(Bbox *node, const std::vector< int > &primitives_index);
    glm::vec3 min_components(const glm::vec3 &vecA, const glm::vec3 &vecB);
    glm::vec3 max_components(const glm::vec3 &vecA, const glm::vec3 &vecB);
    bool traverse(Bbox* node, const Ray &ray, IntersectionRecord &intersection_record) const;
    
    const std::vector< Primitive::PrimitiveUniquePtr > &primitives_;
    std::vector<int> primitives_id_;
    Bbox* root;
};


#endif /* bvh_h */