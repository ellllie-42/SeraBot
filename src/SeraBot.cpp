#include <iostream>
#include <sstream>
#include <iomanip>

#include "SeraBot.h"
#include "python_interpreter.h"


//decompile command?

SeraBot::SeraBot(std::string bot_token) :
    dpp::cluster(bot_token)
{
    this->on_log(dpp::utility::cout_logger());
    std::cout<<"Hello world!"<<std::endl;
    std::cout<<"SeraBot_V" << SeraBot::int_to_string(SeraBot::major_version) << "." << SeraBot::int_to_string(SeraBot::minor_version) << "." << SeraBot::int_to_string(SeraBot::revision_number) <<std::endl;
    ///**I love you**///
    //8

    //i added the following code to encourage me to actually work on this
    this->on_ready([this](const dpp::ready_t& event){this->ready(event);});
    this->on_message_create([this](const dpp::message_create_t& event){this->msg_event(event);});
}

void SeraBot::ready(const dpp::ready_t& event)
{
    if (dpp::run_once<struct register_bot_commands>())
    {
        this->set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_game, "with " + std::to_string(event.guild_count) + " guilds!"));
        this->start_timer([this](const dpp::timer& timer)
                    {
                        this->set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_game, "with " + std::to_string(dpp::get_guild_cache()->count()) + " guilds!"));
                    }, 120);
    }
}



void SeraBot::msg_event(const dpp::message_create_t& event)
{
    std::cout<<"Author: " << event.msg.author.username << std::endl;
    if(event.msg.author == this->me)
    {
        event.cancel_event();
        return;
    }
    event.reply("Hello world!", true);
}

const std::string SeraBot::int_to_string(int _val)
{
    std::stringstream ss;
    ss << std::setw(_val > 9 ? 1 : 0) << std::setfill('0') << _val;
    return ss.str();
}
