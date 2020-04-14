// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvReader.h
//! @brief     Defines class CsvReader
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVREADER_H
#define CSVREADER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

class CSVRow
{
public:
    std::string const& operator[](unsigned index) const;
    unsigned long size() const;
    void readNextRow(std::istream& str);
    void setSeparator(char sep);
    char getSeparator();
    void addCell(std::string str);
    std::vector<std::string> dataVector() { return m_data; }

private:
    std::vector<std::string> m_data;
    char separator = '-';
};

inline std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

class CSVIterator
{
public:
    typedef std::input_iterator_tag iterator_category;
    typedef CSVRow value_type;
    typedef unsigned long difference_type;
    typedef CSVRow* pointer;
    typedef CSVRow& reference;

    CSVIterator(std::istream& str, char sep) : m_str(str.good() ? &str : nullptr)
    {
        m_sep = sep;
        ++(*this);
    }
    CSVIterator() : m_str(nullptr) {}

    // Pre Increment
    CSVIterator& operator++()
    {
        if (m_str) {
            m_row.setSeparator(m_sep);
            if (!((*m_str) >> m_row)) {
                m_str = nullptr;
            }
        }
        return *this;
    }
    // Post increment
    CSVIterator operator++(int)
    {
        CSVIterator tmp(*this);
        ++(*this);
        return tmp;
    }
    CSVRow const& operator*() const { return m_row; }
    CSVRow const* operator->() const { return &m_row; }
    bool operator==(CSVIterator const& rhs)
    {
        return ((this == &rhs) || ((this->m_str == nullptr) && (rhs.m_str == nullptr)));
    }
    bool operator!=(CSVIterator const& rhs) { return !((*this) == rhs); }

private:
    std::istream* m_str;
    CSVRow m_row;
    char m_sep;
};

class CSVFile
{
public:
    CSVFile(std::string path_to_file) : filepath(path_to_file) { Init(); }
    CSVFile(std::string path_to_file, char sep) : filepath(path_to_file), separator(sep) { Init(); }
    CSVFile(std::string path_to_file, char sep, unsigned headRow)
        : filepath(path_to_file), separator(sep), headersRow(headRow)
    {
        Init();
    }

    void Init();
    void Read();
    void EqualizeRowLengths();
    std::vector<std::string> const operator[](unsigned index_i) const;
    unsigned long NumberOfRows() const;
    unsigned long NumberOfColumns() const;
    void set_separator(char sep);
    char get_separator();
    CSVRow get_headers();
    CSVRow get_row(unsigned i);
    std::vector<std::vector<std::string>> asArray() { return m_data; }

private:
    std::string filepath;
    char separator = '-';
    unsigned headersRow = 0;
    unsigned numberOfColumns = 0;
    std::vector<CSVRow> rows;
    std::vector<std::vector<std::string>> m_data;
};

#endif // CSVREADER_H
