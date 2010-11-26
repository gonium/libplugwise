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
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <iterator>
#include <fcntl.h>
#include <termios.h>
#include <boost/crc.hpp>

typedef boost::crc_optimal<16, 0x1021, 0, 0, false, false> crc_plugwise_type;


std::string getStickInitCode() {
  // <ENQ><ENQ><ETX><ETX>000AB43C<CR><LF>
  char initcode[]="\x05\x05\x03\x03\x00\x00\x00\x0a\xb4\x3c\x0d\x0a";
  std::string retval(initcode);
  std::cout << "Prepared init string: " << retval << std::endl;
  return retval;
}



int main(int argc,char** argv) {
  struct termios tio;
  int tty_fd;
  //fd_set rdset;

  unsigned char c='X';

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

  //unsigned char initcode[]="\x05\x05\x03\x03\x30\x30\x30\x41\x42\x34\x33\x43\x0d\x0a";
  unsigned char prefix[]="\x05\x05\x03\x03";
  unsigned char payload[] = "000A";
  //unsigned char crc16[] = "\x42\x34\x33\x43";
  crc_plugwise_type  crc16_calc;
  crc16_calc.process_bytes( payload, 4);
  std::ostringstream oss;
  oss << std::hex << std::uppercase << crc16_calc.checksum();
  std::string crc16(oss.str());
  unsigned char suffix[]= "\x0d\x0a";
    
  std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
  std::cout.setf(std::ios_base::showbase);
  std::cout << "Initcode: " << payload << ", CRC16: " << crc16.c_str() << std::endl;
  write(tty_fd, &prefix, 4);
  write(tty_fd, &payload, 4);
  write(tty_fd, crc16.c_str(), 4);
  write(tty_fd, &suffix, 2);

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
  
  std::cout << std::endl << "Reading stick response" << std::endl;
  while (true) {
    if (read(tty_fd,&c,1)>0) 
      // if new data is available on the serial port, print it out
      std::cout << &c;
     // printf("%#o", &c);
  }

  close(tty_fd);
}
