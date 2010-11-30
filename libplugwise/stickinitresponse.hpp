#ifndef LIBPLUGWISE_STICKINITRESPONSE_HPP
#define LIBPLUGWISE_STICKINITRESPONSE_HPP 1

#include <common.hpp>
#include <response.hpp>
#include <string>

namespace plugwise {
  class StickInitResponse : public Response {
    public:
      typedef std::tr1::shared_ptr<StickInitResponse> Ptr;
      StickInitResponse ( const std::string& line1, 
                          const std::string& line2) :
        _line1(line1), _line2(line2) {};
      virtual std::string str();
      virtual ~StickInitResponse() {};

    private:
      StickInitResponse (const StickInitResponse& original);
      StickInitResponse& operator= (const StickInitResponse& rhs);
      std::string _line1;
      std::string _line2;
      
  };
  
};


#endif /* LIBPLUGWISE_STICKINITRESPONSE_HPP */

