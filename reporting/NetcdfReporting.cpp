#include "NetcdfReporting.hpp"
#include <rtt/Logger.hpp>
#include <rtt/RTT.hpp>
#include <rtt/types/TemplateTypeInfo.hpp>
#include <rtt/types/Types.hpp>
#include "NetcdfHeaderMarshaller.hpp"
#include "NetcdfMarshaller.hpp"

#include "ocl/Component.hpp"

#include <netcdf>

namespace OCL {
using namespace RTT;
using namespace std;
using namespace netCDF;

NetcdfReporting::NetcdfReporting(const std::string& fr_name)
    : ReportingComponent(fr_name),
      repfile("ReportFile", "Location on disc to store the reports.",
              "reports.nc") {
  this->properties()->addProperty(repfile);

  if (types::TypeInfoRepository::Instance()->getTypeInfo<short>() == 0) {
    types::TypeInfoRepository::Instance()->addType(
        new types::TemplateTypeInfo<short, true>("short"));
  }
}

bool NetcdfReporting::startHook() {
  ncfile = NcFile(repfile, NcFile::replace, NcFile::nc4);

  this->addMarshaller(new RTT::NetcdfHeaderMarshaller(ncfile),
                      new RTT::NetcdfMarshaller(ncfile));

  return ReportingComponent::startHook();
}

void NetcdfReporting::stopHook() {
  int retval;

  ReportingComponent::stopHook();

  this->removeMarshallers();

  if (!ncfile.isNull()) ncfile.~NcFile();
}
}

ORO_CREATE_COMPONENT(OCL::NetcdfReporting)
