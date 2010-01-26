//TODO: konfigurace spusteni
//TODO: parsovani argumentu
//TODO: nacitani, parsovani konfiguraku
//TODO: trace chyb pripojeni
//TODO: akce pri zachyceni
//TODO: user mod
//TODO: heslovani
//TODO: zapouzdreni do objektu
//TODO: logovani
//TODO: filetransfer
//TODO: handle odpojeni
//TODO: vypis erroru
//TODO: registrace na serveru
//TODO: ovladani na zaklade Ad-Hoc (mozna)
//TODO: resource na zaklade $HOSTNAME (mozna)
//TODO: GUI, mozna na zaklade ncurses
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
	if ((argc == 2)&&(!strcmp(argv[1],"-v"))) {
		cout << AutoVersion::FULLVERSION_STRING << endl;
		return 0;}
	if ((argc == 2)&&(!strcmp(argv[1],"-h"))) {
		system("cat README");
		return 0;}
    handle_argv(argc, argv);
	ifstream fin;
	string configfile;
	if (argc>1) configfile = argv[1];
	else configfile = "tamara.conf";
	fin.open(configfile.c_str());
	string sJID;
	string spass;
	string bpass;
	bool log = false;
	//TODO: implementovat tohle
	//parse_config(configfile.c_str(),sJID,spass,bpass,log);
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
	  getline(cin,sJID);
	  cout << "$ Pass: ";
	  string spass;
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
	  fin.close();
	}
	cout << "# Ready for initiate\n";
	cout << "# JID is: " << sJID << endl;
	cout << "# pass is: " << spass << endl;
	cout << "# pass for bot is: " << bpass << endl;
	Bot* client = new Bot;
	client -> initiate(sJID,spass,bpass,log);
	// mohlo by to mit gabbage collector
	delete ( client );
	return 0;
}

int handle_argv(int argc, char *argv[])
{
	return 0;
}

int parse_config(char* file, string& sJID, string& spass, string& bpass, bool& log)
{
    ifstream fin;
    fin.open(file);
    while (fin.good())
    {
        string conf;
        fin >> conf;
        if ((conf=="JID:")||(conf=="jid:")) fin >> sJID;
        else if ((conf=="Password:")||(conf=="password:")||(conf=="PASSWORD:")) fin >> spass;
        else if ((conf=="BotPassword:")||(conf=="botpassword:")||(conf=="BOTPASSWORD:")) fin >> bpass;
        else if ((conf=="log:")||(conf=="Log:")||(conf=="LOG:")) {string logs; fin >> logs;
            if ((logs=="true")||(logs=="TRUE")||(logs=="T")||(logs=="t")) log = true; else log = false;}
    }
    fin.close();
	return 0;
}

int init_log()
{
	return 0;
}
