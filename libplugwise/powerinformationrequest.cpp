#include "powerinformationrequest.hpp"

using namespace plugwise;

void PowerInformationRequest::send(plugwise::Connection::Ptr con) {
  con->send_payload("0012"+_circle_mac);
}
