#ifndef PI_PROPERTIES_NETCDFHEADER_SERIALIZER
#define PI_PROPERTIES_NETCDFHEADER_SERIALIZER

#include <boost/lexical_cast.hpp>
#include <rtt/Property.hpp>

#include <netcdf>

#define DIMENSION_VAR 1
#define DIMENSION_ARRAY 2

#include <iostream>
using namespace std;
using namespace netCDF;

namespace RTT {
/**
 * A marsh::MarshallInterface for generating variables in a netcdf dataset
 */
class NetcdfHeaderMarshaller : public marsh::MarshallInterface {
 public:
  NetcdfHeaderMarshaller(NcFile& ncfile) : ncfile(&ncfile) {}

  virtual ~NetcdfHeaderMarshaller() {}

  virtual void serialize(base::PropertyBase* v) {
    log(Error) << "Header: " << v->getName() << endlog();

    if(v->getName() == "TimeStamp") {
        //TODO: extra behavior for the timestamp property provided by the reporter
        return;
    }



  }

  virtual void serialize(const PropertyBag& v) {
    log(Error) << "Header: " << v.getType() << endlog();
    serializeBag(v);
  }

  void serializeBag(const PropertyBag& v, Property<double>* parent_timestamp = NULL) {
      for(int i = 0; i < v.size(); i++) {
          base::PropertyBase* prop = v.getItem(i);

      }
  }

  virtual void flush() {}

 private:
  NcFile* ncfile;
};
}
#endif
