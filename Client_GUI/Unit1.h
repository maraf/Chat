//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <stdio.h>

#include "Unit2.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <winsock2.h>
#include <process.h>
#include <time.h>



//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TMemo *Memo2;
	TButton *Button1;
	TPanel *Panel1;
	TPanel *Panel2;
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TEdit *Edit2;
	TButton *Button3;
	TLabel *Label3;
	TEdit *Edit3;
	TPanel *Panel3;
	TButton *Button2;
	TLabel *Label5;
	TLabel *Label4;
	TLabel *Label6;
	TTimer *Timer1;
	TFontDialog *FontDialog1;
	TButton *Button4;
	TSaveTextFileDialog *SaveTextFileDialog1;
	TColorDialog *ColorDialog1;
	TButton *Button5;
	TButton *Button6;
	TPanel *Panel4;
	TPanel *Panel5;
	TLabel *Label7;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
	int _iClientSocket;
	bool _bIsConnected;
	String _sNickName;
	NetListenThread *_ntlThread;
	
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	__fastcall ~TForm1();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
