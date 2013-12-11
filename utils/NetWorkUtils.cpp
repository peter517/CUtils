#include "StdAfx.h"
#include "NetWorkUtils.h"
#include <winsock.h>


NetWorkUtils::NetWorkUtils(void)
{
}

NetWorkUtils::~NetWorkUtils(void)
{
}

void NetWorkUtils::sendUDPdata(const char *ip, int port, char * data, int data_len){
//�汾Э��
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
	//�����������׽���
	SOCKET Svr = socket(AF_INET,SOCK_DGRAM,0);

	//������ַ
	SOCKADDR_IN sendAddrSvr;
	sendAddrSvr.sin_family = AF_INET;
	sendAddrSvr.sin_port = htons(port);
	sendAddrSvr.sin_addr.S_un.S_addr = inet_addr(ip);

	//��������
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

	//�������ݱ��׽���
	SOCKET svr = socket(AF_INET,SOCK_DGRAM,0);

	//�������ص�ַ��Ϣ
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int sockaddr_size = sizeof(sockaddr);
	bind(svr,(sockaddr*)&addr,sockaddr_size);

	//�����ͻ��˵�ַ����
	SOCKADDR_IN addrClient;

	recvfrom(svr,data,data_len,0,(sockaddr*)&addrClient,&sockaddr_size);
	char * ip = inet_ntoa(addrClient.sin_addr);

	closesocket(svr);
	WSACleanup();
}

void  NetWorkUtils::sendBraodcast(int port, char *data, int data_len){
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	// ����socket api
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

	// ����socket
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
	//���ø��׽���Ϊ�㲥����
	setsockopt(connect_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

	int nAddrLen = sizeof(SOCKADDR);


	// ��������
	int nSendSize = sendto(connect_socket, data, data_len, 0, (SOCKADDR*)&sin, nAddrLen);
	if(SOCKET_ERROR == nSendSize)
	{
		err = WSAGetLastError();
		return ;
	}
}