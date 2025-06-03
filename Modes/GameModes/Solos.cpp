#include "Solos.h"

size_t SoloConnector::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

bool SoloConnector::fetchServers() {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string jsonResponse;
    curl_easy_setopt(curl, CURLOPT_URL, serverListUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "GameClient/1.0");

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Failed to fetch servers: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    try {
        auto json = nlohmann::json::parse(jsonResponse);
        for (const auto& item : json["GameServers"]) {
            GameServer server;
            server.name = item["name"];
            server.url = item["url"];
            server.region = item["region"];
            server.status = item["status"];
            server.maxPlayers = item["maxPlayers"];
            server.currentPlayers = item["currentPlayers"];
            servers.push_back(server);
        }
    } catch (const std::exception& e) {
        std::cerr << "JSON parsing failed: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void SoloConnector::printServers() {
    for (const auto& server : servers) {
        std::cout << "Name: " << server.name << ", URL: " << server.url
                  << ", Region: " << server.region << ", Status: " << server.status
                  << ", Players: " << server.currentPlayers << "/" << server.maxPlayers << std::endl;
    }
}
