#define _WIN32_WINNT 0x0A00 
#include <iostream>
#include <string>

#include "httplib.h"
#include "blockchain.h"

using namespace std;

int main() {
    Blockchain blockchain;

    httplib::Server server;

    server.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("{\"status\":\"ok\"}", "application/json");
    });

    server.listen("0.0.0.0", 18080);

    // Register User
    server.Post("/register", [&](const httplib::Request& req, httplib::Response& res) {
        auto userId = req.get_param_value("userId");

        bool ok = blockchain.registerUser(userId);

        if (ok) {
            res.set_content("User registered successfully\n", "text/plain");
        } else {
            res.status = 400;
            res.set_content("User already exists\n", "text/plain");
        }
    });

    // Create Block
    server.Post("/block", [&](const httplib::Request& req, httplib::Response& res) {
        auto userId = req.get_param_value("userId");
        auto content = req.get_param_value("content");

        bool ok = blockchain.createBlock(userId, content);

        if (ok) {
            res.set_content("Block created successfully\n", "text/plain");
        } else {
            res.status = 400;
            res.set_content("Block creation failed\n", "text/plain");
        }
    });

    // Verify Ownership (ZKP)

    server.Post("/verify", [&](const httplib::Request& req, httplib::Response& res) {
        auto userId = req.get_param_value("userId");
        auto content = req.get_param_value("content");

        bool ok = blockchain.verifyOwnership(userId, content);

        if (ok) {
            res.set_content("Ownership verified successfully\n", "text/plain");
        } else {
            res.status = 400;
            res.set_content("Ownership verification failed\n", "text/plain");
        }
    });

    // View Blockchain

    server.Get("/chain", [&](const httplib::Request&, httplib::Response& res) {
        std::ostringstream out;

        const auto& chain = blockchain.getChain();
        for (const auto& b : chain) {
            out << "Block #" << b.index << "\n";
            out << "Creator: " << b.creatorID << "\n";
            out << "IP Hash: " << b.ipHash << "\n";
            out << "Prev Hash: " << b.prevHash << "\n";
            out << "Block Hash: " << b.blockHash << "\n";
            out << "----------------------\n";
        }

        res.set_content(out.str(), "text/plain");
    });

    cout << "Server running at http://localhost:18080\n";
    server.listen("0.0.0.0", 18080);

    return 0;
}
