//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall NetListenThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall NetListenThread::NetListenThread(bool CreateSuspended, TMemo *Memo1, TLabel *Label2, int ClientSocket)
	: TThread(CreateSuspended)
{
	this->Memo1 = Memo1;
	this->Label5 = Label2;
	this->_iClientSocket = ClientSocket;
}
//---------------------------------------------------------------------------
void __fastcall NetListenThread::Execute()
{
	//---- Place thread code here ----
	int iResult;
	std::string text;

	do {
		char buf[11] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0', '\0'};
		iResult = recv(_iClientSocket, buf, 10, 0);
		if ( iResult > 0 )
			text += buf;
		else if ( iResult == 0 )
			Application->MessageBoxA("Connection to remote server closed!", "Error", MB_OK);
		else
			Application->MessageBoxA("Can't receive data from remote server!", "Error", MB_OK);

		size_t endChar;
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		endChar = text.find("\\q\\q");
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		std::string ss = text.substr(0, text.size() - 4);
		if (endChar != std::string::npos) {
			if(ss.substr(0, 4) == "list") {
				ss = ss.substr(5, ss.size());
				Label5->Caption = ss.c_str();
			} else {
				Memo1->Lines->Add(ss.c_str());
			}
			text = "";
        }

	} while( iResult > 0 );

	return;
}
//---------------------------------------------------------------------------
