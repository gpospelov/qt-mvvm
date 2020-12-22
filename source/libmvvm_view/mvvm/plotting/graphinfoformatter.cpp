// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/graphinfoformatter.h"
#include "mvvm/utils/stringutils.h"
#include <qcustomplot.h>
#include <sstream>

using namespace ModelView;

namespace {

QCPGraph* find_graph_nearby(QCustomPlot* custom_plot, double x, double y)
{
    double widget_px = custom_plot->xAxis->coordToPixel(x);
    double widget_py = custom_plot->yAxis->coordToPixel(y);
    return dynamic_cast<QCPGraph*>(custom_plot->plottableAt(QPointF(widget_px, widget_py)));
}

int getBin(const QCPGraph* graph, double x)
{
    const int key_start = graph->findBegin(x);
    const int key_end = graph->findBegin(x, false); // false = do not expand range
    if (key_end == key_start || key_end == graph->dataCount())
        return key_start;
    return (x - graph->dataSortKey(key_start)) <= (graph->dataSortKey(key_end) - x) ? key_start
                                                                                    : key_end;
}

struct Context {
    double xpos{0.0};
    double ypos{0.0};
    bool close_to_graph{false};
    int nx{0};
    double value{0.0};
};

std::string compose_string(const Context& context)
{
    std::ostringstream ostr;
    ostr << "[x: " << Utils::DoubleToString(context.xpos, 3) << ", ";
    ostr << "y: " << Utils::DoubleToString(context.ypos, 3) << "] ";
    if (context.close_to_graph) {
        ostr << "[binx: " << context.nx << "] ";
        ostr << "[value: " << Utils::ScientificDoubleToString(context.value) << "]";
    }
    return ostr.str();
}

} // namespace

std::string GraphInfoFormatter::status_string(QCustomPlot* custom_plot, double x, double y) const
{
    Context context{x, y};

    if (auto qcp_graph = find_graph_nearby(custom_plot, x, y); qcp_graph) {
        context.close_to_graph = true;
        context.nx = getBin(qcp_graph, x);
        context.value = qcp_graph->dataMainValue(context.nx);
    }

    return compose_string(context);
}
