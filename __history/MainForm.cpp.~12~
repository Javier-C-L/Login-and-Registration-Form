//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainForm.h"
#include "LoginForm.h"
#include "RegistrationForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMyMainForm *MyMainForm;
//---------------------------------------------------------------------------
__fastcall TMyMainForm::TMyMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMyMainForm::loginRegistrationButtonClick(TObject *Sender)
{
	MyLoginForm->Show() ;
	MyLoginForm->usernameEdit->Text = "" ;
	MyLoginForm->passwordEdit->Text = "" ;
    MyLoginForm->messageLabel->Text = "" ;
}
//---------------------------------------------------------------------------
void __fastcall TMyMainForm::registrationNavigationButtonClick(TObject *Sender)
{
	MyRegistrationForm->Show() ;
	MyRegistrationForm->nameEdit->Text = "" ;
	MyRegistrationForm->emailEdit->Text = "" ;
	MyRegistrationForm->usernameEdit->Text = "" ;
	MyRegistrationForm->passwordEdit->Text = "" ;
	MyRegistrationForm->passwordConfirmEdit->Text = "" ;
    MyRegistrationForm->messageLabel->Text = "" ;
}
//---------------------------------------------------------------------------
