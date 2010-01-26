#ifndef BOT_H
#define BOT_H
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <gloox/gloox.h>
#include <gloox/client.h>
#include <gloox/clientbase.h>
#include <gloox/connectionhandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagehandler.h>
#include <gloox/presencehandler.h>
#include <gloox/rostermanager.h>
#include <gloox/mucroom.h>
#include <gloox/message.h>
#include <gloox/messagesession.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/pubsubmanager.h>
#include <gloox/messageeventhandler.h>
#include <gloox/messageeventfilter.h>
#include <gloox/chatstatehandler.h>
#include <gloox/chatstatefilter.h>
#include <gloox/privacymanager.h>
// # means void event, @ means commands, & is for output, $ for getting from user

using namespace std;
using namespace gloox;

class Bot : public ConnectionListener, PresenceHandler, MessageSessionHandler,
 MessageHandler, MessageEventHandler, ChatStateHandler, PrivacyListHandler
{
public:
	Bot() {unpassed=false; handlerJid = "";expmode = false;log = false;}
	void initiate(string aJID,string aPASS,string bPASS,bool log_arg);
	virtual void handlePresence(const Presence& presence );
	virtual void onDisconnect(ConnectionError error);
	virtual void onConnect();
	virtual void handleMessage(const Message& message, MessageSession* session);
	virtual bool onTLSConnect( const CertInfo& info );
	virtual void handleMessageSession(MessageSession* session);
	virtual void handleMessageEvent(const JID& jid, MessageEventType event);
	virtual void handleChatState(const JID& jid, ChatStateType state);
	virtual void handlePrivacyListNames( const std::string& active, const std::string& def,
                                         const StringList& lists );
    virtual void handlePrivacyListResult( const std::string& id, PrivacyListResult plResult );
    virtual void handlePrivacyList( const std::string& name, const PrivacyList& items );
    virtual void handlePrivacyListChanged( const std::string& name );
private:
	Client* client;
	PrivacyManager *p;
	MessageSession* m_session;
	MessageEventFilter* m_messageEventFilter;
	ChatStateFilter* m_chatStateFilter;
	string bpass;
	bool expmode;
	bool unpassed;
	bool log;
	string handlerJid;
	int add_command();
	int do_command();
	int exp_mode(){expmode=!expmode;return 0;};
	int send_file();
	int do_log();
	int add_blocklist(string block_jid);
};


#endif
