// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemcatalogue.h"
#include "ifactory.h"
#include "sessionitem.h"

using namespace ModelView;

class ModelView::ItemCatalogueImpl
{
public:
    IFactory<std::string, SessionItem> factory;
    struct TypeAndLabel {
        std::string item_type;
        std::string item_label;
    };

    std::vector<TypeAndLabel> m_info;
};

ItemCatalogue::ItemCatalogue() : m_data(new ItemCatalogueImpl) {}

ItemCatalogue::ItemCatalogue(const ItemCatalogue& other)
{
    m_data.reset(new ItemCatalogueImpl(*other.m_data.get()));
}

ItemCatalogue& ItemCatalogue::operator=(const ItemCatalogue& other)
{
    if (this != &other) {
        ItemCatalogue tmp(other);
        std::swap(this->m_data, tmp.m_data);
    }
    return *this;
}

void ItemCatalogue::add(const std::string& model_type, ItemCatalogue::factory_func_t func,
                        const std::string& label)
{
    m_data->factory.add(model_type, func);
    m_data->m_info.push_back({model_type, label});
}

ItemCatalogue::~ItemCatalogue() = default;

bool ItemCatalogue::contains(const std::string& model_type) const
{
    return m_data->factory.contains(model_type);
}

std::unique_ptr<SessionItem> ItemCatalogue::create(const std::string& model_type) const
{
    return m_data->factory.create(model_type);
}

std::vector<std::string> ItemCatalogue::modelTypes() const
{
    std::vector<std::string> result;
    for (const auto& x : m_data->m_info)
        result.push_back(x.item_type);
    return result;
}

std::vector<std::string> ItemCatalogue::labels() const
{
    std::vector<std::string> result;
    for (const auto& x : m_data->m_info)
        result.push_back(x.item_label);
    return result;
}

int ItemCatalogue::itemCount() const
{
    return static_cast<int>(m_data->factory.size());
}
