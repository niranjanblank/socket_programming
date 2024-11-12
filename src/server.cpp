#include<iostream>
#include<winsock2.h>
#include <ws2tcpip.h>   // Required for InetPton()
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
  InetPton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr);
  // binding socker 
  if(bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == 0){
    std::cout << "Socket binding complete" << std::endl;
  }
  else{
    std::cerr << "Socket binding failed" << WSAGetLastError() << std::endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
  }

// listen for connections
  if(listen(serverSocket, 5) == 0){
    std::cout << "Listening to clients..." << std::endl;
  }
  else{
    std::cerr << "Error listening on socket: " <<WSAGetLastError() << std::endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;

  }

  // accept client connections
  int clientSocket = accept(serverSocket, nullptr, nullptr);
  
  if(clientSocket == INVALID_SOCKET){
    std::cerr << "Accept Failed " << WSAGetLastError() << std::endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
  }

  // receiving data
  char buffer[200];
  while(true){
    
  int bytes_received = recv(clientSocket, buffer, sizeof(buffer),0);
  if(bytes_received < 0){
    std::cout << "Client: Error " << WSAGetLastError() << std::endl;
    return 0;
  }
  else if(bytes_received == 0){
    // socket closed
    std::cout << "Client Disconnected" << std::endl;
      break;;
  }
  else {
    std::string data_received = std::string(buffer);
    std::cout << "Received data: "<< data_received.substr(0,bytes_received) <<std::endl;
    std::cout << "Bytes: " << bytes_received << std::endl;

    // send data to client
    std::string confirmation = "Server: Message Received";
    int byte_count_sent = send(clientSocket, confirmation.c_str(), confirmation.size(),0);
     if(byte_count_sent == SOCKET_ERROR){
      std::cerr << "Message sending to client failed :" << WSAGetLastError() << std::endl;
      break;
      }
    else{
      std::cout << "Server: Message sent to client " << byte_count_sent <<std::endl;
        }

    }
   

  }

  closesocket(serverSocket);
  WSACleanup();
 
return 0;
}
