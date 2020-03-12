// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SegmentItem.h"

#include "samplemodel.h"
#include "layeritems.h"

#include "materialmodel.h"
#include "materialitems.h"

#include <QColor>
#include <QUndoStack>
#include <cmath>
#include <mvvm/model/externalproperty.h>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

SegmentItem::SegmentItem(std::string layer_identifier_in) 
    : ModelView::CompoundItem("SegmentItem"), layer_identifier(layer_identifier_in)

{
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(P_X_POS, 10.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("X");
    addProperty(P_Y_POS, 10.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("Y");
    addProperty(P_HEIGHT, 5.0)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Height");
    addProperty(P_WIDTH, 5.)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Width");
    addProperty(P_HORIZONTAL, true)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Horizontal");
}

void SegmentItem::setLayerIdentifier(std::string layer_identifier_in)
{
    layer_identifier = layer_identifier_in;
}

std::string SegmentItem::layerIdentifier(std::string layer_identifier_in)
{
    return layer_identifier;
}

void SegmentItem::fetchFromLayer(SampleModel* layer_model, MaterialModel* material_model)
{
    auto layer_item = dynamic_cast<LayerItem*>(layer_model->findItem(layer_identifier));
    if (!layer_item)
        return;

    double buffer_x = property(P_X_POS).toDouble() - property(P_WIDTH).toDouble()/2;
    setProperty(P_WIDTH, layer_item->property(LayerItem::P_THICKNESS).toDouble());
    setProperty(P_X_POS, buffer_x+layer_item->property(LayerItem::P_THICKNESS).toDouble()/2);

    auto material_item = dynamic_cast<SLDMaterialItem*>(
        material_model->findItem(layer_item->property(LayerItem::P_MATERIAL).value<ModelView::ExternalProperty>().identifier()));
    if (!material_item)
        return;

    setProperty(P_Y_POS, material_item->property(SLDMaterialItem::P_SLD_REAL).toDouble()*1e6);
    setProperty(P_COLOR, material_item->property(SLDMaterialItem::P_COLOR));
}
