// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TESTWIDGET3_H
#define TESTWIDGET3_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class ItemsTreeView;
} // namespace ModelView

//! Playground to test basics of ViewModel.

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(QWidget* parent = nullptr);
    ~TestWidget();

private:
    ModelView::ItemsTreeView* m_defaultTreeView;
};

#endif // TESTWIDGET3_H
