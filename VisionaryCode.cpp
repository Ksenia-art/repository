#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
string encrypt(const string& message, const string& key) {
    string crypted;
    int keyLength = key.length();
    for (size_t i = 0; i < message.length(); i++) {
        char32_t symbol = message[i];
        if (isalpha(symbol)) {
            char base = islower(symbol) ? 'a' : 'A';
            int messageChar = symbol - base;
            int keyChar = key[i % keyLength] - base;
            int cryptedChar;
            cryptedChar = (messageChar + keyChar + 26) % 26 + base;
            crypted.push_back(static_cast<char>(cryptedChar));
        }
        else {
            crypted.push_back(symbol);
        }
    }
    return crypted;
}

string decrypt(const string& message, const string& key) {
    string crypted;
    int keyLength = key.length();
    for (size_t i = 0; i < message.length(); i++) {
        char32_t symbol = message[i];
        if (isalpha(symbol)) {
            char base = islower(symbol) ? 'a' : 'A';
            int messageChar = symbol - base;
            int keyChar = key[i % keyLength] - base;
            int cryptedChar;
            cryptedChar = (messageChar - keyChar + 26) % 26 + base;
            crypted.push_back(static_cast<char>(cryptedChar));
        }
        else {
            crypted.push_back(symbol);
        }
    }
    return crypted;
}

int main() {
    string startMessage, key;

    cout << "Message(eng): ";
    getline(cin, startMessage);

    cout << "Key(eng): ";
    getline(cin, key);

    key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
    key.erase(remove_if(key.begin(), key.end(), [](unsigned char c) { return !isalpha(c); }), key.end());

    cout << "Encrypted message: " << encrypt(startMessage, key) << endl;
    cout << "Decrypted message: " << decrypt(encrypt(startMessage, key), key) << endl;

    return 0;
}