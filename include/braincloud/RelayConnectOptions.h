// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#ifndef _RELAYCONNECTOPTIONS_H_
#define _RELAYCONNECTOPTIONS_H_

#include <string>

namespace BrainCloud
{
    struct RelayConnectOptions
    {
        bool ssl = false;
        std::string host;
        int port = 0;
        std::string passcode;
        std::string lobbyId;
    };
};

#endif /* _RELAYCONNECTOPTIONS_H_ */
