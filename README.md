# C++ Port Scanner

## 🔹 Overview
This is a **multi-threaded TCP port scanner** written in C++ for detecting open, closed, or firewalled ports.

## 🚀 Features
- Scans a given **IP address** for open ports.
- Uses **multi-threading** to speed up scanning.
- **Detects firewalled ports** using timeouts.
- Supports **Windows (Winsock2)**.

## 🛠 Installation & Usage
### **🔹 Compilation (Windows)**
1. Ensure you have **MinGW (G++)** installed.
2. Open **Command Prompt** in the project folder.
3. Compile the program using:
   ```sh
   g++ port_scanner.cpp -o port_scanner.exe -lws2_32

Legal Disclaimer

This tool is intended for educational purposes only.
Do not scan systems without explicit permission.
