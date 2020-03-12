// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "RoughnessViewItem.h"

#include "samplemodel.h"
#include "layeritems.h"

#include "materialmodel.h"
#include "materialitems.h"

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

std::string RoughnessViewItem::layerIdentifier(std::string layer_identifier_in)
{
    return layer_identifier;
}

void RoughnessViewItem::fetchFromLayer(SampleModel* layer_model, MaterialModel* material_model)
{
    auto model_pointer = model();
    auto item = dynamic_cast<MaterialBaseItem*>(model_pointer->findItem(layer_identifier));

}
