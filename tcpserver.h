#ifndef TCPSERVER_H
#define TCPSERVER_H

class TcpServer {
public:
	TcpServer(int port);
	~TcpServer();

	bool init();
	bool bind();
	bool listen();
	bool accept();

private:
	int m_port;
	int m_listenfd;
};

#endif
