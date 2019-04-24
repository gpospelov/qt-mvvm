#ifndef LAYEREDITORUTILS_H
#define LAYEREDITORUTILS_H

class QStandardItemModel;
class QTableWidget;

namespace LayerEditorUtils
{
QTableWidget* createLayerTable();
QTableWidget* createShrinkedLayerTable();
QStandardItemModel* createMaterialModel();
};

#endif // LAYEREDITORUTILS_H
