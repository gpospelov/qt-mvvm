// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_CONNECTABLEITEM_H
#define NODEEDITORCORE_CONNECTABLEITEM_H

#include "portinfo.h"
#include "mvvm/model/compounditem.h"

class QColor;

namespace NodeEditor {

//! Base class for all node editor items.

class ConnectableItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_XPOS = "P_XPOS";
    static inline const std::string P_YPOS = "P_YPOS";
    static inline const std::string P_COLOR = "P_COLOR";

    explicit ConnectableItem(const std::string& modelType);

    QColor color() const;

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    void setPos(double x, double y);

    void setNamedColor(const std::string& named_color);

    virtual std::vector<PortInfo> inputPorts() const;

    virtual std::vector<PortInfo> outputPorts() const;
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_CONNECTABLEITEM_H
