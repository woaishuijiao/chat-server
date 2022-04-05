#include "tcpserver.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>

TcpServer::TcpServer(int port)
	:m_port(port),
	m_listenfd(-1)
{

}

TcpServer::~TcpServer()
{
	if(m_listenfd != -1) {
		close(m_listenfd);
	}
}

bool TcpServer::init()
{
	m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if (m_listenfd == -1) {
        std::cout << "create listen socket error" << std::endl;
		return false;
	}
	return true;
}

bool TcpServer::bind()
{
	struct sockaddr_in bindaddr;
	bindaddr.sin_family = AF_INET;
	bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bindaddr.sin_port = htons(m_port);
	if (::bind(m_listenfd, (struct sockaddr*)&bindaddr, sizeof(bindaddr)) == -1) {
		std::cout << "bind listen socket error: " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}

bool TcpServer::listen()
{
    if (::listen(m_listenfd, SOMAXCONN) == -1) {
		std::cout << "listen error" << std::endl;
		return false;
	}
	return true;
}

bool TcpServer::accept()
{
	struct sockaddr_in clientaddr;
	socklen_t clientaddrlen = sizeof(clientaddr);

	int clientfd = ::accept(m_listenfd, (struct sockaddr*)&clientaddr, &clientaddrlen);
	if (clientfd == -1) {
		return false;
	}
	while(1){
		char recvBuf[32] = {0};
		int ret = recv(clientfd, recvBuf, 32, 0);
		if (ret > 0) {
			std::cout << "recv:" << ret << " " << recvBuf << std::endl;
			ret = send(clientfd, recvBuf, strlen(recvBuf), 0);
			if (ret != (int)strlen(recvBuf)) {
				std::cout << "send error:" << ret << " ; strlen(recvBuf): " << strlen(recvBuf) << std::endl;
			} else {
				std::cout << "send:" << recvBuf << std::endl;
				
			}
		}else if (ret == 0) {
				std::cout << "client close sock" << std::endl;
				close(clientfd);
				break;
		} else {
				std::cout << "recv:" << ret << " errno:" << strerror(errno) << std::endl;
				close(clientfd);
				break;
		}
	}
	return true;
}

