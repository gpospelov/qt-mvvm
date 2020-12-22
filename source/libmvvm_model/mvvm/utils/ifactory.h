// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_IFACTORY_H
#define MVVM_UTILS_IFACTORY_H

#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace ModelView {

//! Base for factories.

template <class Key, class Value> class IFactory {
public:
    using function_t = std::function<std::unique_ptr<Value>()>;
    using map_t = std::map<Key, function_t>;

    bool contains(const Key& item_key) const { return m_data.find(item_key) != m_data.end(); }

    std::unique_ptr<Value> create(const Key& item_key) const
    {
        auto it = m_data.find(item_key);
        if (it == m_data.end()) {
            std::ostringstream message;
            message << "IFactory::createItem() -> Error. Unknown item key '" << item_key << "'";
            throw std::runtime_error(message.str());
        }
        return it->second();
    }

    bool add(const Key& key, function_t func)
    {
        if (m_data.find(key) != m_data.end()) {
            std::ostringstream message;
            message << "IFactory::createItem() -> Already registered item key '" << key << "'";
            throw std::runtime_error(message.str());
        }
        return m_data.insert(make_pair(key, func)).second;
    }

    size_t size() const { return m_data.size(); }

    typename map_t::iterator begin() { return m_data.begin(); }
    typename map_t::iterator end() { return m_data.end(); }

private:
    map_t m_data;
};

} // namespace ModelView

#endif // MVVM_UTILS_IFACTORY_H
