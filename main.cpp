//TODO: konfigurace spusteni
//TODO: parsovani argumentu
//TODO: nacitani, parsovani konfiguraku
//TODO: trace chyb pripojeni
//TODO: akce pri zachyceni
//TODO: user mode
<<<<<<< HEAD
=======
//TODO: heslovani
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
//TODO: zapouzdreni do objektu
//TODO: logovani
//TODO: filetransfer
//TODO: handle odpojeni
//TODO: vypis erroru
//TODO: registrace na serveru
<<<<<<< HEAD
//TODO: ovladani na zaklade Ad-Hoc (mozna)
//TODO: resource na zaklade $HOSTNAME (mozna)
//TODO: GUI, mozna na zaklade ncurses
#include <iostream>
#include <fstream>
#include "version.h"
#include "bot.h"
#include "output.h"
=======
//TODO: ovladani na zaklade Ad-Hoc
//TODO: resource na zaklade $HOSTNAME
#include <iostream>
#include <fstream>
#include <cstring>
#include "version.h"
#include "bot.h"
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76

using namespace std;

int handle_argv(int argc, char *argv[]);

int parse_config();

int init_log();

int main(int argc, char *argv[])
{
<<<<<<< HEAD
=======
	if ((argc == 2)&&(!strcmp(argv[1],"-v"))) {
		cout << AutoVersion::FULLVERSION_STRING << endl;
		return 0;}
	if ((argc == 2)&&(!strcmp(argv[1],"-h"))) {
		system("cat README");
		return 0;}
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
    handle_argv(argc, argv);
	ifstream fin;
	string configfile;
	if (argc>1) configfile = argv[1];
	else configfile = "tamara.conf";
	fin.open(configfile.c_str());
<<<<<<< HEAD
	string sJID;
	string spass;
	string bpass;
=======
	//TODO: poresit tuhle zhovadilost
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
	if (!fin.good())
	{
	  fin.close();
	  ofstream fout;
	  fout.open(configfile.c_str());
	  cout << "@ Creating configuration file:\n";
	  cout << "$ JID: ";
<<<<<<< HEAD
	  getline(cin,sJID);
	  cout << "$ Pass: ";
	  getline(cin,spass);
	  cout << "$ Pass for bot: ";
=======
	  string sJID;
	  getline(cin,sJID);
	  cout << "$ Pass: ";
	  string spass;
	  getline(cin,spass);
	  cout << "$ Pass for bot: ";
	  string bpass;
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
	  getline(cin,bpass);
	  fout << "JID: ";
	  fout << sJID << endl;
	  fout << "Password: ";
	  fout << spass << endl;
	  fout << "BotPassword: ";
	  fout << bpass << endl;
	  fout.close();
<<<<<<< HEAD
    } else {
=======
	  fin.open(configfile.c_str());
	}
	string sJID;
	string spass;
	string bpass;
	if (!fin.good())
	{
	  cerr << "@ Cannot operate with files, add info manually: ";
	  cout << "& JID: ";
	  getline(cin,sJID);
	  cout << "& Pass: ";
	  getline(cin,spass);
	  cout << "& BotPass: ";
	  getline(cin,bpass);
	} else {
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
	  fin >> sJID;
	  fin >> sJID;
	  fin.get();
	  fin >> spass;
	  fin >> spass;
	  fin.get();
	  fin >> bpass;
	  fin >> bpass;
	  fin.get();
	}
	cout << "# Ready for initiate\n";
	cout << "# JID is: " << sJID << endl;
	cout << "# pass is: " << spass << endl;
	cout << "# pass for bot is: " << bpass << endl;
	Bot* client = new Bot;
	client -> initiate(sJID,spass,bpass);
<<<<<<< HEAD
	// mohlo by to mit gabbage collector
=======
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
	delete ( client );
	return 0;
}

int handle_argv(int argc, char *argv[])
{
	return 0;
}

int parse_config()
{
	return 0;
}

int init_log()
{
	return 0;
}
