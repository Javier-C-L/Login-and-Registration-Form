﻿//---------------------------------------------------------------------------

#include <fmx.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <System.Hash.hpp>
#pragma hdrstop

#include "LoginForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMyLoginForm *MyLoginForm;
//---------------------------------------------------------------------------
__fastcall TMyLoginForm::TMyLoginForm(TComponent* Owner)
	: TForm(Owner)
{
}

std::vector<std::string> parseCommaDelimitedString(std::string line) {
	std::vector<std::string> result ;
	std::stringstream s_stream(line) ;

	while(s_stream.good()) {
		std::string substr ;
		getline(s_stream, substr, ',') ;
		result.push_back(substr) ;
	}
	return result ;
}

const char* convertToCharPtr(AnsiString ansiStr) {
	return ansiStr.c_str() ;
}

AnsiString hashUserInfo(AnsiString info) {
	UnicodeString infoHash = THashSHA2::GetHashString(info, THashSHA2::TSHA2Version::SHA256);
	AnsiString infoHashAnsi = infoHash ;
	return infoHashAnsi ;
}

//---------------------------------------------------------------------------
void __fastcall TMyLoginForm::LoginButtonClick(TObject *Sender)
{
	bool loginSuccess = false ;
	fstream myFile ;
	myFile.open("registeredUsers.txt", ios::in) ;

	if (myFile.is_open()) {
		std::string line ;

		while (getline(myFile,line) && !loginSuccess) {
			std::vector<std::string> parsedLine = parseCommaDelimitedString(line) ;
			const char* username = parsedLine.at(2).c_str() ;

			// AnsiString editUsername = usernameEdit->Text ;
			// const char* usernameString = editUsername.c_str() ;

			AnsiString usernameEditHash = hashUserInfo(usernameEdit->Text) ;

			if (std::strcmp(username, convertToCharPtr(usernameEditHash)) == 0) {

				const char* password = parsedLine.at(3).c_str() ;

				// AnsiString editPassword = passwordEdit->Text ;
				// const char* passwordString = editPassword.c_str() ;

				AnsiString passwordEditHash = hashUserInfo(passwordEdit->Text) ;

				if (std::strcmp(password, convertToCharPtr(passwordEditHash)) == 0) {
					loginSuccess = true ;
				}

			}

		}

		myFile.close() ;
	}


	if (loginSuccess) {
		messageLabel->Text = "Success" ;
	}
	else {
        messageLabel->Text = "Username and Password do not match" ;
    }


}
//---------------------------------------------------------------------------
