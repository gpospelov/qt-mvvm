// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTDATACOLUMN_H
#define IMPORTDATACOLUMN_H

#include "importutils.h"

#include <memory>
#include <string>
#include <vector>

namespace DataImportLogic
{

//! This is the column object for the data
class DataColumn
{
public:
    DataColumn();
    DataColumn(const std::string& header);
    DataColumn(const DataColumn& other);
    ~DataColumn() = default;

    void setValues(const std::vector<std::string>& values);
    void setValues(const std::vector<double>& values);
    void clearValues();
    int rowCount();

    void setName(const std::string& name);
    void setType(const std::string& type);
    void setHeader(const std::string& header);
    void setUnit(const std::string& unit);
    void setColNum(int column_num);
    void setMultiplier(double multiplier);

    std::vector<double> values() const;
    std::vector<double> finalValues() const;
    double value(int row) const;
    double finalValue(int row) const;
    std::string name() const;
    std::string type() const;
    std::string header() const;
    std::string unit() const;
    int colNum() const;
    double multiplier() const;

private:
    std::string m_name;
    std::string m_type;
    std::string m_header;
    std::string m_unit;
    double m_multiplier;
    int m_column_num;
    std::vector<double> m_values;
};

} // end of namespace DataImportLogic

#endif // IMPORTDATACOLUMN_H
