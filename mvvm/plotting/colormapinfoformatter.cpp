// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapinfoformatter.h"
#include "qcustomplot.h"
#include <iomanip>
#include <sstream>

using namespace ModelView;

namespace
{
QCPColorMap* find_colormap(QCustomPlot* custom_plot)
{
    for (int i = 0; i < custom_plot->plottableCount(); ++i) {
        if (auto plottable = dynamic_cast<QCPColorMap*>(custom_plot->plottable()); plottable)
            return plottable;
    }

    return nullptr;
}

std::string printDouble(double input, int precision = 12)
{
    std::ostringstream inter;
    inter << std::setprecision(precision);
    if (std::abs(input) < std::numeric_limits<double>::epsilon()) {
        inter << "0.0";
        return inter.str();
    }
    inter << input;
    if (inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
        inter << ".0";
    return inter.str();
}

// 1.000000e+07 -> 1.0e+07
std::string printScientificDouble(double input)
{
    std::ostringstream inter;
    inter << std::scientific;
    inter << input;

    std::string::size_type pos = inter.str().find('e');
    if (pos == std::string::npos)
        return inter.str();

    std::string part1 = inter.str().substr(0, pos);
    std::string part2 = inter.str().substr(pos, std::string::npos);

    part1.erase(part1.find_last_not_of('0') + 1, std::string::npos);
    if (part1.back() == '.')
        part1 += "0";

    return part1 + part2;
}

struct Context {
    double xpos{0.0};
    double ypos{0.0};
    int nx{0};
    int ny{0};
    double value{0.0};
};

std::string compose_string(const Context& context)
{
    std::ostringstream ostr;
    ostr << "[x: " << printDouble(context.xpos, 3) << ", ";
    ostr << "y: " << printDouble(context.ypos, 3) << "] ";
    ostr << "[binx: " << context.nx << ", ";
    ostr << "biny: " << context.ny << "] ";
    ostr << "[value: " << printScientificDouble(context.value) << "]";
    return ostr.str();
}

} // namespace

std::string ColorMapInfoFormatter::status_string(QCustomPlot* custom_plot, double x, double y) const
{
    // FIXME provide caching
    auto color_map = find_colormap(custom_plot);
    Context context{x, y};

    color_map->data()->coordToCell(x, y, &context.nx, &context.ny);

    context.value = color_map->data()->cell(context.nx, context.ny);
    return compose_string(context);
}
