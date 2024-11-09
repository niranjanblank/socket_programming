#include<iostream>
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")

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

  // AF_INET speficies IPv4 protocol, SOCK_STREAM defines TCP type socket
  SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  if (serverSocket == INVALID_SOCKET) {
    std::cerr << "Failed to create socket: " << WSAGetLastError() << std::endl;
    WSACleanup();
    return 1;
  }

  // define server address
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  // inaddr_any is used when we dont want to bind socket to any 
  // particular IP and instead make it listen to all the available IPs
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  // binding socker 
  bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

  // listen for connections
  listen(serverSocket, 5);

  // accept client connections
  int clientSocket = accept(serverSocket, nullptr, nullptr);


return 0;
}
