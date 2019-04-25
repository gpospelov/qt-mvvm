#ifndef LAYEREDITORUTILS_H
#define LAYEREDITORUTILS_H

class QStandardItemModel;
class QTableWidget;

namespace LayerEditorUtils
{
QTableWidget* createLayerTable();
QTableWidget* createShrinkedLayerTable();
QTableWidget* createRepetitiveLayerTable();
QStandardItemModel* createMaterialModel();
QStandardItemModel* createTreeLayerModel();
};

#endif // LAYEREDITORUTILS_H
