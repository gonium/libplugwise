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

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <fcntl.h>
#include <termios.h>
#include <boost/crc.hpp>

enum response_state_t {
  start, 
  prefix_1, prefix_2, prefix_3,
  message,
  suffix_1, suffix_2
};

typedef boost::crc_optimal<16, 0x1021, 0, 0, false, false> crc_plugwise_type;

void send_payload(int tty_fd, std::string payload) {
  //unsigned char initcode[]="\x05\x05\x03\x03\x30\x30\x30\x41\x42\x34\x33\x43\x0d\x0a";
  unsigned char prefix[]="\x05\x05\x03\x03";
  //unsigned char crc16[] = "\x42\x34\x33\x43";
  crc_plugwise_type  crc16_calc;
  crc16_calc.process_bytes( payload.c_str(), payload.length());
  std::ostringstream oss;
  oss << std::hex << std::uppercase << crc16_calc.checksum();
  std::string crc16(oss.str());
  unsigned char suffix[]= "\x0d\x0a";
    
  std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
  std::cout.setf(std::ios_base::showbase);
  std::cout << "--> Payload: " << payload << ", CRC16: " << crc16.c_str() << std::endl;
  write(tty_fd, &prefix, 4);
  write(tty_fd, payload.c_str(), payload.length());
  write(tty_fd, crc16.c_str(), 4);
  write(tty_fd, &suffix, 2);
}

void read_response(int tty_fd) {
  // We need a state machine to detect the boundaries of the message.
  enum response_state_t state=start;
  bool received=false;
  unsigned char c;
  std::vector<unsigned char> buffer;
  while (!received) {
    if (read(tty_fd,&c,1)>0) {
      // if new data is available on the serial port, print it out
      //std::cout << &c;
      switch (state) {
        case start:
          if (c == '\x05') state = prefix_1; break;
        case prefix_1:
           if (c == '\x05') state = prefix_2; break;
        case prefix_2:
           if (c == '\x03') state = prefix_3; break;
        case prefix_3:
           if (c == '\x03') state = message; break;
        case message:
          if (c != '\x0d') 
            buffer.push_back(c);
          else {
            state = suffix_2; 
            received = true; 
          }
          break;
      }
    }
  }
  if (buffer.size() != 0) {
    std::ostringstream oss;
    std::vector<unsigned char>::iterator it;
    for (it = buffer.begin(); it != buffer.end(); ++it) 
      oss << (*it);
    std::cout << "<-- Response: " << oss.str() << std::endl;
  }
}

int main(int argc,char** argv) {
  struct termios tio;
  int tty_fd;
  //fd_set rdset;


  std::cout << "Please start with " << argv[0] << 
    " /dev/ttyS1 (for example)" << std::endl;

  memset(&tio,0,sizeof(tio));
  tio.c_iflag=0;
  tio.c_oflag=0;
  tio.c_cflag=CS8|CREAD|CLOCAL;			// 8n1, see termios.h for more information
  tio.c_lflag=0;
  tio.c_cc[VMIN]=1;
  tio.c_cc[VTIME]=5;

  tty_fd=open(argv[1], O_RDWR);			//  | O_NONBLOCK);
  cfsetospeed(&tio,B115200);			// 9600 baud
  cfsetispeed(&tio,B115200);			// 9600 baud
  tcsetattr(tty_fd,TCSANOW,&tio);


  //std::string initcode=getStickInitCode();
  //std::string::iterator it;

  //std::cout << "Sending stick init code" << std::endl;
  //std::cout.width(2);
  //std::cout.fill('0');
  //std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
  //std::cout.setf(std::ios_base::showbase);
  //for (it=initcode.begin(); it != initcode.end(); it++) {
  //  unsigned char foo = (*it);
  //  std::cout << std::hex << foo << ":";
  //write(tty_fd, &foo, 1);
  //}

  std::cout << "### Initializing stick" << std::endl;
  send_payload(tty_fd, "000A");
  read_response(tty_fd);
  read_response(tty_fd);
  std::cout << "### Sending calibration request " << std::endl;
  send_payload(tty_fd, "0026000D6F00007293BD");
  read_response(tty_fd);
  read_response(tty_fd);
  std::cout << "### Sending power information request " << std::endl;
  send_payload(tty_fd, "0012000D6F00007293BD");
  read_response(tty_fd);
  read_response(tty_fd);


  close(tty_fd);
}
