// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#include "braincloud/internal/RelayComms.h"

#include <braincloud/BrainCloudClient.h>
#include <braincloud/IRelayConnectCallback.h>
#include <braincloud/IRelayCallback.h>
#include <braincloud/IRelaySystemCallback.h>

static const int CONTROL_BYTES_SIZE = 1;
static const int CHANNEL_COUNT = 4;
static const int MAX_PACKET_ID_HISTORY = 128;

static const int MAX_PLAYERS = 128;
static const int INVALID_NET_ID = MAX_PLAYERS;

// Messages sent from Client to Relay-Server
static const int CL2RS_CONNECTION = 129;
static const int CL2RS_DISCONNECT = 130;
static const int CL2RS_RELAY = 131;
static const int CL2RS_PING = 133;
static const int CL2RS_RSMG_ACKNOWLEDGE = 134;
static const int CL2RS_ACKNOWLEDGE = 135;

// Messages sent from Relay-Server to Client
static const int RS2CL_RSMG = 129;
static const int RS2CL_PONG = CL2RS_PING;
static const int RS2CL_ACKNOWLEDGE = CL2RS_ACKNOWLEDGE;

static const int RELIABLE_BIT = 0x8000;
static const int ORDERED_BIT = 0x4000;

static const long CONNECT_RESEND_INTERVAL_MS = 500;

static const int MAX_PACKET_ID = 0xFFF;
static const int PACKET_LOWER_THRESHOLD = MAX_PACKET_ID * 25 / 100;
static const int PACKET_HIGHER_THRESHOLD = MAX_PACKET_ID * 75 / 100;

namespace BrainCloud
{
    RelayComms::RelayComms(BrainCloudClient* in_client)
        : m_client(in_client)
        , m_isInitialized(false)
    {
    }

    RelayComms::~RelayComms()
    {
    }

    void RelayComms::initialize()
    {
        m_isInitialized = true;
    }

    bool RelayComms::isInitialized()
    {
        return m_isInitialized;
    }

    void RelayComms::shutdown()
    {
        resetCommunication();
        m_isInitialized = false;
    }

    void RelayComms::resetCommunication()
    {
        disconnect();
    }

    void RelayComms::enableLogging(bool shouldEnable)
    {
        m_loggingEnabled = shouldEnable;
    }

    void RelayComms::connect(eRelayConnectionType in_connectionType, const RelayConnectOptions& in_options, IRelayConnectCallback* in_callback)
    {
    }

    void RelayComms::disconnect()
    {
    }

    bool RelayComms::isConnected() const
    {
        return false;
    }

    int RelayComms::getPing() const
    {
        return 999;
    }

    void RelayComms::setPingInterval(int in_intervalMS)
    {
    }

    const std::string& RelayComms::getOwnerProfileId() const
    {
        static std::string empty;
        return empty;
    }

    const std::string& RelayComms::getProfileIdForNetId(int in_netId) const
    {
        static std::string empty;
        return empty;
    }

    int RelayComms::getNetIdForProfileId(const std::string& in_profileId) const
    {
        return INVALID_NET_ID;
    }

    void RelayComms::registerRelayCallback(IRelayCallback* in_callback)
    {
    }

    void RelayComms::deregisterRelayCallback()
    {
    }

    void RelayComms::registerSystemCallback(IRelaySystemCallback* in_callback)
    {
    }

    void RelayComms::deregisterSystemCallback()
    {
    }

    void RelayComms::send(const uint8_t* in_data, int in_size, int in_toNetId, bool in_reliable, bool in_ordered, eRelayChannel in_channel)
    {
    }

    void RelayComms::runCallbacks()
    {
    }
};
