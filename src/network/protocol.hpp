#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <regex>
#include <queue>


// same things with different name for better clarity in code
/** Data received from client. */
using ClientData = std::queue<std::string>;
/** Parsed data received from client */
using Request = std::queue<std::string>;

namespace Protocol {

    // examples of protocol message

    // C -> S
    // {c,n:nick}
    // {m:07050710}

    // S -> C
    // {rr,il}
    // {rr,ig,ty,op:onick,pf:0..9}
    // -> {rr,ig,ty,op:onick,pf:0000000000111111111122222222223333333333444444444455555555550000000000111111111122222222223333333333}
    // {ig,ty,op:nick}

    // operation codes
    static const std::string OP_SOH     ("{"); // start of header
    static const std::string OP_EOT     ("}"); // end of transmission
    static const std::string OP_SEP     (","); // separator
    static const std::string OP_INI     (":"); // initializer of data
    static const std::string OP_PING    (">"); // enquiry
    static const std::string OP_PONG    ("<"); // acknowledge

    // client codes
    static const std::string CC_CONN    ("c"); // connect request
    static const std::string CC_RECN    ("r"); // reconnect request
    static const std::string CC_NAME    ("n"); // name
    static const std::string CC_MOVE    ("m"); // move
    static const std::string CC_LEAV    ("l"); // leave game
    static const std::string CC_EXIT    ("e"); // exit connection

    // server codes
    static const std::string SC_RESP_CONN    ("rc"); // response connect
    static const std::string SC_RESP_RECN    ("rr"); // response reconnect
    static const std::string SC_RESP_LEAVE   ("rl"); // response leave
    static const std::string SC_IN_LOBBY     ("il"); // client moved to lobby
    static const std::string SC_IN_GAME      ("ig"); // client moved to game
    static const std::string SC_MV_VALID     ("mv"); // valid move
    static const std::string SC_TURN_YOU     ("ty"); // your's turn
    static const std::string SC_TURN_OPN     ("to"); // opponent's turn
    static const std::string SC_PLAYFIELD    ("pf"); // playfield
    static const std::string SC_GO_WIN       ("gw"); // game over win
    static const std::string SC_GO_LOSS      ("gl"); // game over loss
    static const std::string SC_OPN_NAME     ("on"); // opponent's name
    static const std::string SC_OPN_MOVE     ("om"); // opponent's move
    static const std::string SC_OPN_LEAVE    ("ol"); // opponent left the game
    static const std::string SC_OPN_EXIT     ("oe"); // opponent disconnected
    static const std::string SC_OPN_RECN     ("or"); // opponent reconnected
    static const std::string SC_MANY_PLRS    ("t");  // too many players message
    static const std::string SC_NAME_USED    ("u");  // name is already used
    static const std::string SC_KICK         ("k");  // kick client

    // chat code
    static const std::string OP_CHAT         ("ch"); // chat

    // server regex -- valid format: (?:\{(?:<|>|c,n:\w{3,20}|r,n:\w{3,20}|m:\d{8}|l|e|ch:[\w\s.,!?]{1,100})\})+
    static const std::regex rgx_valid_format(R"((?:\{(?:<|>|c,n:\w{3,20}|r,n:\w{3,20}|m:\d{8}|l|e|ch:[\w\s.,!?]{1,100})\})+)");
    // server regex -- valid data in curly brackets: <|>|c,n:\w{3,20}|r,n:\w{3,20}|m:\d{8}|l|e|ch:[\w\s.,!?]{1,100}
    static const std::regex rgx_data(R"(<|>|c,n:\w{3,20}|r,n:\w{3,20}|m:\d{8}|l|e|ch:[\w\s.,!?]{1,100})");
    // server regex -- valid subdata in data: [^,]+
    static const std::regex rgx_subdata(R"([^,]+)");
    // server regex -- valid keys and values in subdata: [^:]+
    static const std::regex rgx_key_value(R"([^:]+)");

    // client regex -- valid format: (?:\{(?:<|>|rc|rr,il|rr,ig,(?:ty|to),on:\w{3,20},pf:\d{100}|rl|il|ig,(?:ty|to),on:\w{3,20}|mv|gw|gl|om:\d{8}|ol|oe|or|t|u|k|ch:[\w\s.,!?]{1,100})\})+
    // client regex -- valid data in curly brackets: <|>|rc|rr,il|rr,ig,(?:ty|to),on:\w{3,20},pf:\d{100}|rl|il|ig,(?:ty|to),on:\w{3,20}|mv|gw|gl|om:\d{8}|ol|oe|or|t|u|k|ch:[\w\s.,!?]{1,100}
}


#endif