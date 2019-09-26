// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CUSTOMPLOT_TEST_UTILS_H
#define CUSTOMPLOT_TEST_UTILS_H

#include <vector>
#include <algorithm>

class QCPGraph;

//! Various common utils for unit tests.

namespace TestUtils
{

//! Returns vector representing bin centers/values on QCPGraph.

template <typename G, typename T> std::vector<double> get_values(const G* graph, T operand)
{
    std::vector<double> result;
    auto graph_data = *graph->data();
    std::transform(std::begin(graph_data), std::end(graph_data), std::back_inserter(result),
                   [operand](const auto& point) { return operand(point); });
    return result;
}

//! Returns vector representing bin centers on QCPgraph.
std::vector<double> binCenters(const QCPGraph* graph);

//! Returns vector representing y-values on QCPgraph.
std::vector<double> binValues(const QCPGraph* graph);

}

#endif
