// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QTabWidget>

namespace DataImport
{

class ImportFileWidget;
class ParameterWidget;
class TextSelectionView;
class TableSelectionView;

//! This is the main dialog for the data loader
class DataLoaderDialog : public QDialog
{
public:
    DataLoaderDialog(QWidget* parent = nullptr);
    ~DataLoaderDialog() = default;

private:
    void setUpFileListSpace(QGroupBox* conainer);
    void setUpParameterSpace(QGroupBox* conainer);
    void setUpSelectionSpace(QTabWidget* tab_widget);

private:
    ImportFileWidget* p_import_file_list{nullptr};
    ParameterWidget* p_parameter_dialog{nullptr};
    TextSelectionView* p_text_view{nullptr};
    TableSelectionView* p_table_view{nullptr};
};
}

#endif // IMPORTDIALOG_H