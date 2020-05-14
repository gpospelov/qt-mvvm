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
string_data transpose(const string_data& input);

//! Erase All substrings
void eraseSubStrings(std::string& main_string, const std::vector<std::string>& string_vector);

//! Erase All occurences of substring
void eraseAllSubString(std::string& main_string, const std::string& earase);

}// End of namespace 

#endif // IMPORUTILS_H