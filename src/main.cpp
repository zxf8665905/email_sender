#include <iostream>
#include <fstream>
#include <string>
#include "sender.h"
#include "config.h"



void get_user_input(
    std::string &receiver_addr,
    std::string &receiver_name,
    std::string &email_subject, 
    std::string &email_body)
{
    std::cout << "Input receiver addr: ";
    std::cin >> receiver_addr;
    std::cout << "Input receiver name: ";
    std::cin >> receiver_name;
    std::cout << "Input email subject: ";
    std::cin >> email_subject;
    std::cout << "Input email body (support html format): ";
    std::cin >> email_body;
}


int main(int arc, char* argv[])
{
    auto config = Config("config.txt");
    config.Print();

    std::string receiver_addr;
    std::string receiver_name;
    std::string email_subject;
    std::string email_body; 

    get_user_input(
        receiver_addr,
        receiver_name,
        email_subject, 
        email_body);

    Sender email_sender(
        config.m_smtp_server, 
        config.m_smtp_port, 
        config.m_sender_addr, 
        config.m_sender_password, 
        config.m_sender_name);
    email_sender.AppendReceiver(receiver_addr, receiver_name);
    email_sender.SetContent(email_subject, email_body);
    email_sender.Send();

    return 0;
}
