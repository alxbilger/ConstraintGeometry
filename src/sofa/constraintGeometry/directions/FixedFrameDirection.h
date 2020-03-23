#pragma once

#include <sofa/constraintGeometry/ConstraintDirection.h>
#include <sofa/defaulttype/Vec.h>

namespace sofa {

namespace constraintGeometry {

/*!
 * \brief The BindDirection class
 * Applies specified algorithm on 'from' and 'dest' geometry
 */
class FixedFrameDirection : public ConstraintDirection {
public:
    SOFA_CLASS(FixedFrameDirection , ConstraintDirection);

//    Data<std::vector<defaulttype::Vec3> > d_frame ;

    FixedFrameDirection ()
//        : d_frame (initData(&d_frame, "frame", "frame vectors"))
    {}

    /*!
     * \brief The ContactNormal class is the container class for direction constraints
     */
    ConstraintNormal createConstraintsNormal(const collisionAlgorithm::PairDetection & /*d*/) const override {
        ConstraintNormal CN ;
        return CN.addOrthogonalDirection()
                 .addOrthogonalDirection()
                 .addOrthogonalDirection();
    }

    ConstraintNormal UpdateConstraintsNormalWithProximityPosition(const collisionAlgorithm::PairDetection & d, defaulttype::Vec3 /*pf*/, bool /*getF*/, defaulttype::Vec3 /*pd*/, bool /*getD*/) const override {
        return createConstraintsNormal(d);
    }

};

}

}
