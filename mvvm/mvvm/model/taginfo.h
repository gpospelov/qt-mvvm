// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_TAGINFO_H
#define MVVM_TAGINFO_H

#include <mvvm/model/mvvm_export.h>
#include <string>
#include <vector>

namespace ModelView
{

//! Holds info about single tag for SessionItem.

class CORE_EXPORT TagInfo
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

    std::string toString() const;

private:
    std::string m_name;
    int m_min;
    int m_max;
    std::vector<std::string> m_modelTypes;
};

} // namespace ModelView

#endif //  MVVM_TAGINFO_H
