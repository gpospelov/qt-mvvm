// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_DATA1DITEM_H
#define MVVM_STANDARDITEMS_DATA1DITEM_H

#include "mvvm/model/compounditem.h"
#include "mvvm/model/sessionmodel.h"
#include <vector>

namespace ModelView {

//! Represents one-dimensional data (axis and values).
//! Values are stored in Data1DItem itself, axis is attached as a child. Corresponding plot
//! properties will be served by GraphItem.

class MVVM_MODEL_EXPORT Data1DItem : public CompoundItem {
public:
    static inline const std::string P_VALUES = "P_VALUES";
    static inline const std::string P_ERRORS = "P_ERRORS";
    static inline const std::string T_AXIS = "T_AXIS";

    Data1DItem();

    //    void setAxis(std::unique_ptr<BinnedAxisItem> axis);

    std::vector<double> binCenters() const;

    void setValues(const std::vector<double>& data);
    std::vector<double> binValues() const;

    void setErrors(const std::vector<double>& errors);
    std::vector<double> binErrors() const;

    //! Inserts axis of given type.
    template <typename T, typename... Args> T* setAxis(Args&&... args);
};

// FIXME Consider redesign of the method below. Should the axis exist from the beginning
// or added later? It is not clear how to create axis a) via Data1DItem::setAxis
// b) via model directly c) in constructor?

template <typename T, typename... Args> T* Data1DItem::setAxis(Args&&... args)
{
    // we disable possibility to re-create axis to facilitate undo/redo
    if (getItem(T_AXIS, 0))
        throw std::runtime_error("Axis was already set. Currently we do not support axis change");

    // acting through the model, if model exists, to enable undo/redo
    auto result = model() ? model()->insertItem<T>(this) : insertItem<T>({T_AXIS, 0});
    result->setParameters(std::forward<Args>(args)...);
    setValues(std::vector<double>(result->size(), 0.0));
    return result;
}

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_DATA1DITEM_H
