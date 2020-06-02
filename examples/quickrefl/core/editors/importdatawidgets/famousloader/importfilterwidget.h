// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTFILTERWIDGET_H
#define IMPORTFILTERWIDGET_H

#include <QWidget>
#include <vector>

#include "importlogic.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QSettings;
QT_END_NAMESPACE

namespace DataImportLogic
{
class ImportLogic;
}

namespace DataImportGui
{

class LineFilterWidget;

//! This is the main dialog for the data loader
class ImportFilterWidget : public QWidget
{
    Q_OBJECT

public:
    ImportFilterWidget(DataImportLogic::ImportLogic* import_logic, QWidget* parent = nullptr);
    ~ImportFilterWidget() = default;

    void addLineFilter();
    void removeLineFilter();
    
    void readSettings();
    void writeSettings();

signals:
    void parameterChanged();
    void namesChanged();
    void typesChanged();

private slots:
    void processNameChanged(std::string name, LineFilterWidget* widget);
    void processTypeChanged(std::string type, LineFilterWidget* widget);

private:
    void setLayout();
    void initialise();
    void connectAll();
    void resetFromLineFilters() const;
    void handleInternalMoveEvent();

private:
    DataImportLogic::ImportLogic* p_import_logic;

    std::vector<LineFilterWidget*> m_line_filter_widgets;
    QListWidget* p_list_widget;
};

} // End of namespace DataImportGui

#endif // IMPORTFILTERWIDGET_H