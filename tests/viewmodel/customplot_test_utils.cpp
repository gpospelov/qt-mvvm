// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "customplot_test_utils.h"
#include <qcustomplot.h>


std::vector<double> TestUtils::binCenters(const QCPGraph* graph)
{
    return get_values(graph, [](auto x) { return x.key; });
}

std::vector<double> TestUtils::binValues(const QCPGraph* graph)
{
    return get_values(graph, [](auto x) { return x.value; });
}
