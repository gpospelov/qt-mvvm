#include "materialmodel.h"
#include <QStandardItemModel>

/*MaterialModel::MaterialModel(QObject* parent)
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
}*/

#include <QPixmap>
namespace {
    QStandardItem* createColorMapItem(Qt::GlobalColor color)
    {
        QPixmap color_pixmap(20,20);
        color_pixmap.fill(QColor(color));
        QStandardItem* item = new QStandardItem();
        item->setData(QVariant(color_pixmap), Qt::DecorationRole);
        return item;
    }
}

QStandardItemModel* MaterialModel::create()
{
    auto model = new QStandardItemModel(3, 4);

    // header
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Re(SLD)");
    model->setHeaderData(2, Qt::Horizontal, "Im(SLD)");
    model->setHeaderData(3, Qt::Horizontal, "Color");

    // row 0
    model->setItem(0, 0, new QStandardItem("air"));
    model->setItem(0, 1, new QStandardItem("0.0"));
    model->setItem(0, 2, new QStandardItem("0.0"));
    model->setItem(0, 3, createColorMapItem(Qt::yellow));

    // row 1
    model->setItem(1, 0, new QStandardItem("mat1"));
    model->setItem(1, 1, new QStandardItem("1.0"));
    model->setItem(1, 2, new QStandardItem("0.1"));
    model->setItem(1, 3, createColorMapItem(Qt::darkBlue));

    // row 2
    model->setItem(2, 0, new QStandardItem("sub"));
    model->setItem(2, 1, new QStandardItem("0.5"));
    model->setItem(2, 2, new QStandardItem("0.01"));
    model->setItem(2, 3, createColorMapItem(Qt::green));

    return model;
}
