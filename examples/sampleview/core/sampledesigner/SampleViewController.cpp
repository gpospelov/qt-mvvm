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

#include "SampleViewController.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "MultiLayerView.h"
#include "ApplicationModels.h"

SampleViewController::SampleViewController(ApplicationModels* models)
    : m_designerScene(models ? models->sampleModel() : nullptr)
{}


SampleViewController::~SampleViewController() = default;

DesignerView* SampleViewController::createDesignerView()
{
    return new DesignerView(&m_designerScene);
}

void SampleViewController::setSelectionModel(QItemSelectionModel *model, FilterPropertyProxy *proxy)
{
    if(model) m_designerScene.setSelectionModel(model, proxy);
}
