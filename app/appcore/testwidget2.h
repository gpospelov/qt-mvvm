// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TESTWIDGET2_H
#define TESTWIDGET2_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class SessionItem;
class ObsoleteViewModel;
}

namespace ToyItems
{
class SampleModel;
}

class QTreeView;
class QStandardItemModel;
class QTextEdit;
class QPoint;

//! Playground to test basics of ViewModel.

class TestWidget2 : public QWidget
{
    Q_OBJECT
public:
    TestWidget2(QWidget* parent = nullptr);
    ~TestWidget2();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    void init_session_model();
    void update_json();
    void init_tree_view(QTreeView* view);
    ModelView::SessionItem* item_from_view(QTreeView* view, const QPoint& point);

    QTreeView* m_treeView1;
    QTreeView* m_treeView2;
    QTextEdit* m_plainText;
    ModelView::ObsoleteViewModel* m_viewModel;
    std::unique_ptr<ToyItems::SampleModel> m_sessionModel;
};

#endif // TESTWIDGET2_H
