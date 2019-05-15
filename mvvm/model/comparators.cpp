#include "comparators.h"
#include "customvariants.h"
#include "comboproperty.h"
#include "externalproperty.h"
#include "reallimits.h"
#include <QMetaType>

using namespace ModelView;

bool Comparators::m_is_registered = false;

void Comparators::registerComparators()
{
    if (!m_is_registered) {
        QMetaType::registerComparators<std::string>();
        QMetaType::registerComparators<std::vector<double>>();
        QMetaType::registerComparators<ComboProperty>();
        QMetaType::registerComparators<ExternalProperty>();
        QMetaType::registerComparators<RealLimits>();
        m_is_registered = true;
    }
}

bool Comparators::registered()
{
    return m_is_registered;
}
