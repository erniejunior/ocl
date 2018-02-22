#ifndef ORO_COMP_NETCDF_REPORTING_HPP
#define ORO_COMP_NETCDF_REPORTING_HPP

#include "ReportingComponent.hpp"
#include <netcdf>

#include <ocl/OCL.hpp>

namespace OCL {
using namespace netCDF;
/**
 * A component which writes data reports to a netCDF file.
 */
class NetcdfReporting : public ReportingComponent {
 protected:
  /**
   * File name of netCDF file.
   */
  RTT::Property<std::string> repfile;
  NcFile ncfile;

 public:
  NetcdfReporting(const std::string& fr_name);

  bool startHook();
  void stopHook();
};
}

#endif
