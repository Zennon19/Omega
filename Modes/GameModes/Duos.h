// Duos.h
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// Struct to hold a game server's info for Duos
struct DuoServer {
    std::string name;
    std::string url;
    std::string region;
    std::string status;
    int maxPlayers;
    int currentPlayers;
};

class DuosConnector {
public:
    DuosConnector(const std::string& jsonUrl) : serverListUrl(jsonUrl) {}

    bool fetchServers();
    void printServers();
    const std::vector<DuoServer>& getServers() const { return servers; }

private:
    std::string serverListUrl;
    std::vector<DuoServer> servers;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
};
