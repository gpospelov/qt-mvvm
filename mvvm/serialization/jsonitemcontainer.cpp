// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonitemcontainer.h"
#include "sessionitemcontainer.h"
#include "jsontaginfo.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

namespace
{
QStringList expected_keys();
}

using namespace ModelView;

const QString JsonItemContainer::tagInfoKey = "tagInfo";
const QString JsonItemContainer::itemsKey = "items";

JsonItemContainer::JsonItemContainer()
    : m_taginfo_converter(new JsonTagInfo)
{

}


JsonItemContainer::~JsonItemContainer() = default;

QJsonObject JsonItemContainer::to_json(const SessionItemContainer& itemTag)
{
    QJsonObject result;

    result[tagInfoKey] = m_taginfo_converter->to_json(itemTag.tagInfo());

    QJsonArray itemArray;
    for (auto child : itemTag.children()) {
        QJsonObject child_json;
//        item_to_json(child, child_json);
        itemArray.append(child_json);
    }
    result[itemsKey] = itemArray;

    return result;
}

std::unique_ptr<SessionItemContainer> JsonItemContainer::from_json(const QJsonObject&)
{
    return {};
}

//! Returns true if given object represents SessionItemContainer.

bool JsonItemContainer::isSessionItemContainer(const QJsonObject& object)
{
    static const QStringList expected = expected_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}

namespace
{
QStringList expected_keys()
{
    QStringList result = QStringList() << JsonItemContainer::tagInfoKey << JsonItemContainer::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}
} // namespace
