// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#ifndef _RELAYCONNECTIONTYPE_H_
#define _RELAYCONNECTIONTYPE_H_

namespace BrainCloud
{
    enum class eRelayConnectionType : int
    {
        WEBSOCKET = 0,
        TCP = 1,
        UDP = 2
    };
};

#endif /* _RELAYCONNECTIONTYPE_H_ */
