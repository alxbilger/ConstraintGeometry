#pragma once

#include <sofa/constraintGeometry/BaseNormalHandler.h>
#include <sofa/collisionAlgorithm/proximity/TriangleProximity.h>
#include <sofa/constraintGeometry/ConstraintProximity.h>
#include <sofa/collisionAlgorithm/proximity/TriangleProximity.h>
#include <sofa/collisionAlgorithm/proximity/MechanicalProximity.h>

namespace sofa::constraintGeometry {

class GouraudTriangleNormalHandler : public BaseNormalHandler {
public:

    SOFA_CLASS(GouraudTriangleNormalHandler, BaseNormalHandler);

    core::objectmodel::SingleLink<GouraudTriangleNormalHandler, BaseGeometry, BaseLink::FLAG_STRONGLINK|BaseLink::FLAG_STOREPATH> l_geometry;

    GouraudTriangleNormalHandler()
    : l_geometry(initLink("geometry", "link to the second normal handler")) {
        l_geometry.setPath("@.");
    }

    BaseGeometry * getGeometry() override { return l_geometry.get(); }

    void prepareDetection() override {}

    const std::type_info & getTypeInfo() override { return typeid(GouraudTriangleNormalHandler); }

    template<class PROXIMITY>
    type::Vector3 getNormal(const typename PROXIMITY::SPtr & prox);

    template<class PROXIMITY>
    static inline ConstraintProximity::SPtr buildCstProximity(GouraudTriangleNormalHandler * handler, typename PROXIMITY::SPtr prox) {
        return TConstraintProximity<PROXIMITY>::create(prox,std::bind(&GouraudTriangleNormalHandler::getNormal<PROXIMITY>,handler,std::placeholders::_1));
    }
};

template<>
inline type::Vector3 GouraudTriangleNormalHandler::getNormal<collisionAlgorithm::TriangleProximity>(const collisionAlgorithm::TriangleProximity::SPtr & prox) {
    return prox->element()->getTriangleInfo().N;
}


template<>
inline type::Vector3 GouraudTriangleNormalHandler::getNormal<collisionAlgorithm::MechanicalProximity<sofa::defaulttype::Vec3dTypes>>(const collisionAlgorithm::MechanicalProximity<sofa::defaulttype::Vec3dTypes>::SPtr & prox) {
    const collisionAlgorithm::PointElement::SPtr & element = prox->getGeometry()->pointElements()[prox->getPId()];

    type::Vector3 N0_point;
    for (auto it = element->triangleAround().cbegin();it!=element->triangleAround().cend();it++) {
        N0_point+=(*it)->getTriangleInfo().N;
        break;
    }

    return N0_point.normalized();
}

}
