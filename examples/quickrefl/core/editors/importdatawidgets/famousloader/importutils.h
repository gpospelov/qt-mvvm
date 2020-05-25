// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORUTILS_H
#define IMPORUTILS_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>

namespace DataImportUtils
{
// Convention
using string_data = std::vector<std::vector<std::string>>;
using header_map = std::map<std::string, int>;

// global constants
enum InfoTypes { Name, Type, Unit, Multiplier, Header };
const std::vector<std::string> InfoNames{"Name", "Type", "Unit", "Multiplier", "Header"};
const std::vector<std::string> Types{"Intensity", "Axis"};
const std::vector<std::string> Units{"a.u.", "counts", "bin", "rad", "deg", "mm", "1/nm"};

//! Helper method to split
std::vector<std::string> split(const std::string& s, char delim);

//! Helper method to clean a string vector
void clean(std::vector<std::string>& input);

//! Transpose method to turn lines into columns
template <typename T> T transpose(const T& input)
{
    T temp_data;
    if (input.size() == 0)
        return temp_data;

    std::vector<size_t> row_size(input.size());
    for (int i = 0; i < input.size(); ++i) {
        row_size[i] = input.at(i).size();
    }
    size_t max = *std::max_element(row_size.begin(), row_size.end());

    for (int i = 0; i < *std::max_element(row_size.begin(), row_size.end()); ++i) {
        typename T::value_type column(input.size());
        for (int j = 0; j < input.size(); ++j) {
            if (i < row_size[j])
                column[j] = input.at(j).at(i);
        }
        temp_data.push_back(column);
    }
    return temp_data;
}

//! Erase All substrings
void eraseSubStrings(std::string& main_string, const std::vector<std::string>& string_vector);

//! Erase All occurences of substring
void eraseAllSubString(std::string& main_string, const std::string& earase);

}// End of namespace 

#endif // IMPORUTILS_H
