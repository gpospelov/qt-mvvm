// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_TAGINFO_H
#define MVVM_MODEL_TAGINFO_H

#include <mvvm/model_export.h>
#include <string>
#include <vector>

namespace ModelView
{

//! Holds info about single tag for SessionItem.

class MVVM_MODEL_EXPORT TagInfo
{
public:
    TagInfo();

    TagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes);

    //! Constructs universal tag intended for unlimited amount of various items.
    static TagInfo universalTag(std::string name, std::vector<std::string> modelTypes = {});

    //! Constructs tag intended for single property.
    static TagInfo propertyTag(std::string name, std::string model_type);

    std::string name() const;

    int min() const;

    int max() const;

    std::vector<std::string> modelTypes() const;

    bool maximumReached() const;

    bool isValidChild(const std::string& child) const;

    bool isSinglePropertyTag() const;

    bool operator==(const TagInfo& other) const;
    bool operator!=(const TagInfo& other) const;

private:
    std::string m_name;
    int m_min;
    int m_max;
    std::vector<std::string> m_modelTypes;
};

} // namespace ModelView

#endif // MVVM_MODEL_TAGINFO_H
