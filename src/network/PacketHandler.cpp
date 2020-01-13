#include <string>

#include "PacketHandler.hpp"
#include "protocol.hpp"


// ---------- CONSTRUCTORS & DESTRUCTORS










// ---------- PRIVATE METHODS










// ---------- PUBLIC METHODS






int PacketHandler::isValidFormat(const std::string& msg) {
    // same reason for 1 as false like in Server::serveClient()
    int valid = 1;

    if (std::regex_match(msg, Protocol::rgx_valid_format)) {
        valid = 0;
    }

    return valid;
}

void PacketHandler::parseMsg(std::string msg, clientData& data) {
    std::smatch match;

    // search every brackets with data in message and emplace it to vector
    while (regex_search(msg, match, Protocol::rgx_data)) {
        data.emplace(match.str());
        msg = match.suffix();
    }
}
