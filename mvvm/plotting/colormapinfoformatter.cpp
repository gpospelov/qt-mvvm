// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapinfoformatter.h"
#include <sstream>

using namespace ModelView;

std::string ColorMapInfoFormatter::status_string(QCustomPlot* /*custom_plot*/, double x,
                                                 double y) const
{
    std::ostringstream ostr;
    ostr << "xxx " << x << " " << y;
    return ostr.str();
}
