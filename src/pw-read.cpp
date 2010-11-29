/**
 * This file is part of libplugwise.
 *
 * (c) Mathias Dalheimer <md@gonium.net>, 2010
 *
 * libplugwise is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libplugwise is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libplugwise. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <connection.hpp>

int main(int argc,char** argv) {

  std::cout << "Please start with " << argv[0] << 
    " /dev/ttyS1 (for example)" << std::endl;

  plugwise::Connection::Ptr con(new plugwise::Connection(argv[1]));


  std::cout << "### Initializing stick" << std::endl;
  con->send_payload("000A");
  con->read_response();
  con->read_response();
  std::cout << "### Sending calibration request " << std::endl;
  con->send_payload("0026000D6F00007293BD");
  con->read_response();
  con->read_response();
  std::cout << "### Sending power information request " << std::endl;
  con->send_payload("0012000D6F00007293BD");
  con->read_response();
  con->read_response();

}
