//---------------------------------------------------------------------------

#include <fmx.h>
#include <fstream>
#include <string>
#pragma hdrstop

#include "RegistrationForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMyRegistrationForm *MyRegistrationForm;
//---------------------------------------------------------------------------
__fastcall TMyRegistrationForm::TMyRegistrationForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

const char* convertToCharPtr(AnsiString ansiStr)
{
	return ansiStr.c_str() ;
}
bool checkTextEmpty(AnsiString name, AnsiString email, AnsiString username,
					AnsiString password, AnsiString passwordConfirm)
{
	bool textEmpty = std::strcmp(convertToCharPtr(name), "") == 0 ||
					 std::strcmp(convertToCharPtr(email), "") == 0 ||
					 std::strcmp(convertToCharPtr(username), "") == 0 ||
					 std::strcmp(convertToCharPtr(password), "") == 0 ||
					 std::strcmp(convertToCharPtr(passwordConfirm), "") == 0 ;

	return textEmpty ;
}

void __fastcall TMyRegistrationForm::SaveButtonClick(TObject *Sender)
{
	fstream myFile ;
	myFile.open("registeredUsers.txt", ios::app) ;

    AnsiString name = nameEdit->Text ;
	AnsiString email = emailEdit->Text ;
	AnsiString username = usernameEdit->Text ;
	AnsiString password = passwordEdit->Text ;
	AnsiString passwordConfirm = passwordConfirmEdit->Text ;

	if (checkTextEmpty(name, email, username, password, passwordConfirm)) {
		messageLabel->Text = "Please fill out all forms before continuing." ;
	}
	else if (std::strcmp(convertToCharPtr(passwordEdit->Text), convertToCharPtr(passwordConfirmEdit->Text)) != 0) {
		messageLabel->Text = "Passwords do not match. Please reenter and try again." ;
	}
	else {
		if (myFile.is_open()) {
			myFile << name << "," << email << "," << username << "," << password << "\n" ;
			myFile.close() ;
			messageLabel->Text = "User registered successfully!" ;
		}
	}

	myFile.close() ;
}
//---------------------------------------------------------------------------

