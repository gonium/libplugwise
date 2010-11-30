#include "responsefactory.hpp"
#include <stickinitresponse.hpp>

using namespace plugwise;

Response::Ptr ResponseFactory::receive() {
  return Response::Ptr(new StickInitResponse("foo", "bar"));
}
