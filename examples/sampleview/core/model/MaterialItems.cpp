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
#include "vectoritem.h"
#include <QColor>

using namespace ModelView;

// ----------------------------------------------------------------------------

const std::string MaterialContainerItem::T_MATERIALS = "T_MATERIALS";

MaterialContainerItem::MaterialContainerItem()
    : ModelView::CompoundItem(::Constants::MaterialContainerType)
{
    registerTag(TagInfo::universalTag(
        T_MATERIALS, {::Constants::SLDMaterialType, ::Constants::RefIndexMaterialType}));
}

// ----------------------------------------------------------------------------

const std::string MaterialBaseItem::P_COLOR = "P_COLOR";
const std::string MaterialBaseItem::P_NAME = "P_NAME";
const std::string MaterialBaseItem::P_H_X = "P_H_X";
const std::string MaterialBaseItem::P_H_Y = "P_H_Y";
const std::string MaterialBaseItem::P_H_Z = "P_H_Z";

MaterialBaseItem::MaterialBaseItem(const std::string& model_type)
    : ModelView::CompoundItem(model_type)
{
    addProperty<>(P_COLOR, QColor(Qt::green))->setDisplayName("Color");
    addProperty<>(P_NAME, "Unnamed")->setDisplayName("Name");
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
    addProperty<>(P_H_X, 0.0)->setDisplayName("H, x");
    addProperty<>(P_H_Y, 0.0)->setDisplayName("H, y");
    addProperty<>(P_H_Z, 0.0)->setDisplayName("H, z");
}

// ----------------------------------------------------------------------------

const std::string SLDMaterialItem::P_SLD_REAL = "P_SLD_REAL";
const std::string SLDMaterialItem::P_SLD_IMAG = "P_SLD_IMAG";

SLDMaterialItem::SLDMaterialItem()
    : MaterialBaseItem(::Constants::SLDMaterialType)
{
    addProperty<>(P_SLD_REAL, 1e-06)->setDisplayName("Re(SLD)");
    addProperty<>(P_SLD_IMAG, 1e-08)->setDisplayName("Im(SLD)");
    initMagFields();
}

void SLDMaterialItem::set_properties(const std::string& name, const QColor& color, double real,
                                     double imag)
{
    setItemValue(P_NAME, QVariant::fromValue(name));
    setItemValue(P_COLOR, QVariant::fromValue(color));
    setItemValue(P_SLD_REAL, real);
    setItemValue(P_SLD_IMAG, imag);
}

// ----------------------------------------------------------------------------

const std::string RefIndexMaterialItem::P_DELTA = "P_DELTA";
const std::string RefIndexMaterialItem::P_BETA = "P_BETA";

RefIndexMaterialItem::RefIndexMaterialItem()
    : MaterialBaseItem(::Constants::RefIndexMaterialType)
{
    addProperty<>(P_DELTA, 1e-06)->setDisplayName("Delta");
    addProperty<>(P_BETA, 1e-08)->setDisplayName("Beta");
    initMagFields();
}

void RefIndexMaterialItem::set_properties(const std::string& name, const QColor& color,
                                          double delta, double beta)
{
    setItemValue(P_NAME, QVariant::fromValue(name));
    setItemValue(P_COLOR, QVariant::fromValue(color));
    setItemValue(P_DELTA, delta);
    setItemValue(P_BETA, beta);
}
