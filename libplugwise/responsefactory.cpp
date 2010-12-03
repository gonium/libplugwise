#include "responsefactory.hpp"
#include <stickinitresponse.hpp>

using namespace plugwise;

Response::Ptr ResponseFactory::receive() {
  std::string line1(_con->read_response());
  std::string line2(_con->read_response());
  return Response::Ptr(new StickInitResponse(line1, line2));
}
