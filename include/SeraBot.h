#ifndef SERABOT_H
#define SERABOT_H

#include <dpp/dpp.h>
#include <string>
#include <sql.h>

///current task:
///do thing //this is a joke
///implement sql backup
///implement pip command
///implement run command (run attached file or run code in message)

std::string token_from_file(std::ifstream file);

class SeraBot : public dpp::cluster
{
    public:
        /** Default constructor */
        SeraBot(std::string bot_token);

        const std::string int_to_string(int _val);

    protected:
        void ready(const dpp::ready_t& event);
        void msg_event(const dpp::message_create_t& event);


    private:
        const static int minor_version = 4;
        const static int major_version = 0;
        const static int revision_number = 0;
};

#endif // SERABOT_H
