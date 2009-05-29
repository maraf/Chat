//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H

#include <winsock2.h>
#include <string>

//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class NetListenThread : public TThread
{
private:
	TMemo *Memo1;
	TLabel *Label5;
	int _iClientSocket;
protected:
	void __fastcall Execute();
public:
	__fastcall NetListenThread(bool CreateSuspended, TMemo *Memo1, TLabel *Label5, int ClientSocket);
};
//---------------------------------------------------------------------------
#endif
