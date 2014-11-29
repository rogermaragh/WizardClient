#include <winsock2.h>

#define WM_MAINSOCKET (WM_USER + 1)

#define TM_KEEPALIVE 0

typedef struct {
	SOCKET hSocket;
	SOCKADDR_IN hSin;
	char SocketBuffer[4096];
	HANDLE hFile;
	bool Transferring;
} Client;

typedef struct {
	HANDLE hFile;
	SOCKET hSocket;
	DWORD FileSize;
	DWORD Offset;
} FILETRANSFERARGS;

extern char *gpHost;
extern bool gbConnected;
extern bool gbTransferring;
extern HINSTANCE ghInstance;
extern HWND ghWnd;
extern SOCKET ghTcpSocket;
extern bool Processing;
extern int ClientCount;
extern Client *Clients;
extern char *RecvBuffer, *SendBuffer;
extern unsigned long RecvBufSize, SendBufSize;

void RemoteDesktopListen(int port);
void RemoteDesktopAccept(SOCKET wParam);
void RemoteDesktopCleanup(SOCKET wParam);
void RemoteDesktopSendData(unsigned short cmd, unsigned long datac, char **data, unsigned long *datal, unsigned short ci);
void RemoteDesktopSendStr(char *msg, unsigned short ci);
DWORD WINAPI RemoteDesktopReceiveFileThread(LPVOID lpArgs);
DWORD WINAPI RemoteDesktopSendFileThread(LPVOID lpArgs);
void RemoteDesktopStartSendThread(SOCKET wParam, unsigned short ci);
void RemoteDesktopParseData(unsigned short cmd, unsigned long datac, char **data, unsigned long *datal, unsigned short ci);
void RemoteDesktopProcessQueue(unsigned short ci);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void RemoteDesktopParseCommand(int argc, char **argv);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
