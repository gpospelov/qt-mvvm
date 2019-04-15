#include "materialmodel.h"

MaterialModel::MaterialModel(QObject* parent)
    :QAbstractTableModel (parent)
    , m_type_filter(MaterialItem::SLD)
{
    MaterialItem air(MaterialItem::SLD);
    air.setName("air");
    m_data.append(air);

    MaterialItem substrate(MaterialItem::SLD);
    air.setName("substrate");
    m_data.append(substrate);
}

int MaterialModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_data.size());
}

int MaterialModel::columnCount(const QModelIndex&) const
{
    return MaterialItem::size;
}

QVariant MaterialModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_data.size() || index.row() < 0)
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    const auto& material = m_data.at(index.row());
    return material.property(index.column());
}

QVariant MaterialModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation != Qt::Horizontal)
        return QVariant();
    return MaterialItem::propertyName(section, m_type_filter);
}
