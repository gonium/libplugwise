#include "stickinitrequest.hpp"

using namespace plugwise;


void StickInitRequest::send(plugwise::Connection::Ptr con) {
  con->send_payload("000A");
}
