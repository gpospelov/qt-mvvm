// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/utils/stringutils.h"
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <limits>
#include <sstream>
#include <string_view>

using namespace ModelView;

std::string Utils::DoubleToString(double input, int precision)
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

std::string Utils::ScientificDoubleToString(double input, int precision)
{
    std::ostringstream inter;
    inter << std::scientific;
    inter << std::setprecision(precision);
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

std::string Utils::TrimWhitespace(const std::string& str)
{
    const char whitespace[]{" \t\n"};
    const size_t first = str.find_first_not_of(whitespace);
    if (std::string::npos == first)
        return {};
    const size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

std::string Utils::RemoveRepeatedSpaces(std::string str)
{
    if (str.empty())
        return {};
    auto it = std::unique(str.begin(), str.end(),
                          [](auto x, auto y) { return x == y && std::isspace(x); });
    str.erase(it, str.end());
    return str;
}

std::optional<double> Utils::StringToDouble(const std::string& str)
{
    std::istringstream iss(Utils::TrimWhitespace(str));
    iss.imbue(std::locale::classic());
    double value;
    iss >> value;
    return (!iss.fail() && iss.eof()) ? std::optional<double>(value) : std::optional<double>{};
}

std::optional<int> Utils::StringToInteger(const std::string& str)
{
    std::istringstream iss(Utils::TrimWhitespace(str));
    int value;
    iss >> value;
    return (!iss.fail() && iss.eof()) ? std::optional<int>(value) : std::optional<int>{};
}

std::vector<std::string> Utils::SplitString(const std::string& str, const std::string& delimeter)
{
    // splitting string following Python's str.split()
    if (delimeter.empty())
        throw std::runtime_error("Empty delimeter");
    if (str.empty())
        return {};

    std::vector<std::string> result;
    std::string_view view(str);
    size_t pos{0};

    while ((pos = view.find(delimeter)) != std::string::npos) {
        result.emplace_back(std::string(view.substr(0, pos)));
        view.remove_prefix(pos + delimeter.length());
    }
    result.emplace_back(std::string(view));
    return result;
}

std::vector<double> Utils::ParseSpaceSeparatedDoubles(const std::string& str)
{
    std::vector<double> result;
    ParseSpaceSeparatedDoubles(str, result);
    return result;
}

void Utils::ParseSpaceSeparatedDoubles(const std::string& str, std::vector<double>& result)
{
    std::istringstream iss(str);
    iss.imbue(std::locale::classic());
    std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(),
              back_inserter(result));
}
