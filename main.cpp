#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/time.h>
#include <sys/select.h>
#include "tcpserver.h"

void error_handling(std::string message);

int main(int argc, char* argv[])
{
//	TcpServer tcpServer(3000);
//
//	if (!tcpServer.init()) {
//		return -1;
//	}
//	if (!tcpServer.bind()) {
//		return -1;
//	}
//	if (!tcpServer.listen()) {
//		return -1;
//	}
//	if (!tcpServer.accept()) {
//		return -1;
//	}
	
	char buf[32];

	int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	sockaddr_in serv_adr;
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(3000);

	if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	fd_set reads, cpy_reads;
	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);
	int fd_max = serv_sock;

	int num = 6;
	while(num--)
	{
		cpy_reads = reads;
		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		int fd_num;
		if ((fd_num = select(fd_max+1, &cpy_reads, 0, 0, &timeout)) == -1)
			break;
		if (fd_num == 0)
			continue;

		for (int i = 0; i < fd_max+1; i++)
		{
			if (FD_ISSET(i, &cpy_reads))
			{
				if (i == serv_sock)
				{
					sockaddr_in clnt_adr;
					socklen_t adr_sz = sizeof(clnt_adr);
					int clnt_sock = 
						accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
					FD_SET(clnt_sock, &reads);
					if (fd_max < clnt_sock)
						fd_max = clnt_sock;
					printf("connected client: %d \n", clnt_sock);
				}
				else
				{
					int str_len = read(i, buf, 32);
					if (str_len == 0)
					{
						FD_CLR(i, &reads);
						close(i);
						printf("closed client: %d \n", i);
					}
					else
					{
						write(i, buf, str_len);
					}
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}

void error_handling(std::string message)
{
	fputs(message.c_str(), stderr);
	fputc('\n', stderr);
	exit(1);

}

