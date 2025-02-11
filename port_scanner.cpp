#include <iostream>
#include <winsock2.h> // Windows-specific socket header
#include <thread> // For multi-threading
#include <vector>
#include <chrono>
#pragma comment(lib, "ws2_32.lib") // Link winsock library

const int MAX_THREADS = 100; // Limit to 100 threads at a time

void scanPort(const char* ip, int port) {
    SOCKET sock;
    struct sockaddr_in server;
    WSADATA wsa;

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock == INVALID_SOCKET) {
        std::cerr << "Could not create socket." << std::endl;
        return;
    }

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    
    // Set timeout to detect firewalled ports
    struct timeval timeout;      
    timeout.tv_sec = 2;  // 2 seconds timeout
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    
    // Try to connect to the port
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == 0) {
        std::cout << "[+] Port " << port << " is open." << std::endl;
    } else {
        std::cout << "[-] Port " << port << " is closed or filtered." << std::endl;
    }
    
    closesocket(sock);
    WSACleanup();
}

int main() {
    char ip[16];
    int startPort, endPort;
    
    std::cout << "Enter target IP: ";
    std::cin >> ip;
    
    std::cout << "Enter start port: ";
    std::cin >> startPort;
    
    std::cout << "Enter end port: ";
    std::cin >> endPort;
    
    std::vector<std::thread> threads;
    for (int port = startPort; port <= endPort; port++) {
        if (threads.size() >= MAX_THREADS) {
            // Wait for threads to finish before creating new ones
            for (auto& t : threads) {
                if (t.joinable()) t.join();
            }
            threads.clear();
        }
        threads.emplace_back(scanPort, ip, port);
    }
    
    // Join remaining threads before exiting
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
    
    std::cout << "\nPress any key to exit..." << std::endl;
    system("pause >nul");
    
    return 0;
}
