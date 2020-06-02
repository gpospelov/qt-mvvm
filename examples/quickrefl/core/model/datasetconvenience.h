// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DATASETCONVENIENCE_H
#define DATASETCONVENIENCE_H

#include <string>
#include <vector>

// ----------------------------------------------------------------
//! Convenience data transfer header information
struct TypeUnit {
    std::string type;
    std::pair<std::string, std::string> unit_pair;
};

// ----------------------------------------------------------------
//! Convenience data transfer structure
struct RealDataStruct {
public:
    std::string type;
    std::string name;

    std::vector<double> axis;
    std::string axis_name;
    std::string axis_unit;

    std::vector<double> data;
    std::string data_name;
    std::string data_unit;
};

#endif // DATASETCONVENIENCE_H
