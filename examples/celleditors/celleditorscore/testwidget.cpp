// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget.h"
#include "itemstreeview.h"
#include <QVBoxLayout>

TestWidget::TestWidget(QWidget* parent)
    : QWidget(parent), m_defaultTreeView(new ModelView::ItemsTreeView)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    setLayout(mainLayout);
}

TestWidget::~TestWidget() = default;
