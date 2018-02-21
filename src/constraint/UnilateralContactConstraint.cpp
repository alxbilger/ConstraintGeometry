/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 RC 1        *
*                (c) 2006-2011 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                               SOFA :: Plugins                               *
*                                                                             *
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/

#include "response/UnilateralResponse.h"
#include "UnilateralContactConstraint.h"
#include <sofa/core/ObjectFactory.h>
#include <sofa/core/visual/VisualParams.h>
#include <math.h>
#include <assert.h>     /* assert */

namespace sofa
{

namespace core
{

namespace behavior
{

UnilateralContactConstraint::UnilateralContactConstraint()
: d_algo(initData(&d_algo, "algo", "Collision reponse algorithm")) {}


void UnilateralContactConstraint::init() {
    this->getContext()->get(m_algo,d_algo.getValue());
    if (m_algo == NULL) serr << "Error cannot find the algo" << std::endl;
}

void UnilateralContactConstraint::fillConstraints(helper::vector<ConstraintResponsePtr> &constraints) {
    m_algo->clear();
    m_algo->update();

    const PariProximityVector & detection = m_algo->getDetection();

    for (unsigned i=0;i<detection.size();i++) {
        ConstraintProximityPtr prox1 = detection[i].first;
        ConstraintProximityPtr prox2 = detection[i].second;
        defaulttype::Vector3 N = prox2->getPosition() - prox1->getPosition();
        N.normalize();

        ConstraintResponsePtr cst = std::make_shared<UnilateralResponse>(prox1,prox2,N);

        constraints.push_back(cst);
    }
}


SOFA_DECL_CLASS(UnilateralContactConstraint)

int UnilateralContactConstraintClass = core::RegisterObject("Triangle liear interpolation")
.add<UnilateralContactConstraint >()
;

} // namespace controller

} // namespace component

} // namespace sofa

