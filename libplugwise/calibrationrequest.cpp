#include "calibrationrequest.hpp"

using namespace plugwise;


void CalibrationRequest::send(plugwise::Connection::Ptr con) {
  con->send_payload("0026"+_circle_mac);
}
