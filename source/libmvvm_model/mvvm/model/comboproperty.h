// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_COMBOPROPERTY_H
#define MVVM_MODEL_COMBOPROPERTY_H

#include "mvvm/core/variant.h"
#include "mvvm/model_export.h"
#include <string>
#include <vector>

namespace ModelView {

//! Custom property to define list of string values with multiple selections.

class MVVM_MODEL_EXPORT ComboProperty {
public:
    ComboProperty();

    static ComboProperty createFrom(const std::vector<std::string>& values,
                                    const std::string& current_value = {});

    std::string value() const;
    void setValue(const std::string& name);

    std::vector<std::string> values() const;
    void setValues(const std::vector<std::string>& values);

    std::vector<std::string> toolTips() const;
    void setToolTips(const std::vector<std::string>& tooltips);

    int currentIndex() const;
    void setCurrentIndex(int index);

    ComboProperty& operator<<(const std::string& str);
    ComboProperty& operator<<(const std::vector<std::string>& str);
    bool operator==(const ComboProperty& other) const;
    bool operator!=(const ComboProperty& other) const;
    bool operator<(const ComboProperty& other) const;

    std::string stringOfValues() const;
    void setStringOfValues(const std::string& values);

    std::vector<int> selectedIndices() const;
    std::vector<std::string> selectedValues() const;

    void setSelected(int index, bool value = true);
    void setSelected(const std::string& name, bool value = true);

    std::string stringOfSelections() const;
    void setStringOfSelections(const std::string& values);

    std::string label() const;

private:
    ComboProperty(std::vector<std::string> values);

    std::vector<std::string> m_values;
    std::vector<std::string> m_tooltips;
    std::vector<int> m_selected_indices;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::ComboProperty)

#endif // MVVM_MODEL_COMBOPROPERTY_H
