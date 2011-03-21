#include "bot.h"
void Bot::initiate(string aJID,string aPASS,string bPASS,bool log_arg)
{
  JID jid( aJID );
  bpass = bPASS;
  log = log_arg;
  time_t rawtime;
  time(&rawtime);
  string cas = ctime(&rawtime);
  cas.erase(cas.length()-1,1);
  cout << "# Debugstep 1: " << cas << endl;
  client = new Client( jid, aPASS );
  client -> registerConnectionListener( this );
  client -> disco() -> setVersion("Catamaran 0.01", GLOOX_VERSION);
  client -> disco() -> setIdentity("client","bot");
  number_repeated_conn = 0;
  
  p = new PrivacyManager( client );
  p->registerPrivacyListHandler(this);

  client -> registerPresenceHandler( this );
  client -> registerMessageSessionHandler( this, 0 );
  client -> connect();
  
  delete( p );
  delete( client );
}

void Bot::onConnect()
{
  cout << "# catamaran is online\n";
  //onConnect udalosti
}

bool Bot::onTLSConnect( const CertInfo& info )
{
  //kontrola certifikatu
  return true;
}

void Bot::handlePresence(const Presence& presence )
{
  //handle udalosti s necim
  //TODO: tady se asi handluje stav lidi co si s catamaranem pisou, zkontrolovat
  time_t rawtime;
  time(&rawtime);
  string cas = ctime(&rawtime);
  cas.erase(cas.length()-1,1);
  cout << "# Debugstep 4 at " << cas << ": " << presence.presence()
       << " from " << presence.from().bare() << endl;
  if (presence.presence()==Presence::Available)
    {
      cout << "# Active JID = " << presence.from().full() << endl;
    }
  else if (presence.presence()==Presence::Unavailable&&presence.from().full()==handlerJid)
    {
      cout << "# JID gone = " << presence.from().bare() << endl;
      unpassed = false;
    }
}

void Bot::onDisconnect(ConnectionError error)
{
  //TODO: handle: 16 bad password, 9 offline, 0 no problem, 3 server reset, 17 user end
  time_t rawtime;
  time(&rawtime);
  string cas = ctime(&rawtime);
  cas.erase(cas.length()-1,1);
  if (error != ConnUserDisconnected) {
    cout << "# Error at " << cas << ": " << error << endl;
  }
  if (error == ConnStreamClosed) {
    //co se zase pripojit?
    if (number_repeated_conn < 10) {
      number_repeated_conn++;
      client -> connect();
    } else {
      cout << "# Warning: exceeted limit of repeated connections!\n";
    }
  }
}

void Bot::handleMessageSession(MessageSession* session)
{
  if (unpassed == false)
    {
      if ( m_session ) client -> disposeMessageSession( m_session );
      m_session = session;
      m_session->registerMessageHandler( this );
      m_messageEventFilter = new MessageEventFilter ( m_session );
      m_messageEventFilter -> registerMessageEventHandler(this);
      m_chatStateFilter = new ChatStateFilter( m_session );
      m_chatStateFilter -> registerChatStateHandler(this);
      time_t rawtime;
      time(&rawtime);
      string cas = ctime(&rawtime);
      cas.erase(cas.length()-1,1);
      cout << "# Newsession at " << cas << ": " << session->target().full() << endl;
    }
  else {
    time_t rawtime;
    time(&rawtime);
    string cas = ctime(&rawtime);
    cas.erase(cas.length()-1,1);
    cout << "# Cannot open new session, someone other is handling catamaran at " << cas << endl;
  }
}

void Bot::handleMessage(const Message& message, MessageSession* session)
{
  time_t rawtime;
  time(&rawtime);
  string cas = ctime(&rawtime);
  cas.erase(cas.length()-1,1);
  cout << "@ Command at " << cas << " from: " << session->target().full() << ": "
       << message.body() << endl;
  if (!unpassed)
    {
      if (message.body()==bpass)
	{
	  unpassed = true;
	  cout << "# Password is correct\n";
	  session->send("password is correct","Output");
	  handlerJid = session->target().full();
	}
      else
	{
	  cout << "# Password is not correct!\n";
	  session->send("password not correct","Fail");
	}
    }
  else
    {
      if (handlerJid != session->target().full())
	{
	  cout << "# False session from " << session->target().full()
	       << endl;
	  session->send("Someone other handlig gloox!","Fail");
	}
      else
	{
	  if (message.body().length() > 3 && message.body()[0] == '!' && message.body()[1] == '!') {
	    string rm_jid = message.body();
	    rm_jid.erase(0,2);
	    add_blocklist(rm_jid);
	  } else if (message.body().length() > 3 && message.body()[0] == '?' && message.body()[1] == '?') {
	    string allow_jid = message.body();
	    allow_jid.erase(0,2);
	    remove_blocklist(allow_jid);
	  } else if (message.body().length() > 3 && message.body()[0] == '#' && message.body()[1] == '#') {
	    string whatdo = message.body();
	    whatdo.erase(0,2);
	    do_spec(whatdo);
	  } else {
	    FILE* outp;
	    string outps="";
	    uint32_t znak;
	    outp = popen(message.body().c_str(),"r");
	    while((znak = getc(outp))!=EOF) outps+=znak;
	    pclose(outp);
	    cout << "& Output from command: " << outps << endl;
	    if (outps!="") session->send(outps,"Output");
	  }
	}
    }
}

void Bot::handleMessageEvent(const JID& jid, MessageEventType event)
{
  cout << "# Debugstep 3\n";
}

void Bot::handleChatState(const JID& jid, ChatStateType state)
{
  cout << "# Debugstep 2\n";
}
//TODO: Odsud dolu
void Bot::handlePrivacyListNames( const std::string& active, const std::string& def,
				  const StringList& lists )
{
}

void Bot::handlePrivacyListResult( const std::string& id, PrivacyListResult plResult )
{
}

void Bot::handlePrivacyList( const std::string& name, const PrivacyList& items )
{
}

void Bot::handlePrivacyListChanged( const std::string& name )
{
}

int Bot::add_command()
{
  return 0;
}

int Bot::do_command()
{
  return 0;
}

int Bot::send_file()
{
  //uvidime, jestli tohle vubec pujde udelat
  return 0;
}

int Bot::do_log()
{
  return 0;
}

int Bot::add_blocklist(string block_jid)
{
  PrivacyManager* p = new PrivacyManager(client);
  PrivacyListHandler::PrivacyList list;
  PrivacyItem item (PrivacyItem::TypeJid, PrivacyItem::ActionDeny, PrivacyItem::PacketMessage, block_jid);
  list.push_back( item );
  p -> store ("BlockList",list);
  cout << "@ Blocklist stored, " << block_jid << " added.\n";
  m_session->send("Blocklist stored, "+block_jid+" added.","Blocklist");
  return 0;
}
 
int Bot::remove_blocklist(string allow_jid)
{
  PrivacyManager* p = new PrivacyManager(client);
  PrivacyListHandler::PrivacyList list;
  PrivacyItem item (PrivacyItem::TypeJid, PrivacyItem::ActionAllow, PrivacyItem::PacketMessage, allow_jid);
  list.push_back( item );
  p -> store ("BlockList",list);
  cout << "@ Blocklist stored, " << allow_jid << " removed.\n";
  m_session->send("Blocklist stored, "+allow_jid+" removed.","Blocklist");
  return 0;
}

int Bot::do_spec(string whatdo)
{
  if (whatdo == "disconnect") {
    time_t rawtime;
    time(&rawtime);
    string cas = ctime(&rawtime);
    cout << "# Disconnecting at: " << cas;
    client -> disconnect();
  }
  // add new catamaran specific commands
  return 0;
}
