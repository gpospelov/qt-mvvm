// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#ifndef IMPORTLOGIC_H
#define IMPORTLOGIC_H

#include "csvfile.h"
#include "importdatastructure.h"

#include <memory>
#include <QObject>
#include <QColor>

namespace DataImport
{
//! Helper method to split
std::vector<std::string> split(const std::string &s, char delim);
//! Helper method to clean a string vector
void clean(std::vector<std::string>& input);
//! Transpose method to turn lines into columns
string_data transpose(const string_data &input);

//! This is the class holding a text region
class LineFilter
{
public:
    LineFilter(std::string name);
    ~LineFilter() = default;

    //! Public access
    void setSeparators(std::map<std::string, char>* separators); 
    std::vector<std::string> separatorNames() const;
    void processColors(std::vector<std::string> &color_vec) const;
    void processSeparator(std::vector<char> &separator_vec) const;
    void processType(std::vector<std::string> &type_vec) const;

    //! Getters
    const std::string& name() const;
    const bool& active() const;
    const std::string& type() const;
    const std::string& separator() const;
    const std::string& color() const;
    const int& start() const;
    const int& end() const;

    //! Setters
    void setName(std::string);
    void setActive(bool active);
    void setType(std::string type_string);
    void setSeparator(std::string separator_name);
    void setColor(std::string color_string);
    void setStart(int start_line);
    void setEnd(int end_line);

private:
    std::string m_name;
    std::string m_separator_str;
    std::string m_type_string;
    std::string m_color;
    
    std::vector<char> m_ignore_characters;
    std::vector<int> m_ignore_lines;

    bool m_active;
    char m_separator = ' ';

    int m_start_line;
    int m_end_line;

    std::map<std::string, char>* m_separators{nullptr};
};

//! Here sits all the logic for the importation of data
class ImportLogic : public QObject
{
    Q_OBJECT

public:
    ImportLogic();
    ~ImportLogic() = default;

    LineFilter* addLineFilter(std::string name);
    void removeLineFilter(LineFilter* block_ptr);

    std::string getPreview(const int& row) const;
    string_data getData(const int& row) const;
    header_map getHeader(const int& row) const;
    void updateData(const int& row);
    DataStructure* dataStructure() const;

    LineFilter* nameInBlocks(const std::string &name) const;
    LineFilter* typeInBlocks(const std::string &type) const;

public slots:
    void setFiles(std::vector<std::string> file_paths);

private:
    void initSeparators();
    std::vector<std::string> getColorScheme(const int& length) const;
    std::vector<char> getSeparatorScheme(const int& length) const;
    std::vector<std::string> getTypeScheme(const int& length) const;

private:
    std::vector<std::unique_ptr<CSVFile>> m_files;
    std::vector<std::unique_ptr<LineFilter>> m_line_blocks;
    std::map<std::string, char> m_separators;
    std::unique_ptr<DataStructure> p_data_structure;
};

} // namespace DataImport

#endif // IMPORTLOGIC_H