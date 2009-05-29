#include <iostream>
#include <windows.h>
#include <process.h>
#include <string>
#include <list>

#define BUFSIZE 1000

using namespace std;

int _iCommand = -1;
list<SOCKET> _lsClients;
list<string> _sUsers;
SOCKET _sNewClient;
sockaddr_in _saiClientInfo;

void threadNetListen(void *param);
int netListen(char * param);
void threadConListen(void *param);
int conListen();

void threadStartNewClient(void *param);
int startNewClient(SOCKET client, sockaddr_in _saiClientInfo);

void sendToAllExpect(string text, SOCKET client);

int main(int argc, char *argv[])
{
    if(argc != 2) {
        cerr << "Run program as \n\tTHIS_PROGRAM_NAME PORT_NUMBER!" << endl;
        return -1;
    }
    
    HANDLE thread1 = (HANDLE) _beginthread( threadNetListen,0,argv[1]);
    HANDLE thread2 = (HANDLE) _beginthread( threadConListen,0,0);
    WaitForSingleObject(thread2, INFINITE);
    
    system("PAUSE");  
    return 0;
}

void threadNetListen(void *param) {
    netListen((char *)param);
    _endthread();
}

int netListen(char * param) {
    WORD wVersionRequested = MAKEWORD(1,1);
    WSADATA data;
    string text;
    sockaddr_in sockName;
    sockaddr_in clientInfo;
    SOCKET mainSocket;
    int port;
    int size;
    int addrlen;
    int count = 0;
    
    port = atoi(param);
    
    if (WSAStartup(wVersionRequested, &data) != 0)
    {
        cout << "Failed to initialize sockets!" << endl;        
        return -1;
    }    
    
    if ((mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        cerr << "Failed to create socket!" << endl;
        WSACleanup();
        return -1;
    }
    
    sockName.sin_family = AF_INET;
    sockName.sin_port = htons(port);
    sockName.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(mainSocket, (sockaddr *)&sockName, sizeof(sockName)) == SOCKET_ERROR)
    {
        cerr << "Problem with naming the socket!" << endl;
        WSACleanup();
        return -1;
    }
    
    if (listen(mainSocket, 10) == SOCKET_ERROR)
    {
        cerr << "Problem with creating the queue!" << endl;
        WSACleanup();
        return -1;
    }
    do
    {
        addrlen = sizeof(clientInfo);
        SOCKET client = accept(mainSocket, (sockaddr*)&clientInfo, &addrlen);
        _sNewClient = client;
        _lsClients.push_back(client);
        _saiClientInfo = clientInfo;
        
        
        HANDLE threadx = (HANDLE) _beginthread(threadStartNewClient,0,0);
    


    } while (_iCommand != 1);
    
    closesocket(mainSocket); 
    WSACleanup();           
}

void threadConListen(void *param) {
    conListen();
    _endthread();
}

int conListen() {
    string input;
    do {
        cin >> input;
    } while(input != "exit");
    _iCommand = 1;
}

void threadStartNewClient(void *param) {
    startNewClient(_sNewClient, _saiClientInfo);
    _endthread();
}

int startNewClient(SOCKET client, sockaddr_in clientInfo) {
    string text;
    int size;
    int count = 0;
    int totalSize = 0;
        if (client == INVALID_SOCKET)
        {
                cerr << "Problem with receiving client" <<endl;
                WSACleanup();
                return -1;
        }
        
        cout << "Connected from: " 
                << inet_ntoa((in_addr)clientInfo.sin_addr) << endl;
        text = "";
        
    //--------------------------------------------------------------------
        
    int iResult;
        
    do {
        char buf[11] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0', '\0'};
        iResult = recv(client, buf, 10, 0);
        if ( iResult > 0 )
            text += buf;
        else if ( iResult == 0 )
            cout << "Connection closed, socket: " << client << endl;
        else
            cout << "Recv failed: " << WSAGetLastError() << endl;
            
        size_t endChar;
        endChar = text.find("\\q\\q");
        if (endChar != string::npos) {
           string ss(text);
           ss = ss.substr(0, 4);
           text = text.substr(0, text.size() - 4);
           if(ss == "helo") {
                string nickName = text.substr(5, text.size());
                cout << "Add user to list nickname: " << nickName << endl;
                _sUsers.push_back(nickName);
           } else if(ss == "exit") {
                string nickName = text.substr(5, text.size() - 4);
                cout << "Remove user from list nickname: " << nickName << endl;
                _sUsers.remove(nickName);
           } else if(ss == "list") {
                std::list<string>::iterator iter=NULL;
                string list;
                list.append("list");
                for(iter = _sUsers.begin();iter != _sUsers.end(); )
                {
                    list.append("\n");
                    list.append(*iter);
                    iter ++;
                }
                list.append("\\q\\q");
                if ((size = send(client, list.c_str(), list.size(), 0)) == SOCKET_ERROR)
                {
                    cerr << "Problem with sending data!" << endl;
                    WSACleanup();
                }
           } else {
                cout<< "Received: " << text.size() << " bytes, socket: " << client << ", message content: " << endl;
                cout << text << endl;
                sendToAllExpect(text, client);       
           }
           text = "";
        }

    } while( iResult > 0 );

    //--------------------------------------------------------------------
    
    _lsClients.remove(client);
    iResult = shutdown(client, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        cout << "Shutdown failed: " << WSAGetLastError() << endl;
        closesocket(client);
        WSACleanup();
        return 1;
    }
    //-------------------------------------------------------------
    closesocket(client);
}

void sendToAllExpect(string text, SOCKET client) {
    int size;
    text.append("\\q\\q");
    std::list<SOCKET>::iterator iter=NULL;
    for(iter = _lsClients.begin();iter != _lsClients.end(); )
    {
        if(*iter != client)
        {
            if ((size = send(*iter, text.c_str(), text.size(), 0)) == SOCKET_ERROR)
            {
                cerr << "Problem with sending data!" << endl;
                WSACleanup();
                return;
            }   
        }
        iter ++;
    }
}
