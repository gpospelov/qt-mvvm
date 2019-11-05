// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialItems.h"
#include "item_constants.h"
#include <mvvm/standarditems/vectoritem.h>
#include <QColor>

using namespace ModelView;

MaterialContainerItem::MaterialContainerItem()
    : ModelView::CompoundItem(::Constants::MaterialContainerType)
{
    registerTag(TagInfo::universalTag(
        T_MATERIALS, {::Constants::SLDMaterialType, ::Constants::RefIndexMaterialType}));
}

// ----------------------------------------------------------------------------

MaterialBaseItem::MaterialBaseItem(const std::string& model_type)
    : ModelView::CompoundItem(model_type)
{
    addProperty(P_COLOR, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_NAME, "Unnamed")->setDisplayName("Name");
}

/*! Creates mag. field-related properties.
 *  Should be called from descendants' constructors in order
 *  to preserve view-oriented property sequence.
 *  The same can be achieved with a proper
 *  ModelView::RowStrategyInterface::constructRow
 *  implementation.
 */
void MaterialBaseItem::initMagFields()
{
    addProperty(P_H_X, 0.0)->setDisplayName("H, x");
    addProperty(P_H_Y, 0.0)->setDisplayName("H, y");
    addProperty(P_H_Z, 0.0)->setDisplayName("H, z");
}

// ----------------------------------------------------------------------------

SLDMaterialItem::SLDMaterialItem() : MaterialBaseItem(::Constants::SLDMaterialType)
{
    addProperty(P_SLD_REAL, 1e-06)->setDisplayName("Re(SLD)");
    addProperty(P_SLD_IMAG, 1e-08)->setDisplayName("Im(SLD)");
    initMagFields();
}

void SLDMaterialItem::set_properties(const std::string& name, const QColor& color, double real,
                                     double imag)
{
    setProperty(P_NAME, QVariant::fromValue(name));
    setProperty(P_COLOR, QVariant::fromValue(color));
    setProperty(P_SLD_REAL, real);
    setProperty(P_SLD_IMAG, imag);
}

// ----------------------------------------------------------------------------

RefIndexMaterialItem::RefIndexMaterialItem() : MaterialBaseItem(::Constants::RefIndexMaterialType)
{
    addProperty(P_DELTA, 1e-06)->setDisplayName("Delta");
    addProperty(P_BETA, 1e-08)->setDisplayName("Beta");
    initMagFields();
}

void RefIndexMaterialItem::set_properties(const std::string& name, const QColor& color,
                                          double delta, double beta)
{
    setProperty(P_NAME, QVariant::fromValue(name));
    setProperty(P_COLOR, QVariant::fromValue(color));
    setProperty(P_DELTA, delta);
    setProperty(P_BETA, beta);
}
