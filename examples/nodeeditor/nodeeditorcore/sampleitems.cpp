// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sampleitems.h"
#include "mvvm/editors/editor_constants.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/widgets/widgetutils.h"
#include <QColor>

using namespace ModelView;

namespace NodeEditor {

ConnectableItem::ConnectableItem(const std::string& modelType) : ModelView::CompoundItem(modelType)
{
    addProperty(P_XPOS, 0.0)->setDisplayName("X");
    addProperty(P_YPOS, 0.0)->setDisplayName("Y");
    addProperty(P_COLOR, QColor(Qt::gray))->setDisplayName("Color");
}

QColor ConnectableItem::color() const
{
    return property<QColor>(P_COLOR);
}

double ConnectableItem::x() const
{
    return property<double>(P_XPOS);
}

void ConnectableItem::setX(double x)
{
    setProperty(P_XPOS, x);
}

double ConnectableItem::y() const
{
    return property<double>(P_YPOS);
}

void ConnectableItem::setY(double y)
{
    setProperty(P_YPOS, y);
}

//! Sets named color following schema from https://www.w3.org/TR/css-color-3/#svg-color.
//! e.g. "mediumaquamarine"

void ConnectableItem::setNamedColor(const std::string& named_color)
{
    setProperty(P_COLOR, QColor(QString::fromStdString(named_color)));
}

std::vector<PortInfo> ConnectableItem::inputPorts() const
{
    return {};
}

std::vector<PortInfo> ConnectableItem::outputPorts() const
{
    return {};
}

ParticleItem::ParticleItem() : ConnectableItem(ParticleItemType)
{
    // intended to attach TransformationItem (maximum 1)
    registerTag(TagInfo(T_TRANSFORMATION, 0, 1, {TransformationItemType}), true);
    setNamedColor("antiquewhite");
}

std::vector<PortInfo> ParticleItem::inputPorts() const
{
    return {TransformationPort};
}

TransformationItem::TransformationItem() : ConnectableItem(TransformationItemType)
{
    setNamedColor("lightseagreen");
}

std::vector<PortInfo> TransformationItem::outputPorts() const
{
    return {TransformationPort};
}

} // namespace NodeEditor
