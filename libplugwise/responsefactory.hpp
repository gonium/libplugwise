#ifndef LIBPLUGWISE_RESPONSEFACTORY_HPP
#define LIBPLUGWISE_RESPONSEFACTORY_HPP 1

#include <common.hpp>
#include <response.hpp>
#include <connection.hpp>

namespace plugwise {
  class ResponseFactory {
    public:
      typedef std::tr1::shared_ptr<ResponseFactory> Ptr;
      ResponseFactory (Connection::Ptr con) :
        _con(con) {} ;
      Response::Ptr receive();
      virtual ~ResponseFactory() {};

    private:
      ResponseFactory (const ResponseFactory& original);
      ResponseFactory& operator= (const ResponseFactory& rhs);
      Connection::Ptr _con;
      
  };
  
};


#endif /* LIBPLUGWISE_RESPONSEFACTORY_HPP */

