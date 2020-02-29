#include "sender.h"


Sender::Sender(const std::string& smtp_server,
                         const int smtp_port,
                         const std::string& sender_email,
                         const std::string& sender_password,
                         const std::string& sender_name)
{
    // init sender config
    m_smtp_url = "smtp://" + smtp_server + ':' + std::to_string(smtp_port); // smtp://example.com
    m_sender_info = std::make_pair(sender_email, sender_name);
    m_sender_password = sender_password;
}

Sender::~Sender()
{
    m_receivers_info.clear();
}

void Sender::SetContent(const std::string& subject,
                                  const std::string& body)
{
    // set email title and body content
    m_subject = subject;
    m_body = body;
}

void Sender::AppendReceiver(const std::string& receiver_addr, const std::string &receiver_name)
{
    // add receiver to list
    m_receivers_info.push_back(std::make_pair(receiver_addr, receiver_name));
}


void Sender::Send()
{
    // here init curl and do smtp email send
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl)
    {
        struct curl_slist *headers = NULL;
        struct curl_slist *recipients = NULL;

        curl_mime *mime;
        curl_mime *alt;
        curl_mimepart *part;

        /* This is the URL for your mailserver */
        curl_easy_setopt(curl, CURLOPT_URL, m_smtp_url.c_str());

        /* Login smtp server to verify */
        curl_easy_setopt(curl, CURLOPT_USERNAME, m_sender_info.first.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, m_sender_password.c_str());

        /* Note that this option isn't strictly required, omitting it will result
       * in libcurl sending the MAIL FROM command with empty sender data. All
       * autoresponses should have an empty reverse-path, and should be directed
       * to the address in the reverse-path which triggered them. Otherwise,
       * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
       * details.
       */
        auto sender_addr = '<' + m_sender_info.first + '>'; // should be like <example@126.com>
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, sender_addr.c_str());

        /* Add recipients, in this particular case they correspond to the
       * To: and Cc: addressees in the header, but they could be any kind of
       * recipient. */
        // receiver
        for (auto &email_pair : m_receivers_info)
        {
            std::string email_addr = '<' + email_pair.first + '>';
            recipients = curl_slist_append(recipients, email_addr.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        /* Build and set the message header list. */
        std::string header;

        header += "From:";
        header += m_sender_info.second + '<' + m_sender_info.first + '>' + "\n";

        header += "To:";
        for (int i = 0; i < m_receivers_info.size(); i++)
        {
            header += m_receivers_info[i].second += '<' + m_receivers_info[i].first + '>';
            if (i != m_receivers_info.size() - 1)
                header += ',';
        }
        header += "\n";

        header += "Subject:";
        header += m_subject + "\n";


        headers = curl_slist_append(headers, header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        /* Build the mime message. */
        mime = curl_mime_init(curl);

        /* The inline part is an alternative proposing the html and the text
         versions of the e-mail. */
        alt = curl_mime_init(curl);

        /* HTML message. */
        part = curl_mime_addpart(alt);
        curl_mime_data(part, m_body.c_str(), CURL_ZERO_TERMINATED);
        curl_mime_type(part, "text/html");
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, alt);

        /* Send the message */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, SENDER_LOG_STATE);
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* Free lists. */
        curl_slist_free_all(recipients);
        curl_slist_free_all(headers);

        /* curl won't send the QUIT command until you call cleanup, so you should
       * be able to re-use this connection for additional messages (setting
       * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
       * curl_easy_perform() again. It may not be a good idea to keep the
       * connection open for a very long time though (more than a few minutes
       * may result in the server timing out the connection), and you do want to
       * clean up in the end.
       */
        curl_easy_cleanup(curl);

        /* Free multipart message. */
        curl_mime_free(mime);
    }
}
