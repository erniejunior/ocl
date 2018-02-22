#ifndef PI_PROPERTIES_NETCDFTABLESERIALIZER
#define PI_PROPERTIES_NETCDFTABLESERIALIZER

#include <boost/lexical_cast.hpp>
#include <rtt/Property.hpp>
#include <rtt/base/PropertyIntrospection.hpp>

#include <iostream>
#include <netcdf>
using namespace std;

namespace RTT {
using namespace netCDF;
/**
 * A marsh::MarshallInterface for writing data logs into the variables of a
 * netcdf file.
 * The dimension of the time is increased on each flush() command.
 * The NetcdfHeaderMarshaller creates the appropriate variables in a netcdf
 * file.
 */
class NetcdfMarshaller : public marsh::MarshallInterface {
 public:
  /**
   * Create a new NetcdfMarshaller
   * @param ncid The ID number of the netcdf file
   */
  NetcdfMarshaller(NcFile &ncfile) : ncfile(&ncfile), just_flushed(true) {}

  virtual ~NetcdfMarshaller() {}

  virtual void serialize(base::PropertyBase *v) {
    log(Error) << "Serializiing: " << v->getName() << endlog();
    just_flushed = false;
  }

  virtual void serialize(const PropertyBag &v) {
    log(Error) << "Serializing bag: " << v.getType() << endlog();
    just_flushed = false;
  }

  /**
   * Increase unlimited time dimension
   */
  virtual void flush() { just_flushed = true; }

 private:
  NcFile *ncfile;
  bool just_flushed;
};
}
#endif
