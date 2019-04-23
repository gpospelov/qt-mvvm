#include "treeitem.h"

namespace {
	QVector<QVariant> defaultLayerData()
	{
		/*layer_name, material_name, thickness, roughness*/
		return { "layer", "default", 0.0, 0.0 };
	}

	QVector<QVariant> defaultAssemblyData()
	{
		/*assembly_name, number_of_repetitions*/
		return { "assembly", 1 };
	}
}

TreeItem::TreeItem(TYPE type, const QVector<QVariant>& data, TreeItem* parent)
	: m_type(type)
	, itemData(data)
	, parentItem(parent)
{}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

TreeItem* TreeItem::parent() const
{
    return parentItem;
}

TreeItem* TreeItem::child(int number)
{
    return childItems.value(number);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

bool TreeItem::setData(int column, const QVariant& value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

LayerItem::LayerItem(TreeItem* parent)
	: TreeItem(TYPE::Layer, defaultLayerData(), parent)
{}

AssemblyItem::AssemblyItem(TreeItem* parent)
	: TreeItem(TYPE::Assembly, defaultAssemblyData(), parent)
{}

bool AssemblyItem::insertChildren(int position, int count, TYPE type)
{
	if (position < 0 || position > childItems.size())
		return false;

	for (int row = 0; row < count; ++row) {
		TreeItem* item = nullptr;
		switch (type) {
		case TYPE::Layer:
			item = new LayerItem(this);
			break;
		case TYPE::Assembly:
			item = new AssemblyItem(this);
			break;
		default:
			throw std::runtime_error("TreeItem::insertChildren: unexpected item type.");
		}
		childItems.insert(position, item);
	}

	return true;
}
