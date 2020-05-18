// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importutils.h"

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
