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
#include "axesplotcontroller.h"
#include <QBoxLayout>

using namespace ModelView;

struct CustomGraphWidget::CustomGraphWidgetPrivate {
    QCustomPlot* m_customPlot{nullptr};
    std::unique_ptr<AxesPlotController> m_axesController;

    CustomGraphWidgetPrivate() : m_customPlot(new QCustomPlot)
    {
        m_axesController = std::make_unique<AxesPlotController>(m_customPlot);
    }
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

CustomGraphWidget::~CustomGraphWidget() = default;
