// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class SessionItem;
class SessionModel;
class AllItemsTreeView;
class PropertyTreeView;
class TopItemsTreeView;
} // namespace ModelView

class QTreeView;
class QUndoView;
class QBoxLayout;

//! Collection of tree editors.

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(ModelView::SessionModel* model, QWidget* parent = nullptr);
    ~TestWidget();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    ModelView::SessionItem* item_from_view(QTreeView* view, const QPoint& point);

    QBoxLayout* create_left_layout();
    QBoxLayout* create_middle_layout();
    QBoxLayout* create_right_layout();

    void connect_views();

    QUndoView* m_undoView;
    ModelView::AllItemsTreeView* m_defaultTreeView;
    ModelView::TopItemsTreeView* m_topItemView;
    ModelView::AllItemsTreeView* m_subsetTreeView;
    ModelView::PropertyTreeView* m_propertyTreeView;
    ModelView::SessionModel* m_sessionModel;
};

#endif // TESTWIDGET_H
