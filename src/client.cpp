#include<iostream>
#include<string>
#include<winsock2.h>
#include <ws2tcpip.h>   // Required for InetPton()                        //
#pragma comment(lib, "ws2_32.lib")

int main (int argc, char *argv[]) {
  
  WSADATA wsaData;
  int result = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (result != 0) {
    std::cerr << "WSAStartup failed:" << result << std::endl;
  }
  else
  {
    std::cout << "WSAStartup succeded" << std::endl;
  }
  
  SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  if (client_socket == INVALID_SOCKET) {
    std::cerr << "Failed to create socket: " << WSAGetLastError() << std::endl;
    WSACleanup();
    return 1;
  }

  // define the serverr address
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  // inaddr_any is used when we dont want to bind socket to any 
  // particular IP and instead make it listen to all the available IPs
  InetPton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr);
  
  // connect to the server
  if( connect(client_socket, (sockaddr*) &serverAddr, sizeof(serverAddr)) == 0){
    std::cout << "Client connected to server" << std::endl;
  }
  else {
    std::cerr << "Client connection failed" << std::endl;
    WSACleanup();
    return 0;
  }

  // send data to the server
  std::string answer;
  std::cout << "Enter some thing" <<std::endl;
  std::getline(std::cin, answer);

  size_t byte_count = send(client_socket, answer.c_str(), answer.size(),0);

  if(byte_count == SOCKET_ERROR){
    std::cerr << "Server sent error :" << WSAGetLastError() << std::endl;
    return -1;
  }
  else{
    std::cout << "Server: sent " << byte_count <<std::endl;
  }

  return 0;
}
