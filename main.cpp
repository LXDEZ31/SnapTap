#include <windows.h>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace std;
using namespace std::chrono;

atomic<bool> running(true);
atomic<bool> snapActive(true);
mutex io_mutex;

int getOppositeKey(int key) {
    switch (key) {
        case 'W': return 'S';
        case 'S': return 'W';
        case 'A': return 'D';
        case 'D': return 'A';
        default: return 0;
    }
}

void clearTerminal() {
    system("cls"); 
}

void printStatus() {
    clearTerminal();
    cout << "==========================" << endl;
    cout << " SnapTap Durumu: " << (snapActive ? "[AKTIF ]" : "[PASIF ]") << endl;
    cout << "==========================" << endl;
    cout << "(Insert tusuyla ac/kapat, 'kapat' yazarak cikis)" << endl;
}

bool isKeyDown(int vk) {
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

void tapKey(int vk) {
    INPUT input[2] = {};
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = vk;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = vk;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

void snapTapCounterStrafe() {
    unordered_map<int, bool> wasPressed;
    static bool insertPrev = false;

    printStatus(); 

    while (running) {
        
        bool insertNow = isKeyDown(VK_INSERT);
        if (insertNow && !insertPrev) {
            snapActive = !snapActive;
            printStatus();
        }
        insertPrev = insertNow;

        if (snapActive) {
            for (int key : { 'W', 'A', 'S', 'D' }) {
                bool down = isKeyDown(key);

                if (down && !wasPressed[key]) {
                    wasPressed[key] = true;
                }
                else if (!down && wasPressed[key]) {
                    int opposite = getOppositeKey(key);
                    if (opposite) {
                        lock_guard<mutex> lock(io_mutex);
                        cout << ">> " << (char)key << " bırakıldı -> " << (char)opposite << " tap!" << endl;

                        tapKey(opposite);
                        this_thread::sleep_for(milliseconds(20));
                    }
                    wasPressed[key] = false;
                }
            }
        }

        this_thread::sleep_for(milliseconds(5));
    }
}

void inputThread() {
    string cmd;
    while (running) {
        getline(cin, cmd);
        if (cmd == "kapat") {
            running = false;
            break;
        }
    }
}

int main() {
    cout << "SnapTap Basladi. Insert ile ac/kapat. 'kapat' yazarak cik.\n";

    thread logicThread(snapTapCounterStrafe);
    thread consoleThread(inputThread);

    logicThread.join();
    consoleThread.join();

    cout << "Program kapatildi." << endl;
    return 0;
}
