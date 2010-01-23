//TODO: konfigurace spusteni
//TODO: parsovani argumentu
//TODO: nacitani, parsovani konfiguraku
//TODO: trace chyb pripojeni
//TODO: akce pri zachyceni
//TODO: user mode
//TODO: zapouzdreni do objektu
//TODO: logovani
//TODO: filetransfer
//TODO: handle odpojeni
//TODO: vypis erroru
//TODO: registrace na serveru
//TODO: ovladani na zaklade Ad-Hoc (mozna)
//TODO: resource na zaklade $HOSTNAME (mozna)
#include <iostream>
#include <fstream>
#include "version.h"
#include "bot.h"
#include "output.h"

using namespace std;

int handle_argv(int argc, char *argv[]);

int parse_config();

int init_log();

int main(int argc, char *argv[])
{
    handle_argv(argc, argv);
	ifstream fin;
	string configfile;
	if (argc>1) configfile = argv[1];
	else configfile = "tamara.conf";
	fin.open(configfile.c_str());
	string sJID;
	string spass;
	string bpass;
	if (!fin.good())
	{
	  fin.close();
	  ofstream fout;
	  fout.open(configfile.c_str());
	  cout << "@ Creating configuration file:\n";
	  cout << "$ JID: ";
	  getline(cin,sJID);
	  cout << "$ Pass: ";
	  getline(cin,spass);
	  cout << "$ Pass for bot: ";
	  getline(cin,bpass);
	  fout << "JID: ";
	  fout << sJID << endl;
	  fout << "Password: ";
	  fout << spass << endl;
	  fout << "BotPassword: ";
	  fout << bpass << endl;
	  fout.close();
    } else {
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
	// mohlo by to mit gabbage collector
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
