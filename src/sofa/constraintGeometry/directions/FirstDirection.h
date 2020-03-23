#pragma once

#include <sofa/constraintGeometry/ConstraintDirection.h>

namespace sofa {

namespace constraintGeometry {

/*!
 * \brief The FirstDirection class
 * Applies specified algorithm on 'from' and 'dest' geometry
 */
class FirstDirection : public ConstraintDirection {
public:
    SOFA_CLASS(FirstDirection , ConstraintDirection);

    /*!
     * \brief The ContactNormal class is the container class for direction constraints
     */
    ConstraintNormal createConstraintsNormal(const collisionAlgorithm::PairDetection & d) const override {
        return ConstraintNormal(-d.first->getNormal());
    }

    ConstraintNormal UpdateConstraintsNormalWithProximityPosition(const collisionAlgorithm::PairDetection & d, defaulttype::Vec3 /*pf*/, bool /*getF*/, defaulttype::Vec3 /*pd*/, bool /*getD*/) const override {
        return createConstraintsNormal(d);
    }

};

}

}
