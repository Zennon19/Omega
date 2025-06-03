// Solo.h
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <Curl/curl.h>
#include <Json/json.hpp>

// Struct to hold a game server's info
struct GameServer {
    std::string name;
    std::string url;
    std::string region;
    std::string status;
    int maxPlayers;
    int currentPlayers;
};

class SoloConnector {
public:
    SoloConnector(const std::string& jsonUrl) : serverListUrl(jsonUrl) {}

    bool fetchServers();
    void printServers();
    const std::vector<GameServer>& getServers() const { return servers; }

private:
    std::string serverListUrl;
    std::vector<GameServer> servers;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
};
