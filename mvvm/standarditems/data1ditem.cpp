// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "data1ditem.h"
#include "axesitems.h"

using namespace ModelView;

Data1DItem::Data1DItem() : CompoundItem(Constants::Data1DItemType)
{
    TagInfo tagInfo(T_AXIS, 0, 1, {Constants::FixedBinAxisType});
    registerTag(tagInfo, /*set_as_default*/ true);
}

//! Sets fixed bin axis. If other axis exists, it will be overriden.
//! Bin content will be set to zero.

void Data1DItem::setFixedBinAxis(int nbins, double xmin, double xmax)
{
    // removing previous axis
    if (auto axis = getItem(T_AXIS, 0))
        delete takeItem(T_AXIS, 0);

    insertItem(FixedBinAxisItem::create(nbins, xmin, xmax).release(), T_AXIS);
    setContent(std::vector<double>(static_cast<size_t>(nbins), 0.0));
}

//! Sets internal data buffer to given data. If size of axis doesn't match the size of the data,
//! exception will be thrown.
#include <QDebug>
void Data1DItem::setContent(const std::vector<double>& data)
{
    if (auto axis = dynamic_cast<FixedBinAxisItem*>(getItem(T_AXIS, 0)); axis) {
        if (axis->binCenters().size() == data.size()) {
            setData(QVariant::fromValue(data), ItemDataRole::DATA);
            return;
        }
     }

    throw std::runtime_error("Data1DItem::setContent() -> Data doesn't match size of axis");
}

//! Returns coordinates of bin centers.

std::vector<double> Data1DItem::binCenters() const
{
    if (auto axis = dynamic_cast<FixedBinAxisItem*>(getItem(T_AXIS, 0)))
        return axis->binCenters();
    else
        return {};
}

//! Returns values stored in bins.

std::vector<double> Data1DItem::binValues() const
{
    auto variant = data(ItemDataRole::DATA);
    return variant.isValid() ? variant.value<std::vector<double>>() : std::vector<double>();
}
