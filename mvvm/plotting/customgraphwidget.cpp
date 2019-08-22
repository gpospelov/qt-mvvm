// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "customgraphwidget.h"
#include "qcustomplot.h"
#include <QBoxLayout>

using namespace ModelView;

struct CustomGraphWidget::CustomGraphWidgetPrivate {
    QCustomPlot* m_customPlot{nullptr};
    CustomGraphWidgetPrivate() : m_customPlot(new QCustomPlot) {}
};

CustomGraphWidget::CustomGraphWidget(QWidget* parent)
    : QWidget(parent), p_impl(std::make_unique<CustomGraphWidgetPrivate>())
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(p_impl->m_customPlot);
    setLayout(layout);
}
