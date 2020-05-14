// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importutils.h"

#include <algorithm>
#include <functional>
#include <sstream>

namespace DataImportUtils
{

//! Standard function to handle spinting
std::vector<std::string> split(const std::string& s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//! Cleans the vector of strings provided by removing empty parts
void clean(std::vector<std::string>& input)
{
    std::vector<std::string>::iterator i = input.begin();
    while (i != input.end()) {
        if (*i == "") {
            i = input.erase(i);
        } else {
            ++i;
        }
    }
}

//! Transpose the current data array
string_data transpose(const string_data& output)
{
    string_data temp_data;
    if (output.size() == 0)
        return temp_data;

    std::vector<size_t> row_size(output.size());
    for (int i = 0; i < output.size(); ++i) {
        row_size[i] = output.at(i).size();
    }
    size_t max = *std::max_element(row_size.begin(), row_size.end());

    for (int i = 0; i < *std::max_element(row_size.begin(), row_size.end()); ++i) {
        std::vector<std::string> column(output.size(), "");
        for (int j = 0; j < output.size(); ++j) {
            if (i < row_size[j])
                column[j] = output.at(j).at(i);
        }
        temp_data.push_back(column);
    }
    return temp_data;
}

//! Erase All substrings
void eraseSubStrings(std::string& main_string, const std::vector<std::string>& string_vector)
{
    std::for_each(string_vector.begin(), string_vector.end(),
                  std::bind(eraseAllSubString, std::ref(main_string), std::placeholders::_1));
}

//! Erase All occurences of substring
void eraseAllSubString(std::string& main_string, const std::string& to_erase)
{
    if (to_erase == "")
        return;

    // Search for the substring in string in a loop untill nothing is found
    for (std::string::size_type i = main_string.find(to_erase); i != std::string::npos;
         i = main_string.find(to_erase)) {
        // If found then erase it from string
        main_string.erase(i, to_erase.length());
    }
}

}// End of namespace 
