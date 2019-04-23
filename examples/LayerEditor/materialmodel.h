#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "materialitem.h"
#include <QAbstractItemModel>

class MaterialModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MaterialModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

private:
    QList<MaterialItem> m_data;
    MaterialItem::DATA_TYPE m_type_filter;
};

#endif // MATERIALMODEL_H
