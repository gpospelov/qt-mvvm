// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTDATASTRUCTURE_H
#define IMPORTDATASTRUCTURE_H

#include "importutils.h"
#include "importdatacolumn.h"

#include <memory>
#include <string>
#include <vector>

namespace DataImportLogic
{

class DataColumn;

//! This will manage all the column objects
class DataStructure
{
public:
    DataStructure();
    ~DataStructure() = default;

    void setData(DataImportUtils::string_data& data);
    void setData(DataImportUtils::header_map& headers, DataImportUtils::string_data& data);
    
    DataColumn* column(const std::string& header);
    const DataColumn* column(int column) const;
    DataColumn* column(int column);

    int rowCount() const;
    int columnCount() const;

private:    
    void processHeaders(int num);
    void processHeaders(const std::vector<std::string>& headers);
    std::vector<bool> checkHeaders(const std::vector<std::string>& headers);
    void addColumn(const std::string& header);
    void delColumn(const std::string& header);
    void clearColumnValues();

private:
    std::vector<std::unique_ptr<DataColumn>> m_data_columns;
};

} // end of namespace DataImportLogic

#endif // IMPORTDATASTRUCTURE_H
