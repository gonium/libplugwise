#include "responsefactory.hpp"
#include <stickinitresponse.hpp>

using namespace plugwise;

Response::Ptr ResponseFactory::receive() {

  _con->read_response();
  _con->read_response();
  return Response::Ptr(new StickInitResponse("foo", "bar"));
}
