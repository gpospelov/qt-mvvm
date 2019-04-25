#ifndef LAYEREDITORUTILS_H
#define LAYEREDITORUTILS_H

class QStandardItemModel;
class QTableWidget;
class TreeModel;

namespace LayerEditorUtils
{
QTableWidget* createLayerTable();
QTableWidget* createShrinkedLayerTable();
QTableWidget* createRepetitiveLayerTable();
TreeModel* createCascadeLayerModel();
QStandardItemModel* createMaterialModel();
QStandardItemModel* createTreeLayerModel();
};

#endif // LAYEREDITORUTILS_H
