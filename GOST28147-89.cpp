#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
class ObfusG {
public:
    enum class CipherMode {
        Encrypt,
        Decrypt
    };

    string process_text(const string& text, CipherMode mode) {
        string result;
        for (size_t i = 0; i < text.length(); i += 8) {
            uint64_t data = str_to_block(text.substr(i, 8));
            uint64_t processed_data = process_block(data, mode);
            result += block_to_str(processed_data);
        }
        return result;
    }

private:
    vector<uint32_t> k = { 0xFFFFFFFF, 0xABCD1234, 0x5678EFEF, 0x98765432, 0xFEDCBA12, 0x11223344, 0xAABBCCDD, 0x55667788 };
    vector<vector<uint8_t>> s = {
        {4, 7, 1, 9, 0, 2, 4, 8, 6, 3, 11, 12, 13, 14, 15, 10},
        {12, 6, 11, 2, 10, 4, 7, 5, 9, 0, 1, 3, 8, 13, 14, 15},
        {7, 2, 5, 0, 11, 14, 15, 10, 9, 12, 8, 1, 3, 4, 6, 13},
        {8, 14, 7, 6, 2, 5, 1, 15, 4, 0, 11, 10, 13, 9, 12, 3},
        {15, 6, 9, 11, 3, 12, 4, 2, 10, 8, 1, 0, 7, 14, 4, 13},
        {12, 15, 0, 9, 4, 8, 13, 2, 11, 10, 7, 6, 5, 3, 14, 1},
        {14, 3, 1, 10, 7, 15, 13, 12, 0, 2, 11, 4, 8, 9, 6, 5},
        {6, 8, 15, 4, 10, 7, 12, 1, 2, 0, 14, 5, 11, 3, 9, 13}
    };

    uint32_t F(uint32_t r, uint32_t ki) {
        r = (r + ki) & 0xFFFFFFFF;
        r = sub(r);
        return (r << 11) & 0xFFFFFFFF;
    }

    uint32_t sub(uint32_t r) {
        uint32_t result = 0;
        for (int i = 0; i < 8; ++i) {
            result |= (s[i][(r >> (4 * i)) & 0xF] << (4 * i));
        }
        return result;
    }

    pair<uint32_t, uint32_t> process_round(uint32_t left, uint32_t right, uint32_t round_key, CipherMode mode) {
        uint32_t new_left, new_right;
        if (mode == CipherMode::Encrypt) {
            new_left = right;
            new_right = left ^ F(right, round_key);
        }
        else {
            new_right = left;
            new_left = right ^ F(left, round_key);
        }
        return make_pair(new_left, new_right);
    }

    uint64_t process_block(uint64_t b, CipherMode mode) {
        uint32_t l = b >> 32;
        uint32_t r = b & 0xFFFFFFFF;
        for (int i = 0; i < 32; ++i) {
            uint32_t ki;
            if (mode == CipherMode::Encrypt) {
                ki = (i < 24) ? k[i % 8] : k[7 - (i % 8)];
            }
            else {
                ki = (i < 8) ? k[i] : k[7 - (i % 8)];
            }
            auto result = process_round(l, r, ki, mode);
            l = result.first;
            r = result.second;
        }
        return ((uint64_t)l << 32) | r;
    }

    static uint64_t str_to_block(const string& t) {
        string bin_s;
        for (char c : t) {
            bin_s += bitset<8>(c).to_string();
        }
        bin_s.resize(64, '0');
        return bitset<64>(bin_s).to_ullong();
    }

    static string block_to_str(uint64_t b) {
        string bin_s = bitset<64>(b).to_string();
        string res;
        for (int i = 0; i < 64; i += 8) {
            res += static_cast<char>(bitset<8>(bin_s.substr(i, 8)).to_ulong());
        }
        return res;
    }
};

int main() {
    ObfusG cipher;
    string t = "Text";
    string encrypted_res = cipher.process_text(t, ObfusG::CipherMode::Encrypt);
    cout << "Encrypted: " << encrypted_res << endl;

    string decrypted_res = cipher.process_text(encrypted_res, ObfusG::CipherMode::Decrypt);
    cout << "Decrypted: " << decrypted_res << endl;

    return 0;
}