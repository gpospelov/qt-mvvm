// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
#define MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H

#include <mvvm/serialization/itemcopystrategy.h>
#include <memory>

namespace ModelView
{

class SessionItem;
class ItemFactoryInterface;

//! Provide SessionItem copying using json based strategy.

class CORE_EXPORT JsonItemCopyStrategy : public ItemCopyStrategy
{
public:
    JsonItemCopyStrategy(const ItemFactoryInterface* item_factory);
    ~JsonItemCopyStrategy();

    std::unique_ptr<SessionItem> createCopy(const SessionItem* item) const;

private:
    struct JsonItemCopyStrategyImpl;
    std::unique_ptr<JsonItemCopyStrategyImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
