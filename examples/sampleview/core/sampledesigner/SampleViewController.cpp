// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SampleViewController.h"
#include "ApplicationModels.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "MultiLayerView.h"

SampleViewController::SampleViewController(ApplicationModels* models)
    : m_designerScene(models ? models->sampleModel() : nullptr)
{
}

SampleViewController::~SampleViewController() = default;

DesignerView* SampleViewController::createDesignerView()
{
    return new DesignerView(&m_designerScene);
}

void SampleViewController::setSelectionModel(QItemSelectionModel* model, FilterPropertyProxy* proxy)
{
    if (model)
        m_designerScene.setSelectionModel(model, proxy);
}
