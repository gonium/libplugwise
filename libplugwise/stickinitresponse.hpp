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
        Response(line1, line2) { parse_line2(); };
      virtual std::string str();
      virtual ~StickInitResponse() {};
      bool is_ok();

    private:
      StickInitResponse (const StickInitResponse& original);
      StickInitResponse& operator= (const StickInitResponse& rhs);
      void parse_line2();
      uint32_t _response_code;
      uint32_t _resp_seq_number;
      std::string _stick_mac_addr;
      bool _network_online;
      std::string _network_uuid;
      uint32_t _network_short_id;
  };
  
};


#endif /* LIBPLUGWISE_STICKINITRESPONSE_HPP */

