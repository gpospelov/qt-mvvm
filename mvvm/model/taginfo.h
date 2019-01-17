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

    //! Returns default tag (intended for unlimited amount of various items).
    static TagInfo defaultTag(std::string name);

    //! Returns tag inteded for single property.
    static TagInfo propertyTag(std::string name, std::string property_type);

    std::string name() const;

    int min() const;

    int max() const;

    int childCount() const;

    bool maximumReached() const;

    bool isValidChild(const std::string& child) const;

    void add(const std::string& child);

    void remove();

    bool isSingleItemTag() const;

private:
    std::string m_name;
    int m_min;
    int m_max;
    int m_childCount;
    std::vector<std::string> m_modelTypes;
};

}  // namespace ModelView

#endif //  TAGINFO_H

