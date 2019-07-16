// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewFactory.cpp
//! @brief     Implements class SampleViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleViewFactory.h"
#include "InterferenceFunctionViews.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "MesoCrystalView.h"
#include "ParticleCompositionView.h"
#include "ParticleCoreShellView.h"
#include "ParticleDistributionView.h"
#include "ParticleLayoutView.h"
#include "ParticleView.h"
#include "TransformationView.h"
#include "item_constants.h"

QStringList SampleViewFactory::m_valid_item_names  = QStringList()
        << Constants::MultiLayerType
        << Constants::LayerType
        << Constants::ParticleLayoutType
        << Constants::ParticleType
        << Constants::RotationType
        << Constants::ParticleCoreShellType
        << Constants::ParticleCompositionType
        << Constants::MesoCrystalType
        << Constants::ParticleDistributionType
        << Constants::InterferenceFunction1DLatticeType
        << Constants::InterferenceFunction2DLatticeType
        << Constants::InterferenceFunction2DParaCrystalType
        << Constants::InterferenceFunctionFinite2DLatticeType
        << Constants::InterferenceFunctionHardDiskType
<< Constants::InterferenceFunctionRadialParaCrystalType;


bool SampleViewFactory::isValidType(const QString &name)
{
    if(name.startsWith(Constants::FormFactorType)) {
        return true;
    } else {
        return m_valid_item_names.contains(name);
    }
}


IView *SampleViewFactory::createSampleView(const QString &name)
{
    if (name==Constants::MultiLayerType) {
        return new MultiLayerView();
    }
    else if (name==Constants::LayerType) {
        return new LayerView();
    }
    else if (name==Constants::ParticleLayoutType) {
        return new ParticleLayoutView();
    }
    else if (name==Constants::ParticleType) {
        return new ParticleView();
    }
    else if (name==Constants::RotationType) {
        return new TransformationView();
    }
    else if (name==Constants::ParticleCoreShellType) {
        return new ParticleCoreShellView();
    }
    else if (name==Constants::ParticleCompositionType) {
        return new ParticleCompositionView();
    }
    else if (name==Constants::MesoCrystalType) {
        return new MesoCrystalView();
    }
    else if (name==Constants::ParticleDistributionType) {
        return new ParticleDistributionView();
    }
    else if (name==Constants::InterferenceFunction1DLatticeType) {
        return new InterferenceFunction1DLatticeView();
    }
    else if (name==Constants::InterferenceFunction2DLatticeType) {
        return new InterferenceFunction2DLatticeView();
    }
    else if (name==Constants::InterferenceFunction2DParaCrystalType) {
        return new InterferenceFunction2DParaCrystalView();
    }
    else if (name==Constants::InterferenceFunctionFinite2DLatticeType) {
        return new InterferenceFunctionFinite2DLatticeView();
    }
    else if (name==Constants::InterferenceFunctionHardDiskType) {
        return new InterferenceFunctionHardDiskView();
    }
    else if (name==Constants::InterferenceFunctionRadialParaCrystalType) {
        return new InterferenceFunctionRadialParaCrystalView();
    }
    return 0;
}
