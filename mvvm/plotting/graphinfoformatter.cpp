// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphinfoformatter.h"
#include "stringutils.h"
#include <sstream>

using namespace ModelView;

namespace
{

struct Context {
    double xpos{0.0};
    double ypos{0.0};
    int nx{0};
    double value{0.0};
};

std::string compose_string(const Context& context)
{
    std::ostringstream ostr;
    ostr << "[x: " << Utils::DoubleToString(context.xpos, 3) << ", ";
    ostr << "y: " << Utils::DoubleToString(context.ypos, 3) << "] ";
    ostr << "[binx: " << context.nx << "] ";
    ostr << "[value: " << Utils::ScientificDoubleToString(context.value) << "]";
    return ostr.str();
}

} // namespace

std::string GraphInfoFormatter::status_string(QCustomPlot* /*custom_plot*/, double x,
                                              double y) const
{
    Context context{x, y};

    return compose_string(context);
}
