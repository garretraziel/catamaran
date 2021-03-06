//TODO: konfigurace spusteni
//TODO: parsovani argumentu
//TODO: trace chyb pripojeni
//TODO: akce pri zachyceni
//TODO: user mod
//TODO: zapouzdreni do objektu
//TODO: logovani
//TODO: filetransfer
//TODO: handle odpojeni
//TODO: vypis erroru
//TODO: registrace na serveru
//TODO: ovladani na zaklade Ad-Hoc (mozna)
//TODO: resource na zaklade $HOSTNAME (mozna)
//TODO: GUI, mozna na zaklade ncurses
//TODO: odpojovani clienta pomoci client -> disconnect()
#include <iostream>
#include <fstream>
#include <string>
#include "version.h"
#include "bot.h"
#include "output.h"


using namespace std;

int handle_argv(int argc, char *argv[]);

int parse_config(const char* file, string& sJID, string& spass, string& bpass, bool& log);

int init_log();

int main(int argc, char *argv[])
{
	if ((argc == 2)&&(!strcmp(argv[1],"-v"))) {
		cout << AutoVersion::FULLVERSION_STRING << endl;
		return 0;}
	if ((argc == 2)&&(!strcmp(argv[1],"-h"))) {
		system("cat README");
		return 0;}
    FILE* outp;
    string outps = "";
    uint32_t znak;
    outp = popen("id -u","r");
    while ((znak=getc(outp))!='\n') outps+=znak;
    pclose(outp);
    if (outps=="0") {
        cout << "# Not so good idea to run under root. Continue anyway? y/n ";
        string potvrzeni;
        getline(cin,potvrzeni);
        if (potvrzeni=="n") return 0;
    }
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
      fin.close();
      parse_config(configfile.c_str(),sJID,spass,bpass,log);
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

int parse_config(const char* file, string& sJID, string& spass, string& bpass, bool& log)
{
    ifstream fin;
    fin.open(file);
    string conf;
    while (fin.good())
    {
        fin >> conf;
        if ((conf=="JID:")||(conf=="jid:")) {fin >> sJID; getline(fin,conf);}
        else if ((conf=="Password:")||(conf=="password:")||(conf=="PASSWORD:")) {fin >> spass; getline(fin,conf);}
        else if ((conf=="BotPassword:")||(conf=="botpassword:")||(conf=="BOTPASSWORD:")) {fin >> bpass; getline(fin,conf);}
        else if ((conf=="log:")||(conf=="Log:")||(conf=="LOG:")) {string logs; fin >> logs;
            if ((logs=="true")||(logs=="TRUE")||(logs=="T")||(logs=="t")) log = true; else log = false; getline(fin,conf);}
        else if (conf[0]=='/'&&conf[1]=='/') getline(fin,conf);
        else if (conf=="") ; else cout << "# Error parsing from config file: \"" << conf << "\" means nothing\n";
    }
    fin.close();
	return 0;
}

int init_log()
{
    return 0;
}
