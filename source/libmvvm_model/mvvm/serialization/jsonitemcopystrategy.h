// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
#define MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H

#include "mvvm/interfaces/itemcopystrategy.h"
#include <memory>

namespace ModelView {

class SessionItem;
class ItemFactoryInterface;

//! Provide SessionItem copying using json based strategy.

class MVVM_MODEL_EXPORT JsonItemCopyStrategy : public ItemCopyStrategy {
public:
    JsonItemCopyStrategy(const ItemFactoryInterface* item_factory);
    ~JsonItemCopyStrategy();

    std::unique_ptr<SessionItem> createCopy(const SessionItem* item) const;

private:
    struct JsonItemCopyStrategyImpl;
    std::unique_ptr<JsonItemCopyStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
