// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "RoughnessViewItem.h"

#include "layeritems.h"
#include "samplemodel.h"

#include "materialitems.h"
#include "materialmodel.h"

#include <QColor>
#include <QUndoStack>
#include <cmath>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

RoughnessViewItem::RoughnessViewItem() : ModelView::CompoundItem("RoughnessItem")
{
    addProperty(P_ROUGHNESS, 10.)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Roughness");
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color");
}

void RoughnessViewItem::setLayerIdentifier(std::string layer_identifier_in)
{
    layer_identifier = layer_identifier_in;
}

std::string RoughnessViewItem::layerIdentifier()
{
    return layer_identifier;
}

void RoughnessViewItem::fetchFromLayer(SampleModel* layer_model, MaterialModel* material_model)
{
    auto layer_item = dynamic_cast<LayerItem*>(layer_model->findItem(layer_identifier));
    if (!layer_item)
        return;
    auto roughness_item = layer_item->item<RoughnessItem>(LayerItem::P_ROUGHNESS);

    setProperty(P_ROUGHNESS, roughness_item->property(RoughnessItem::P_SIGMA));
}
