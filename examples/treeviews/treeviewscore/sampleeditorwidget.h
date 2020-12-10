// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEEDITORWIDGET_H
#define SAMPLEEDITORWIDGET_H

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

namespace TreeViews
{

//! Collection of tree editors.

class SampleEditorWdiget : public QWidget
{
    Q_OBJECT

public:
    SampleEditorWdiget(ModelView::SessionModel* model, QWidget* parent = nullptr);
    ~SampleEditorWdiget();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    ModelView::SessionItem* item_from_view(QTreeView* view, const QPoint& point);

    QBoxLayout* createLeftLayout();
    QBoxLayout* createMiddleLayout();
    QBoxLayout* createRightLayout();

    void connect_views();

    QUndoView* m_undoView{nullptr};
    ModelView::AllItemsTreeView* m_defaultTreeView{nullptr};
    ModelView::TopItemsTreeView* m_topItemView{nullptr};
    ModelView::AllItemsTreeView* m_subsetTreeView{nullptr};
    ModelView::PropertyTreeView* m_propertyTreeView{nullptr};
    ModelView::SessionModel* m_sessionModel{nullptr};
};

} // namespace TreeViews

#endif // SAMPLEEDITORWIDGET_H
