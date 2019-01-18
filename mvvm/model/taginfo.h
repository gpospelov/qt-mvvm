// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TAGINFO_H
#define TAGINFO_H

#include "global.h"
#include <string>
#include <vector>

namespace ModelView {

//! Holds info about single tag for SessionItem.

class CORE_EXPORT TagInfo
{
public:
    TagInfo();

    TagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes);

    //! Returns universal tag intended for unlimited amount of various items.
    static TagInfo universalTag(std::string name);

    //! Returns tag intended for single property.
    static TagInfo propertyTag(std::string name, std::string model_type);

    std::string name() const;

    int min() const;

    int max() const;

    int childCount() const;

    std::vector<std::string> modelTypes() const;

    bool maximumReached() const;

    bool isValidChild(const std::string& child) const;

    void add();

    void remove();

    bool isSinglePropertyTag() const;

private:
    std::string m_name;
    int m_min;
    int m_max;
    int m_childCount;
    std::vector<std::string> m_modelTypes;
};

}  // namespace ModelView

#endif //  TAGINFO_H

