// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/TableContextMenu.h
//! @brief     Defines class TableContextMenu
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TABLECONTEXTMENU_H
#define TABLECONTEXTMENU_H

#include "CsvNamespace.h"
#include "IUnitConverter.h"
#include <QMenu>
#include <QStringList>
#include <QTableWidget>

class TableContextMenu : public QMenu
{
    Q_OBJECT
public:
    TableContextMenu(QWidget* parent = nullptr);

signals:
    void setFirstRow();
    void setLastRow();
    void setColumnAs(csv::ColumnType);
    void resetTable();
    void discardRow();

private:
    int m_row;
    int m_col;
    QMenu* m_coordSubMenu;
    QAction* m_selectFromThisRowOn;
    QAction* m_selectUntilThisRow;
    QAction* m_resetAction;
    QAction* m_setAsTheta;
    QAction* m_setAsQ;
    QAction* m_setAsIntensity;
    QAction* m_discardRow;
};

#endif // TABLECONTEXTMENU_H
