#ifndef _CONFIG_H_
#define	_CONFIG_H_

#include <iostream>
#include <fstream>
#include <string>

class Config
{
    public:
        std::string m_smtp_server;
        int m_smtp_port;
        std::string m_sender_addr;
        std::string m_sender_password;
        std::string m_sender_name;
        Config(std::string file_path);
        void Print();
};
#endif