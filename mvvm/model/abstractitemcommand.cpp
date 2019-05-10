// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <stdexcept>

using namespace ModelView;

AbstractItemCommand::AbstractItemCommand(SessionItem* context)
    : m_is_obsolete(false), m_model(nullptr)
{
    if (!context)
        throw std::runtime_error("Invalid item.");

    if (!context->model())
        throw std::runtime_error("Item doesn't have a model");

    m_model = context->model();
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
