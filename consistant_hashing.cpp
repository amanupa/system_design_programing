#include <bits/stdc++.h>
using namespace std;

class ConsistentHashing {
    map<size_t, string> ring; // hash -> server

public:
    // hash function
    size_t getHash(const string &key) {
        return hash<string>{}(key);
    }

    // add server using virtual nodes
    void addServer(const string &server) {
    int VIRTUAL_NODES = 100;

    for (int i = 0; i < VIRTUAL_NODES; i++) {
        string vnode = server + "#" + to_string(i);
        ring[getHash(vnode)] = server;
    }
}
    
    void printRing() {
    cout << "\n--- Hash Ring ---\n";
    for (auto &entry : ring) {
        cout << entry.first << " → " << entry.second << endl;
    }
}

    // remove server
    void removeServer(const string &server) {
        size_t hashValue = getHash(server);
        ring.erase(hashValue);
    }

    // get server for a key
    string getServer(const string &key) {
        if (ring.empty()) return "";

        size_t hashValue = getHash(key);

        // find first server >= key hash
        auto it = ring.lower_bound(hashValue);

        // wrap around
        if (it == ring.end()) {
            it = ring.begin();
        }

        return it->second;
    }
};

int main() {
    ConsistentHashing ch;

    ch.addServer("Server1");
    ch.addServer("Server2");
    ch.addServer("Server3");

    vector<string> users = {"UserA", "UserB", "UserC", "UserD"};

    for (auto &user : users) {
        string server = ch.getServer(user);
        cout << user << " → " << server << endl;
    }
   ch.printRing();
}