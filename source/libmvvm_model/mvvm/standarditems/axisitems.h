// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_AXISITEMS_H
#define MVVM_STANDARDITEMS_AXISITEMS_H

//! @file axisitems.h
//! Collection of axis items for 1D and 2D data/plotting support.

#include "mvvm/model/compounditem.h"
#include <memory>
#include <vector>

namespace ModelView {

//! Base class for all axes items. Has min, max defined, but nothing else.

class MVVM_MODEL_EXPORT BasicAxisItem : public CompoundItem {
public:
    static inline const std::string P_MIN = "P_MIN";
    static inline const std::string P_MAX = "P_MAX";

    explicit BasicAxisItem(const std::string& model_type);

protected:
    void register_min_max();
};

//! Item to represent viewport axis.
//! Serves as a counterpart of QCPAxis from QCustomPlot. Intended to cary title, fonts etc.

class MVVM_MODEL_EXPORT ViewportAxisItem : public BasicAxisItem {
public:
    static inline const std::string P_TITLE = "P_TITLE";
    static inline const std::string P_IS_LOG = "P_IS_LOG";
    explicit ViewportAxisItem(const std::string& model_type = Constants::ViewportAxisItemType);

    std::pair<double, double> range() const;

    void set_range(double lower, double upper);

    bool is_in_log() const;
};

//! Item to represent an axis with arbitrary binning.
//! Base class to define an axis with specific binning (fixed, variable). Used in Data1DItem and
//! Data2Ditem to store 1d and 2d data.  Doesn't carry any appearance info (e.g. axis title, label
//! size, etc) and thus not intended for direct plotting.

class MVVM_MODEL_EXPORT BinnedAxisItem : public BasicAxisItem {
public:
    explicit BinnedAxisItem(const std::string& model_type);

    virtual std::pair<double, double> range() const = 0;

    virtual int size() const = 0;

    virtual std::vector<double> binCenters() const = 0;
};

//! Item to represent fixed bin axis.
//! Defines an axis with equidistant binning.

class MVVM_MODEL_EXPORT FixedBinAxisItem : public BinnedAxisItem {
public:
    static inline const std::string P_NBINS = "P_NBINS";
    explicit FixedBinAxisItem(const std::string& model_type = Constants::FixedBinAxisItemType);

    void setParameters(int nbins, double xmin, double xmax);

    static std::unique_ptr<FixedBinAxisItem> create(int nbins, double xmin, double xmax);

    std::pair<double, double> range() const override;

    int size() const override;

    std::vector<double> binCenters() const override;
};

//! Item to represent pointwise axis.
//! Defines an axis via array of points representing point coordinates.

class MVVM_MODEL_EXPORT PointwiseAxisItem : public BinnedAxisItem {
public:
    explicit PointwiseAxisItem(const std::string& model_type = Constants::PointwiseAxisItemType);

    void setParameters(const std::vector<double>& data);

    static std::unique_ptr<PointwiseAxisItem> create(const std::vector<double>& data);

    std::pair<double, double> range() const override;

    int size() const override;

    std::vector<double> binCenters() const override;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_AXISITEMS_H
