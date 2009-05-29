#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <process.h>
#include <time.h>

#define BUFSIZE 1000

using namespace std;

int mySocket;
string _sNickName;
bool _bLogMessages;
bool _bListRoster;

void threadNetListen(void *param);
int netListen();
void threadConListen(void *param);
int conListen();

int main(int argc, char *argv[])
{
    HANDLE thread1;
    HANDLE thread2;
    
    _bLogMessages = false;
    _bListRoster = false;
    
    WORD wVersionRequested = MAKEWORD(1,1); // Cislo verze
    WSADATA data;                           // Struktura s info. o knihovne
    string text("No feed back\n");          // Odesilany a prijimany text
    hostent *host;                          // Vzdaleny pocitac
    sockaddr_in serverSock;                 // Vzdaleny "konec potrubi"
    int port;                               // Cislo portu
    char buf[BUFSIZE];                      // Prijimaci buffer
    int size;                               // Pocet prijatých a odeslanych bytù
    
    if (WSAStartup(wVersionRequested, &data) != 0)
    {
        cout << "Nepodarilo se inicializovat sokety" << endl;
        return -1;
    }
    
    // SET host + port
    if (argc != 4)
    {
        cerr << "Syntaxe:\n\t" << argv[0]
             << " " << "adresa port nickname" << endl;
        return -1;
    }
    host = gethostbyname(argv[1]);
    port = atoi(argv[2]);
    _sNickName = argv[3];
    //host = gethostbyname("127.0.0.1");
    //port = 3030;
    
    if ((mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        cerr << "Nelze vytvorit soket" << endl;
        WSACleanup();
        return -1;
    }
    
    serverSock.sin_family = AF_INET;
    serverSock.sin_port = htons(port);
    memcpy(&(serverSock.sin_addr), host->h_addr, host->h_length);
    if (connect(mySocket, (sockaddr *)&serverSock, sizeof(serverSock)) == -1)
    {
        cerr << "Nelze navazat spojeni" << endl;
        WSACleanup();
        return -1;
    }
    
    string sendText;
    sendText.append("helo:");
    sendText.append(_sNickName);
    sendText.append("\\q\\q");
    int iResult;
    if ((iResult = send(mySocket, sendText.c_str(), sendText.size(), 0)) == -1)
    {
        cerr << "Problem s odeslanim dat" << endl;
        WSACleanup();
        return -1;
    }
    
    thread1 = (HANDLE) _beginthread( threadNetListen,0,0);
    thread2 = (HANDLE) _beginthread( threadConListen,0,0);
    
    WaitForSingleObject(thread2, INFINITE);
    
    closesocket(mySocket);
    WSACleanup();
    if(text == "OK") {
        cout << "Zprava prijata!" << endl;
    }
    
    system("PAUSE");
    return 0;
}

void threadNetListen(void *param) {
     netListen();
     _endthread();
}

int netListen() {
    int iResult;
    string text;
        
    do {
        char buf[11] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0', '\0'};
        iResult = recv(mySocket, buf, 10, 0);
        if ( iResult > 0 )
            text += buf;
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());
            
        size_t endChar;
        endChar = text.find("\\q\\q");
        if (endChar != string::npos) {
           text = text.substr(0, text.size() - 4);
           if(text != "exit") {
                if(_bListRoster && text.substr(0, 4) == "list") {
                    cout << "Received roster: " << endl << text.substr(5, text.size()) << endl;
                    _bListRoster = false;
                } else {
                    cout<< "Received: " << text.size() << " bytes; Message content: " << endl;
                    cout << text << endl;
                
                    if(_bLogMessages && text != "exit" && text != "log") {
                        SYSTEMTIME st;
                        GetSystemTime(&st);
                        stringstream ssFileName;
                        stringstream ssWriteToFile;
             
                        ssFileName << st.wYear << "-" << st.wMonth << "-" << st.wDay << ".txt";
                        ssWriteToFile << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl << _sNickName << ": " << text << endl << "--------------------" << endl;
             
                        CRITICAL_SECTION m_cs;
                        EnterCriticalSection( &m_cs );
             
                        FILE * f = fopen(ssFileName.str().c_str(), "a");
                        fputs(ssWriteToFile.str().c_str(), f);
                        fclose(f);
             
                        LeaveCriticalSection( &m_cs );
                    }
                }
                
                text = "";
           }
        }

    } while( iResult > 0 );
}

void threadConListen(void *param) {
     conListen();
     _endthread();
}

int conListen() {
    int iResult;
    string text("aabbcc");
    
    while(text != "exit") {
        text = "";
        getline(std::cin, text);
        
        // Operations ....
        if(text == "log") {
            _bLogMessages = true;
        }
        
        if(text == "list") {
            _bListRoster = true;
        }
        
        if(_bLogMessages && text != "exit" && text != "log" && text != "list") {
             SYSTEMTIME st;
             GetSystemTime(&st);
             stringstream ssFileName;
             stringstream ssWriteToFile;
             
             ssFileName << st.wYear << "-" << st.wMonth << "-" << st.wDay << ".txt";
             ssWriteToFile << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl << _sNickName << ": " << text << endl << "--------------------" << endl;
             
             CRITICAL_SECTION m_cs;
             EnterCriticalSection( &m_cs );
             
             FILE * f = fopen(ssFileName.str().c_str(), "a");
             fputs(ssWriteToFile.str().c_str(), f);
             fclose(f);
             
             LeaveCriticalSection( &m_cs );
        }
        
        if(text != "log") {
            string sendText;
            if(text == "exit" || text == "list") {
                sendText.append(text);
                sendText.append(":");
                sendText.append(_sNickName);
                sendText.append("\\q\\q");
            } else {
                text.append("\\q\\q");
                sendText.append(_sNickName);
                sendText.append(" >> ");
                sendText.append(text);
            }
            //cout << "Sending: " << sendText.c_str() << endl;
            if ((iResult = send(mySocket, sendText.c_str(), sendText.size(), 0)) == -1)
            {
                cerr << "Problem s odeslanim dat" << endl;
                WSACleanup();
                return -1;
            }
        }
    }
    
    iResult = shutdown(mySocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(mySocket);
        WSACleanup();
        return 1;
    }
}
