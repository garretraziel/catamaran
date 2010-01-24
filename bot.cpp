#include "bot.h"
<<<<<<< HEAD
=======
//TODO: Message event a ChatState je presnej opak nez jsem si myslel, reimplementovat
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
void Bot::initiate(string aJID,string aPASS,string bPASS)
{
	JID jid( aJID );
	bpass = bPASS;
	cout << "# Debugstep 1\n";
	client = new Client( jid, aPASS );
	client -> registerConnectionListener( this );
	client -> disco() -> setVersion("Catamaran 0.01", GLOOX_VERSION);
	client -> disco() -> setIdentity("client","bot");

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
	cout << "# Debugstep 4: " << presence.presence()
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
	cout << "# Error: " << error << endl;
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
		cout << "# Newsession from: " << session->target().full() << endl;
	}
}

void Bot::handleMessage(const Message& message, MessageSession* session)
{
	cout << "@ Command from " << session->target().full() << ": "
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
			FILE* outp;
			char buffer[100];
			string outps="";
			outp = popen(message.body().c_str(),"r");
			while (true)
			{
				fgets(buffer,100,outp);
				if (feof(outp))
					break;
				outps=outps+buffer;
			}
			pclose(outp);
			cout << "& Output from command: " << outps << endl;
			if (outps!="") session->send(outps.c_str(),"Output");
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
	return 0;
}

int Bot::log()
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
<<<<<<< HEAD
	cout << "Blocklist stored, " << block_jid << " added.\n";
	m_session->send("Blocklist stored, "+block_jid+" added.","Blocklist");
=======
>>>>>>> e2d5bf0779ad4e07a38eeaf5eb781d9d462fdd76
	return 0;
}
