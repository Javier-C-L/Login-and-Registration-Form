//---------------------------------------------------------------------------

#include <fmx.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <locale>
#pragma hdrstop

#include <System.Hash.hpp>
/*
#include <IdHashMessageDigest.hpp>
#include <IdSSLOpenSSLHeaders.hpp>
#include <IdHashSHA.hpp>
*/
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

// Function declarations
const char* convertToCharPtr(AnsiString ansiStr) ;
AnsiString hashUserInfo(AnsiString info) ;
bool checkTextEmpty(AnsiString name, AnsiString email, AnsiString username,
					AnsiString password, AnsiString passwordConfirm) ;
bool checkCommas(AnsiString name, AnsiString email, AnsiString username,
					AnsiString password) ;
bool checkStringSize(AnsiString string) ;
std::vector<std::string> parseCommaDelimitedString(std::string line) ;
bool checkUsernameAvailable(AnsiString usernameNew) ;
AnsiString hashUserInfo(AnsiString info) ;

void __fastcall TMyRegistrationForm::SaveButtonClick(TObject *Sender)
{

    AnsiString name = nameEdit->Text ;
	AnsiString email = emailEdit->Text ;
	AnsiString username = usernameEdit->Text ;
	AnsiString password = passwordEdit->Text ;
	AnsiString passwordConfirm = passwordConfirmEdit->Text ;

	if (checkTextEmpty(name, email, username, password, passwordConfirm)) {
		messageLabel->Text = "Please fill out all forms before continuing." ;
	}
	else if (checkCommas(name, email, username, password)) {
		messageLabel->Text = "Forms cannot contain commas." ;
	}
	else if (checkStringSize(username)) {
		messageLabel->Text = "Username must be 8 to 20 characters long." ;
	}
	else if (checkUsernameAvailable(username)) {
		messageLabel->Text = "Username already in use." ;
	}
	else if (checkStringSize(password)) {
		messageLabel->Text = "Password must be 8 to 20 characters long." ;
	}
	else if (std::strcmp(convertToCharPtr(passwordEdit->Text), convertToCharPtr(passwordConfirmEdit->Text)) != 0) {
		messageLabel->Text = "Passwords do not match." ;
	}
	else {
		fstream myFile ;
		myFile.open("registeredUsers.txt", ios::app) ;

		if (myFile.is_open()) {
			/*
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			const std::wstring wide_string = L"This is a string";
			const std::string utf8_string = converter.to_bytes(wide_string);
			*/

			myFile << hashUserInfo(name) << "," << hashUserInfo(email) << ","
				   << hashUserInfo(username) << "," << hashUserInfo(password) << "\n" ;
			myFile.close() ;
			messageLabel->Text = "User registered successfully!." ;

			Close() ;
		}
	}
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

bool checkCommas(AnsiString name, AnsiString email, AnsiString username,
					AnsiString password)
{
	std::string nameStr = convertToCharPtr(name) ;
	std::string emailStr = convertToCharPtr(email) ;
	std::string usernameStr = convertToCharPtr(username) ;
	std::string passwordStr = convertToCharPtr(password) ;
	bool commaFound = (nameStr.find(',') != std::string::npos) ||
				 (emailStr.find(',') != std::string::npos) ||
				 (usernameStr.find(',') != std::string::npos) ||
				 (passwordStr.find(',') != std::string::npos) ;

	return commaFound ;
}

bool checkStringSize(AnsiString string) {
	if (string.Length() > 20 || string.Length() < 8) {
		return true ;
	}
	else {
		return false ;
    }
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

bool checkUsernameAvailable(AnsiString usernameNew) {
	bool usernameFound = false;

    fstream myFile ;
	myFile.open("registeredUsers.txt", ios::in) ;

	if (myFile.is_open()) {
		std::string line ;

		while (getline(myFile,line) && !usernameFound) {
			std::vector<std::string> parsedLine = parseCommaDelimitedString(line) ;
			const char* username = parsedLine.at(2).c_str() ;

			// AnsiString editUsername = usernameEdit->Text ;
			// const char* usernameString = editUsername.c_str() ;

			AnsiString usernameNewHash = hashUserInfo(usernameNew) ;

			if (std::strcmp(convertToCharPtr(usernameNewHash), username) == 0) {

				usernameFound = true ;

			}

		}

		myFile.close() ;

	}

	return usernameFound ;
}

AnsiString hashUserInfo(AnsiString info) {
	UnicodeString infoHash = THashSHA2::GetHashString(info, THashSHA2::TSHA2Version::SHA256);
	AnsiString infoHashAnsi = infoHash ;
	return infoHashAnsi ;
}
