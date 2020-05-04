// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportTable.h
//! @brief     Defines class CsvImportTable
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IMPORTTABLEVIEW_H
#define IMPORTTABLEVIEW_H

#include "importdatastructure.h"

#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QModelIndex>
#include <vector>

namespace DataImport
{

// -------------------------------------------------
// This is the area for the table model
class ImportTableModel : public QAbstractItemModel
{
    Q_OBJECT
    
public:
    ImportTableModel(QWidget* parent = nullptr);

    void setDataStructure(DataStructure* data_structure);
    DataStructure* dataStructure() const;
    void refreshFromDataStructure();

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int numUtilityRows() const;
    std::vector<InfoTypes> infoTypes() const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    DataStructure* p_data_structure {nullptr};
    bool m_show_name;
    bool m_show_type;
    bool m_show_header;
    bool m_show_units;
    bool m_show_multiplier;

};

// -------------------------------------------------
// This is the area for the table view delegate
class ImportTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ImportTableDelegate(QObject *parent = nullptr);
    ~ImportTableDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};

// -------------------------------------------------
// This is the area for the table view
class ImportTableView : public QTableView
{
    Q_OBJECT

public:
    ImportTableView(QWidget* parent = nullptr);
    ImportTableModel* model() const;

private:

};

}

#endif // IMPORTTABLEVIEW_H
