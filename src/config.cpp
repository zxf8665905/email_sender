#include "config.h"


Config::Config(std::string file_path)
{

    std::ifstream file(file_path);
    std::string str;

    std::getline(file, m_smtp_server);
    std::getline(file, str);
    m_smtp_port = atoi(str.c_str());
    std::getline(file, m_sender_addr);
    std::getline(file, m_sender_password);
    std::getline(file, m_sender_name);

}

void Config::Print()
{
    std::cout << "---------Sender email config---------" << std::endl;
    std::cout << "m_smtp_server=" + m_smtp_server << std::endl;
    std::cout << "m_smtp_port=" << m_smtp_port << std::endl;
    std::cout << "m_sender_addr=" + m_sender_addr << std::endl;
    std::cout << "m_sender_password=" + m_sender_password << std::endl;
    std::cout << "m_sender_name=" + m_sender_name << std::endl;
    std::cout << "------------------------" << std::endl;

}