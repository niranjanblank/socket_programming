#include<iostream>
#include<winsock2.h>

int main(){
  WSADATA wsaData;
  // MAKEWORD create a 16-bit value that represents version of winsock we want
  int result = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (result != 0) {
    std::cerr << "WSAStartup failed:" << result << std::endl;
  }
  else
  {
    std::cout << "WSAStartup succeded" << std::endl;
  }


return 0;
}
