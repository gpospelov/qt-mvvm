#include "comparators.h"
#include "customvariants.h"
#include <QMetaType>

bool Comparators::m_is_registered = false;

void Comparators::registerComparators()
{
    if (!m_is_registered) {
        QMetaType::registerComparators<std::string>();
        QMetaType::registerComparators<std::vector<double>>();
        m_is_registered = true;
    }
}

bool Comparators::registered()
{
    return m_is_registered;
}
