//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	_bIsConnected = false;

	Form1->Left = 60;
	Form1->Top = 60;
	Form1->ClientWidth = 280;
	Form1->ClientHeight = 175;
}

__fastcall TForm1::~TForm1()
{
	if(_bIsConnected) {
		_ntlThread->Terminate();
		closesocket(_iClientSocket);
		WSACleanup();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(StrLen(Memo2->Lines->GetText()) == 0) {
		return;
	}

	std::string gettext = Memo2->Lines->GetText();
	gettext.erase(gettext.find_last_not_of(' ')+1);

	if(gettext.size() == 0) {
		Memo2->Lines->Clear();
		return;
	}

	Memo1->Lines->Add(_sNickName + " << " + gettext.c_str());
	String text = _sNickName + " >> " + gettext.c_str() + "\\q\\q";

	int iResult;
	if ((iResult = send(_iClientSocket, text.c_str(), text.Length(), 0)) == -1)
	{
		Application->MessageBoxA("Problem with sending data to remote server", "Error", MB_OK);
		WSACleanup();
		Application->Terminate();
	}
	
	Memo2->Lines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if(Edit1->Text.Length() == 0 || Edit2->Text.Length() == 0 || Edit3->Text.Length() == 0) {
		Application->MessageBoxA("You have to fill NickName, IP Address & Port!", "Error", MB_OK);
		return;
	}



	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA data;
	sockaddr_in serverSock;
	HOSTENT *host;
	int port;
	int size;

	host = gethostbyname(Edit1->Text.c_str());
	port = StrToInt(Edit2->Text);
	_sNickName = Edit3->Text;

	if (WSAStartup(wVersionRequested, &data) != 0)
	{
		Application->MessageBoxA("Failed to initialize sockets!", "Error", MB_OK);
	}

	if ((_iClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		Application->MessageBoxA("Failed to create socket!", "Error", MB_OK);
		WSACleanup();
	}
	
	serverSock.sin_family = AF_INET;
	serverSock.sin_port = htons(port);

	serverSock.sin_addr.s_addr = inet_addr(Edit1->Text.c_str());

	if (serverSock.sin_addr.s_addr == INADDR_NONE) {
		Application->MessageBoxA("The address must be IPv4 address!", "Error", MB_OK);
		return;
	}

	int iResult;
	if (iResult = connect(_iClientSocket, (sockaddr *)&serverSock, sizeof(serverSock)) == -1)
	{
		Application->MessageBoxA("Can't connect to remote server!", "Error", MB_OK);
		WSACleanup();
	}
	else
	{
		String helloMsg = "helo:" + _sNickName + "\\q\\q";
		if ((iResult = send(_iClientSocket, helloMsg.c_str(), helloMsg.Length(), 0)) == -1)
		{
			Application->MessageBoxA("Can't receive data from remote server!", "Error", MB_OK);
			WSACleanup();
		}
		else
		{
			_ntlThread = new NetListenThread(false, Memo1, Label5, _iClientSocket);

			Form1->Visible = false;
			Panel2->Visible = false;
			Panel1->Visible = true;
			Panel3->Visible = true;
			Form1->ClientWidth = 845;
			Form1->ClientHeight = 646;
			this->Button2Click(Sender);
			Form1->Position = poScreenCenter;
			Form1->BorderStyle = bsSizeable;
			Form1->BorderIcons << biMaximize;
			Form1->Constraints->MinHeight = 678;
			Form1->Constraints->MinWidth = 851;
			Form1->Visible = true;

			_bIsConnected = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	int iResult = 0;
	if(_bIsConnected) {
		String helloMsg = "exit:" + _sNickName + "\\q\\q";
		if ((iResult = send(_iClientSocket, helloMsg.c_str(), helloMsg.Length(), 0)) == -1)
		{
			WSACleanup();
		}
	}
	iResult = shutdown(_iClientSocket, 0x01);
	if (iResult == SOCKET_ERROR) {
		closesocket(_iClientSocket);
		WSACleanup();
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int iResult = 0;
	if(_bIsConnected) {
		String helloMsg = "list\\q\\q";
		if ((iResult = send(_iClientSocket, helloMsg.c_str(), helloMsg.Length(), 0)) == -1)
		{
			Application->MessageBoxA("Problem with sending data to remote server", "Error", MB_OK);
			WSACleanup();
			Application->Terminate();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	this->Button2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	if(FontDialog1->Execute() == true) {
		Memo1->Font = FontDialog1->Font;
		Memo2->Font = FontDialog1->Font;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	if(ColorDialog1->Execute() == true) {
		Memo1->Color = ColorDialog1->Color;
		Memo2->Color = ColorDialog1->Color;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	
	std::stringstream ssFileName;
	ssFileName << st.wYear << "-" << st.wMonth << "-" << st.wDay << ".txt";
	SaveTextFileDialog1->FileName = ssFileName.str().c_str();
	if(SaveTextFileDialog1->Execute() == true) {
		FILE * save = fopen(SaveTextFileDialog1->FileName.c_str(), "w");
		fputs(Memo1->Lines->GetText(), save);
		fclose(save);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
	Panel1->Width = Form1->ClientWidth - 235;
	Panel3->Left = Form1->ClientWidth - 222;
	Memo1->Width = Form1->ClientWidth - 255;
	Memo2->Width = Form1->ClientWidth - 255;
	Panel4->Left = Form1->ClientWidth - 245 - Panel4->Width;

	Panel1->Height = Form1->Height - 47;
	Panel3->Height = Form1->Height - 47;
	Memo1->Height = Form1->Height - 245;
	Memo2->Top = Form1->Height - 231;
	Panel4->Top = Form1->Height - 86;
	Panel5->Top = Form1->Height - 86;
}
//---------------------------------------------------------------------------

