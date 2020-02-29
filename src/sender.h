#ifndef _SENDER_H_
#define	_SENDER_H_
 
#include <string>
#include <vector>
#include <utility>

#include "curl/curl.h"

#define SENDER_LOG_ON 1
#define SENDER_LOG_OFF 0
#define SENDER_LOG_STATE SENDER_LOG_ON

class Sender 
{
public:
    Sender(const std::string& smtp_server,
                const int smtp_port,
                const std::string& sender_email,
                const std::string& sender_password,
                const std::string& sender_name="");
    ~Sender();
    void SetContent(const std::string& subject="", const std::string& body=""); // support html format
    void AppendReceiver(const std::string& receiver_addr, const std::string& receiver_name="");
    void Send();

private:
    std::string m_smtp_url;
    std::pair<std::string, std::string> m_sender_info;    // (addr, name)
    std::string m_sender_password;
    std::vector<std::pair<std::string, std::string>> m_receivers_info; // [(email,name), ...]
    std::string m_subject;
    std::string m_body;
};
 
 
#endif
