// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_PROPERTYWIDGET_H
#define NODEEDITORCORE_PROPERTYWIDGET_H

#include <QWidget>

namespace NodeEditor {

//! The panel with sample tree on top, and item property editor at the bottom.
//! Located on the right side of ModelEditorWidget.

class PropertyWidget : public QWidget {
    Q_OBJECT

public:
    PropertyWidget(QWidget* parent = nullptr);
};

} // namespace NodeEditor

#endif //  NODEEDITORCORE_PROPERTYWIDGET_H
