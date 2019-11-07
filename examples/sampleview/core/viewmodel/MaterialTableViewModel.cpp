// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MaterialTableViewModel.h"
#include "MaterialItems.h"
#include <mvvm/viewmodel/childrenstrategyinterface.h>
#include "item_constants.h"
#include <mvvm/model/itemutils.h>
#include <mvvm/viewmodel/rowstrategyinterface.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>
#include <mvvm/viewmodel/viewdataitem.h>

using namespace ModelView;

namespace {
const std::map<std::string, std::function<bool(const ModelView::SessionItem*)>> name_2_filter = {
    {::Constants::SLDMaterialType,
     [](const SessionItem* item) -> bool { return dynamic_cast<const SLDMaterialItem*>(item); }},
    {::Constants::RefIndexMaterialType, [](const SessionItem* item) -> bool {
         return dynamic_cast<const RefIndexMaterialItem*>(item);
     }}
};

//! Acts like standard TopItemsStrategy, but filters out all items
//! according to view model's discriminant.
class FilterChildrenStrategy : public ChildrenStrategyInterface
{
public:
    FilterChildrenStrategy(MaterialTableViewModel* view_model);
    //! Returns vector of children of given item.
    std::vector<SessionItem*> children(const SessionItem* item) const override;

private:
    MaterialTableViewModel* m_view_model;
};

class MaterialTableRowStrategy : public RowStrategyInterface
{
public:
    MaterialTableRowStrategy(MaterialTableViewModel* view_model);
    //! Construct row of QStandardItems from given SessionItem.
    QList<QStandardItem*> constructRow(SessionItem* item) override;

    QStringList horizontalHeaderLabels() const override;

private:
    MaterialTableViewModel* m_view_model;
};

class MaterialViewController : public AbstractViewModelController
{
public:
    MaterialViewController(MaterialTableViewModel* model);
};

QStandardItem* createCheckItem();
} // namespace

MaterialTableViewModel::MaterialTableViewModel(ModelView::SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<MaterialViewController>(this), parent)
    , m_material_type(::Constants::SLDMaterialType)
{
    setSessionModel(model);
}

void MaterialTableViewModel::setMaterialType(const std::string& material_type)
{
    m_material_type = material_type;
    update();
}

/*! Returns material item associated with the particular row.
    Searches for MaterialBaseItem among items associated with
    current view model and their parents. Breaks the search as
    soon as some material item is found.
 */
MaterialBaseItem* MaterialTableViewModel::sessionItemFromRow(int row) const
{
    const auto current_root = sessionItemFromIndex(QModelIndex());
    if (!current_root)
        return nullptr;

    for (int i = 0, n_cols = columnCount(); i < n_cols; ++i){
        QModelIndex i_index = index(row, i, QModelIndex());
        if (!i_index.isValid())
            continue;
        auto current_item = sessionItemFromIndex(i_index);
        while(current_item && current_item != current_root)
            if (auto material = dynamic_cast<MaterialBaseItem*>(current_item))
                return material;
            else
                current_item = current_item->parent();
    }
    return nullptr;
}

namespace {
FilterChildrenStrategy::FilterChildrenStrategy(MaterialTableViewModel* view_model)
    : ChildrenStrategyInterface()
    , m_view_model(view_model)
{}

std::vector<SessionItem*> FilterChildrenStrategy::children(const SessionItem* item) const
{
    std::vector<SessionItem*> result;
    std::string current_material_type = m_view_model->materialType();
    auto filter_iter = name_2_filter.find(current_material_type);
    if (filter_iter == name_2_filter.end())
        throw std::runtime_error(
            "Error in FilterChildrenStrategy::children: unknown material type encountered");

    auto children = item ? Utils::TopLevelItems(*item) : std::vector<SessionItem*>();
    std::copy_if(children.begin(), children.end(), std::back_inserter(result), filter_iter->second);

    return result;
}

MaterialTableRowStrategy::MaterialTableRowStrategy(MaterialTableViewModel* view_model)
    : RowStrategyInterface()
    , m_view_model(view_model)
{}

QList<QStandardItem*> MaterialTableRowStrategy::constructRow(SessionItem* item)
{
    QList<QStandardItem*> result;

    if (!item)
        return result;

    for (auto child : Utils::SinglePropertyItems(*item))
        result.push_back(new ViewDataItem(child));
    result.push_front(createCheckItem());
    return result;
}

QStringList MaterialTableRowStrategy::horizontalHeaderLabels() const
{
    std::unique_ptr<MaterialBaseItem> label_carrier;
    std::string material_type = m_view_model->materialType();
    if (material_type == ::Constants::SLDMaterialType)
        label_carrier = std::make_unique<SLDMaterialItem>();
    else if (material_type == ::Constants::RefIndexMaterialType)
        label_carrier = std::make_unique<RefIndexMaterialItem>();
    else
        throw std::runtime_error("Error in MaterialTableRowStrategy::horizontalHeaderLabels: "
                                 "unknown material type encountered");

    QStringList result;
    for (auto child_item: label_carrier->children()) {
        result.append(QString::fromStdString(child_item->displayName()));
    }

    // adding header for the checkbox column
    result.push_front("Selection");

    return result;
}

MaterialViewController::MaterialViewController(MaterialTableViewModel* model)
    : AbstractViewModelController(model)
{
    setRowStrategy(std::make_unique<MaterialTableRowStrategy>(model));
    setChildrenStrategy(std::make_unique<FilterChildrenStrategy>(model));
}

QStandardItem* createCheckItem()
{
    auto check_item = new QStandardItem();
    check_item->setData(false, Qt::CheckStateRole);
    check_item->setCheckable(true);
    return check_item;
}
} //namespace
