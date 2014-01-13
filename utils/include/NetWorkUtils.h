#ifndef CUTILS_NETWORKUTILS_H_
#define CUTILS_NETWORKUTILS_H_

class NetWorkUtils
{
public:
	NetWorkUtils(void);
	~NetWorkUtils(void);
	static void sendUDPdata(const char *ip, int port, char * data, int data_len);
	static void recvUDPdata(int port, char *data, int data_len);
	static void sendBraodcast(int port, char *data, int data_len);
	static int  checkPortUDP( short int nPort );
};

#endif
