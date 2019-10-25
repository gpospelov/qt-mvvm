// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "customplotutils.h"
#include <qcustomplot.h>

void ModelView::Utils::SetLogarithmicScale(QCPColorScale* axis, bool is_log_scale)
{
    if (is_log_scale && axis->dataScaleType() != QCPAxis::stLogarithmic)
        axis->setDataScaleType(QCPAxis::stLogarithmic);

    else if (!is_log_scale && axis->dataScaleType() != QCPAxis::stLinear)
        axis->setDataScaleType(QCPAxis::stLinear);

    SetLogarithmicScale(axis->axis(), is_log_scale);
}

void ModelView::Utils::SetLogarithmicScale(QCPAxis* axis, bool is_log_scale)
{
    if (is_log_scale) {
        axis->setNumberFormat("eb");
        axis->setNumberPrecision(0);
        axis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTickerLog);
        axis->setTicker(ticker);
    } else {
        axis->setNumberFormat("f");
        axis->setNumberPrecision(0);
        axis->setScaleType(QCPAxis::stLinear);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
        axis->setTicker(ticker);
    }
}
