// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/ImportTableView.cpp
//! @brief     Implements class ImportTableView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "importtableview.h"
#include "importdatacolumn.h"

#include <mvvm/editors/scientificspinboxeditor.h>

#include <QComboBox>
#include <QHeaderView>
#include <QLineEdit>
#include <algorithm>

namespace DataImportGui
{

// -------------------------------------------------
// This is the area for the table model

//! This is the constructor
ImportTableModel::ImportTableModel(QWidget* parent)
    : QAbstractItemModel(parent), m_show_name(true), m_show_type(true), m_show_header(true),
      m_show_units(true), m_show_multiplier(true)
{
}

//! This is the column count (override of pure virtual)
void ImportTableModel::setDataStructure(DataImportLogic::DataStructure* data_structure)
{
    p_data_structure = data_structure;
    refreshFromDataStructure();
}

//! Getter for the current data structure
DataImportLogic::DataStructure* ImportTableModel::dataStructure() const
{
    return p_data_structure;
}

//! This is the column count (override of pure virtual)
void ImportTableModel::refreshFromDataStructure()
{
    beginResetModel();
    endResetModel();
}

//! This is the column count (override of pure virtual)
int ImportTableModel::columnCount(const QModelIndex& /*parent*/) const
{
    return (p_data_structure == nullptr) ? (0) : (p_data_structure->columnCount());
}

//! This is the row count (override of pure virtual)
int ImportTableModel::rowCount(const QModelIndex& /*parent*/) const
{
    int extra_lines = m_show_name + m_show_type + m_show_header + m_show_units + m_show_multiplier;
    return (p_data_structure == nullptr) ? (numUtilityRows())
                                         : (p_data_structure->rowCount() + numUtilityRows());
}

//! Get the number of utility lines
int ImportTableModel::numUtilityRows() const
{
    return m_show_name + m_show_type + m_show_header + m_show_units + m_show_multiplier;
}

//! Get the vector of visible info types
std::vector<DataImportUtils::InfoTypes> ImportTableModel::infoTypes() const
{
    std::vector<DataImportUtils::InfoTypes> info_types;
    if (m_show_name)
        info_types.push_back(DataImportUtils::InfoTypes::Name);
    if (m_show_type)
        info_types.push_back(DataImportUtils::InfoTypes::Type);
    if (m_show_units)
        info_types.push_back(DataImportUtils::InfoTypes::Unit);
    if (m_show_multiplier)
        info_types.push_back(DataImportUtils::InfoTypes::Multiplier);
    if (m_show_header)
        info_types.push_back(DataImportUtils::InfoTypes::Header);
    return info_types;
}

//! This is the index processing for a row, col and parent (override of pure virtual)
QModelIndex ImportTableModel::index(int row, int column, const QModelIndex& /*parent*/) const
{
    return createIndex(row, column);
}

//! This is the index processing for a row, col and parent (override of pure virtual)
QModelIndex ImportTableModel::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

//! The flags
Qt::ItemFlags ImportTableModel::flags(const QModelIndex& index) const
{
    int utility_lines = numUtilityRows();
    if (index.row() >= utility_lines) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    } else {
        std::vector<Qt::ItemFlags> flags;
        if (m_show_name)
            flags.push_back(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        if (m_show_type)
            flags.push_back(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        if (m_show_units)
            flags.push_back(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        if (m_show_multiplier)
            flags.push_back(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        if (m_show_header)
            flags.push_back(Qt::ItemIsEnabled);
        return flags.at(index.row());
    }
}

//! This is the data getter implementation (override of pure virtual)
QVariant ImportTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (p_data_structure == nullptr)
        return QVariant();

    DataImportLogic::DataColumn* column = p_data_structure->column(index.column());
    int utility_lines = numUtilityRows();
    if (index.row() >= utility_lines && index.row() < column->rowCount() + utility_lines) {
        if (role == Qt::DisplayRole)
            return QVariant(column->finalValue(index.row() - utility_lines));
    } else if (index.row() < utility_lines) {
        if (role == Qt::DisplayRole) {
            std::vector<QVariant> values;
            if (m_show_name)
                values.push_back(QVariant(QString::fromStdString(column->name())));
            if (m_show_type)
                values.push_back(QVariant(QString::fromStdString(column->type())));
            if (m_show_units)
                values.push_back(QVariant(QString::fromStdString(column->unit())));
            if (m_show_multiplier)
                values.push_back(QVariant(column->multiplier()));
            if (m_show_header)
                values.push_back(QVariant(QString::fromStdString(column->header())));
            return values.at(index.row());
        }
        if (role == Qt::BackgroundRole) {
            return QBrush(Qt::gray);
        }
        if (role == Qt::TextAlignmentRole) {
            return Qt::AlignCenter;
        }
        if (role == Qt::ToolTipRole) {
            std::vector<QVariant> tooltips;
            if (m_show_name)
                tooltips.push_back(QVariant(
                    QString("The name of the column that will be displayed in the loaded data")));
            if (m_show_type)
                tooltips.push_back(QVariant(QString("The import type of the data")));
            if (m_show_units)
                tooltips.push_back(QVariant(QString("The unit type of the data")));
            if (m_show_multiplier)
                tooltips.push_back(QVariant(QString("The multiplier for the data")));
            if (m_show_header)
                tooltips.push_back(
                    QVariant(QString("The identified Header from the selection rules")));
            return tooltips.at(index.row());
        }
    }

    return QVariant();
}

//! This is the data setter implementation (TODO)
bool ImportTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{

    return true;
}

QVariant ImportTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
        return QVariant();

    if (p_data_structure == nullptr)
        return QVariant();

    int utility_lines = numUtilityRows();
    auto info_types = infoTypes();
    if (section >= utility_lines && section < rowCount()) {
        if (role == Qt::DisplayRole)
            return QVariant(section - utility_lines);
    } else if (section < utility_lines) {
        if (role == Qt::DisplayRole) {
            if (info_types.at(section) == DataImportUtils::InfoTypes::Name) {
                return QVariant("Name");
            }
            if (info_types.at(section) == DataImportUtils::InfoTypes::Type) {
                return QVariant("Type");
            }
            if (info_types.at(section) == DataImportUtils::InfoTypes::Unit) {
                return QVariant("Unit");
            }
            if (info_types.at(section) == DataImportUtils::InfoTypes::Header) {
                return QVariant("Header");
            }
            if (info_types.at(section) == DataImportUtils::InfoTypes::Multiplier) {
                return QVariant("Multiplier");
            }
        }
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

// -------------------------------------------------
// This is the area for the table view delegate

//! This is the constructor
ImportTableDelegate::ImportTableDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

//! This is the destructor
ImportTableDelegate::~ImportTableDelegate() {}

//! Create the initial widget
QWidget* ImportTableDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                           const QModelIndex& index) const
{
    const ImportTableModel* model = dynamic_cast<const ImportTableModel*>(index.model());
    int utility_rows = model->numUtilityRows();
    if (index.row() < utility_rows) {
        std::vector<DataImportUtils::InfoTypes> info_types = model->infoTypes();
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Name) {
            QLineEdit* line_edit = new QLineEdit(parent);
            line_edit->setAlignment(Qt::AlignCenter);
            return line_edit;
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Type) {
            QComboBox* combo_box = new QComboBox(parent);
            QList<QString> items;
            std::for_each(
                DataImportUtils::Types.begin(), DataImportUtils::Types.end(),
                [&](const std::string& type) { items.append(QString::fromStdString(type)); });
            combo_box->addItems(items);
            return combo_box;
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Unit) {
            QComboBox* combo_box = new QComboBox(parent);
            QStringList items;
            std::for_each(
                DataImportUtils::Units.begin(), DataImportUtils::Units.end(),
                [&](const std::string& unit) { items.append(QString::fromStdString(unit)); });
            combo_box->addItems(items);
            return combo_box;
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Multiplier) {
            ModelView::ScientificSpinBoxEditor* spin_box =
                new ModelView::ScientificSpinBoxEditor(parent);
            return spin_box;
        }
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

//! Set the actual data of the widget
void ImportTableDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    const ImportTableModel* model = dynamic_cast<const ImportTableModel*>(index.model());
    int utility_rows = model->numUtilityRows();
    DataImportLogic::DataColumn* column = (model->dataStructure() == nullptr)
                                              ? (nullptr)
                                              : (model->dataStructure()->column(index.column()));

    if (!column)
        return;

    if (index.row() < utility_rows) {
        std::vector<DataImportUtils::InfoTypes> info_types = model->infoTypes();
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Name) {
            QLineEdit* line_edit = dynamic_cast<QLineEdit*>(editor);
            line_edit->setText(QString::fromStdString(column->name()));
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Type) {
            QComboBox* combo_box = dynamic_cast<QComboBox*>(editor);
            combo_box->setCurrentText(QString::fromStdString(column->type()));
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Unit) {
            QComboBox* combo_box = dynamic_cast<QComboBox*>(editor);
            combo_box->setCurrentText(QString::fromStdString(column->unit()));
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Multiplier) {
            ModelView::ScientificSpinBoxEditor* spin_box =
                dynamic_cast<ModelView::ScientificSpinBoxEditor*>(editor);
            spin_box->setData(column->multiplier());
        }
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

//! Send the widget data to the model
void ImportTableDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                       const QModelIndex& index) const
{
    const ImportTableModel* table_model = dynamic_cast<const ImportTableModel*>(model);
    int utility_rows = table_model->numUtilityRows();
    DataImportLogic::DataColumn* column =
        (table_model->dataStructure() == nullptr)
            ? (nullptr)
            : (table_model->dataStructure()->column(index.column()));

    if (!column)
        return;

    if (index.row() < utility_rows) {
        std::vector<DataImportUtils::InfoTypes> info_types = table_model->infoTypes();
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Name) {
            QLineEdit* line_edit = dynamic_cast<QLineEdit*>(editor);
            auto text = line_edit->text().toStdString();
            column->setName(text);
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Type) {
            QComboBox* combo_box = dynamic_cast<QComboBox*>(editor);
            auto text = combo_box->currentText().toStdString();
            column->setType(text);
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Unit) {
            QComboBox* combo_box = dynamic_cast<QComboBox*>(editor);
            auto text = combo_box->currentText().toStdString();
            column->setUnit(text);
        }
        if (info_types.at(index.row()) == DataImportUtils::InfoTypes::Multiplier) {
            ModelView::ScientificSpinBoxEditor* spin_box =
                dynamic_cast<ModelView::ScientificSpinBoxEditor*>(editor);
            column->setMultiplier(spin_box->data().value<double>());
        }
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

// -------------------------------------------------
// This is the area for the table view

//! This is the constructor
ImportTableView::ImportTableView(QWidget* parent) : QTableView(parent)
{
    setModel(new ImportTableModel(this));
    setItemDelegate(new ImportTableDelegate(this));
    verticalHeader()->setMaximumWidth(100);
}

//! override the view to avoid writing dynamic casts elsewhere
ImportTableModel* ImportTableView::model() const
{
    return dynamic_cast<ImportTableModel*>(QTableView::model());
}

} // namespace DataImportGui
