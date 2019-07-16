// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleDesigner.cpp
//! @brief     Implements class SampleDesigner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "FilterPropertyProxy.h"
#include "ISample.h"
#include "MultiLayerView.h"
#include "ApplicationModels.h"

SampleDesigner::SampleDesigner(QWidget *parent)
    : SampleDesignerInterface(parent)
    , m_designerScene(0)
    , m_designerView(0)
{
    m_designerScene = new DesignerScene(parent);
    m_designerView = new DesignerView(m_designerScene, parent);
}


SampleDesigner::~SampleDesigner()
{
}

void SampleDesigner::setModels(ApplicationModels* models)
{
    m_designerScene->setSampleModel(models->sampleModel());
    m_designerScene->setInstrumentModel(models->instrumentModel());
    m_designerScene->setMaterialModel(models->materialModel());
}

void SampleDesigner::setSelectionModel(QItemSelectionModel *model, FilterPropertyProxy *proxy)
{
    if(model) m_designerScene->setSelectionModel(model, proxy);
}
