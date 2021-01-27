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

class QSplitter;

namespace ModelView {
class PropertyTreeView;
class TopItemsTreeView;
} // namespace ModelView

namespace NodeEditor {

class SampleModel;
class ConnectableItem;

//! The panel with sample tree on top, and item property editor at the bottom.
//! Located on the right side of ModelEditorWidget.

class PropertyWidget : public QWidget {
    Q_OBJECT

public:
    PropertyWidget(SampleModel* model, QWidget* parent = nullptr);

    void onSelectionRequest(ConnectableItem* item);

private:
    SampleModel* m_model{nullptr};
    ModelView::TopItemsTreeView* m_topItemsTree{nullptr};
    ModelView::PropertyTreeView* m_propertyTree{nullptr};
    QSplitter* m_splitter{nullptr};
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_PROPERTYWIDGET_H
