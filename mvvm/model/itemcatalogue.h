// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMCATALOGUE_H
#define ITEMCATALOGUE_H

#include "global.h"
#include <memory>
#include <string>
#include <functional>

namespace ModelView
{

class SessionItem;

//! Catalogue for item constructions.

class ItemCatalogue
{
public:
    using factory_func_t = std::function<SessionItem*()>;

    ItemCatalogue();
    ~ItemCatalogue();

//    template<typename T>
//    void add(const std::string& model_type);

    template<typename T>
    void add();

    bool contains(const std::string& model_type) const;

    std::unique_ptr<SessionItem> create(const std::string& model_type) const;

private:
    void add(const std::string& model_type, factory_func_t func);
    std::unique_ptr<class ItemCatalogueImpl> m_data;
};

//template <typename T>
//void ItemCatalogue::add(const std::string& model_type)
//{
//    add(model_type, []() { return new T(); });
//}

template <typename T>
void ItemCatalogue::add()
{
    T x;
    add(x.modelType(), []() { return new T(); });
}


} // namespace ModelView

#endif // ITEMCATALOGUE_H
