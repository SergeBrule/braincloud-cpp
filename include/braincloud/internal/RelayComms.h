// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#ifndef _RELAYCOMMS_H_
#define _RELAYCOMMS_H_

#include "braincloud/RelayChannel.h"
#include "braincloud/RelayConnectionType.h"
#include "braincloud/RelayConnectOptions.h"

#include <cinttypes>

namespace BrainCloud
{
    class BrainCloudClient;
    class IRelayConnectCallback;
    class IRelayCallback;
    class IRelaySystemCallback;

    class RelayComms
    {
    public:
        RelayComms(BrainCloudClient* in_client);
        virtual ~RelayComms();

        void initialize();
        bool isInitialized();
        void shutdown();
        void resetCommunication();
        void runCallbacks();
        void enableLogging(bool shouldEnable);

        void connect(eRelayConnectionType in_connectionType, const RelayConnectOptions& in_options, IRelayConnectCallback* in_callback);
        void disconnect();
        bool isConnected() const;
        int getPing() const;
        void setPingInterval(int in_intervalMS);
        const std::string& getOwnerProfileId() const;
        const std::string& getProfileIdForNetId(int in_netId) const;
        int getNetIdForProfileId(const std::string& in_profileId) const;
        void registerRelayCallback(IRelayCallback* in_callback);
        void deregisterRelayCallback();
        void registerSystemCallback(IRelaySystemCallback* in_callback);
        void deregisterSystemCallback();
        void send(const uint8_t* in_data, int in_size, int in_toNetId, bool in_reliable, bool in_ordered, eRelayChannel in_channel);

    private:
        BrainCloudClient* m_client = nullptr;
        bool m_isInitialized = false;
        bool m_loggingEnabled = false;
    };
};

#endif /* _RELAYCOMMS_H_ */
