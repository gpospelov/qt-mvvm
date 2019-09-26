// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "data1dplotcontroller.h"
#include "qcustomplot.h"
#include "data1ditem.h"

using namespace ModelView;

struct Data1DPlotController::Data1DPlotControllerPrivate {
    QCPGraph* m_graph{nullptr};
    Data1DPlotControllerPrivate(QCPGraph* graph) : m_graph(graph) {

    }

};

Data1DPlotController::Data1DPlotController(QCPGraph* graph)
    : p_impl(std::make_unique<Data1DPlotControllerPrivate>(graph))
{
}

void Data1DPlotController::subscribe()
{

}

Data1DPlotController::~Data1DPlotController() = default;
