#include "StdAfx.h"
#include <winsock.h>
#include "..\include\NetWorkUtils.h"


NetWorkUtils::NetWorkUtils(void)
{
}

NetWorkUtils::~NetWorkUtils(void)
{
}

void NetWorkUtils::sendUDPdata(const char *ip, int port, char * data, int data_len){
//版本协商
	WORD wVersionRequested;
	WSADATA wsaData;

	int err;
	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );

	if ( err != 0 ) {
		return;
	}


	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
			WSACleanup( );
			return; 
	}

	int len = sizeof(sockaddr);
	//创建服务器套接字
	SOCKET Svr = socket(AF_INET,SOCK_DGRAM,0);

	//创建地址
	SOCKADDR_IN sendAddrSvr;
	sendAddrSvr.sin_family = AF_INET;
	sendAddrSvr.sin_port = htons(port);
	sendAddrSvr.sin_addr.S_un.S_addr = inet_addr(ip);

	//发送数据
	sendto(Svr,data,data_len,0,(sockaddr*)&sendAddrSvr,len);

	closesocket(Svr);
	WSACleanup();

}

void  NetWorkUtils::recvUDPdata(int port, char *data, int data_len){

	int err = 0;
	WORD revWORD;
	revWORD = MAKEWORD( 1, 1 );
	WSADATA revDATA;

	err = WSAStartup(revWORD, &revDATA );

	if ( err != 0 ) {
		return ;
	}

	if ( LOBYTE( revDATA.wVersion ) != 1 ||
		HIBYTE( revDATA.wVersion ) != 1) {
			WSACleanup( );
			return ; 
	}

	//创建数据报套接字
	SOCKET svr = socket(AF_INET,SOCK_DGRAM,0);

	//创建本地地址信息
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int sockaddr_size = sizeof(sockaddr);
	bind(svr,(sockaddr*)&addr,sockaddr_size);

	//创建客户端地址对象
	SOCKADDR_IN addrClient;

	recvfrom(svr,data,data_len,0,(sockaddr*)&addrClient,&sockaddr_size);
	//char * ip = inet_ntoa(addrClient.sin_addr);

	closesocket(svr);
	WSACleanup();
}

void  NetWorkUtils::sendBraodcast(int port, char *data, int data_len){
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	// 启动socket api
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 )
	{
		WSACleanup( );
		return ; 
	}

	// 创建socket
	SOCKET connect_socket;
	connect_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == connect_socket)
	{
		err = WSAGetLastError();
		return ;
	}

	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_BROADCAST;

	bool bOpt = true;
	//设置该套接字为广播类型
	setsockopt(connect_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

	int nAddrLen = sizeof(SOCKADDR);


	// 发送数据
	int nSendSize = sendto(connect_socket, data, data_len, 0, (SOCKADDR*)&sin, nAddrLen);
	if(SOCKET_ERROR == nSendSize)
	{
		err = WSAGetLastError();
		return ;
	}
}

int NetWorkUtils::checkPortUDP( short int nPort )
{
	struct sockaddr_in nSockServer;

	WSADATA wsaData;

	int lBusy = 0;
	int nSocket;

	/* Initialization */
	if( WSAStartup( 0x0101, &wsaData ) == 0 )
	{
		/* Create Socket */
		nSockServer.sin_family      = AF_INET;
		nSockServer.sin_port        = htons( nPort );
		nSockServer.sin_addr.s_addr = inet_addr( "127.0.0.1" );

		/* Check UDP Protocol */
		nSocket = socket( AF_INET, SOCK_DGRAM, 0 );

		lBusy = ( bind( nSocket, (SOCKADDR FAR *) &nSockServer,
			sizeof( SOCKADDR_IN ) ) == SOCKET_ERROR );

		/* Close Socket if Busy */
		if( lBusy )
			closesocket( nSocket );

		/* Close Winsock */
		WSACleanup();
	}

	/* Return */
	return( lBusy );
}
