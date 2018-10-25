// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONITEMTAGS_H
#define SESSIONITEMTAGS_H

#include "global.h"
#include <string>
#include <vector>

namespace ModelView {

//! Holds all tag info for SessionItem.

class CORE_EXPORT SessionItemTags
{
public:
    bool registerTag(const std::string& name, int min, int max,
                     const std::vector<std::string>& modelTypes);

    bool isValid(const std::string& tagName, const std::string& modelType = {}) const;

    std::vector<std::string> modelTypesForTag(const std::string& tagName) const;

    int tagStartIndex(const std::string& tagName) const;

    int indexFromTagRow(const std::string& tagName, int row) const;
    int insertIndexFromTagRow(const std::string& tagName, int row);

    std::string tagFromIndex(int index) const;

    int childCount(const std::string& tagName);
    int childMax(const std::string& tagName);

    void addChild(const std::string& tagName);
    void removeChild(const std::string& tagName);

    bool isSingleItemTag(const std::string& tagName);

    bool maximumReached(const std::string& tagName) const;

private:
    class TagInfo
    {
    public:
        TagInfo();
        std::string name;
        int min;
        int max;
        int childCount;
        std::vector<std::string> modelTypes;
    };

    TagInfo& tagInfo(const std::string& tagName);
    const TagInfo& tagInfo(const std::string& tagName) const;

    std::vector<TagInfo> m_tags;
};

}  // namespace ModelView

#endif //  SESSIONITEMTAGS_H
