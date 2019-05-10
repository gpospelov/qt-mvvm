// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractitemcommand.h"

using namespace ModelView;

AbstractItemCommand::AbstractItemCommand()
    : m_is_obsolete(false)
{

}

void AbstractItemCommand::setObsolete(bool flag)
{
    m_is_obsolete = flag;
}

bool AbstractItemCommand::isObsolete() const
{
    return m_is_obsolete;
}

std::string AbstractItemCommand::text() const
{
    return m_text;
}

void AbstractItemCommand::setText(const std::string& text)
{
    m_text = text;
}
