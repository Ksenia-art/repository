#include <iostream>
#include <string>
#include <cmath>

using namespace std;
long long mod_pow(long long base, long long exponent, long long mod) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}

int main() {
    // ��������� ������
    long long p = 61;  // ������� ����� 1
    long long q = 53;  // ������� ����� 2
    long long N = p * q;  // ������������ ������� �����
    long long PHI = (p - 1) * (q - 1);  // ������� ������

    long long e = 17;  // �������� ���������� (������ ���� ������� ������ � PHI)

    // ������ �������� ���������� d, ����� ��� (d * e) mod PHI = 1
    long long d = 1;
    while ((d * e) % PHI != 1) {
        d++;
    }

    // ���� ��������� ��� ����������
    string message = "Hello, RSA!";

    // ����������
    string encrypted_message;
    for (char letter : message) {
        long long m = static_cast<long long>(letter);
        long long c = mod_pow(m, e, N);
        encrypted_message += to_string(c) + " ";
    }

    // ������������
    string decrypted_message;
    for (size_t i = 0; i < encrypted_message.length(); i++) {
        if (encrypted_message[i] == ' ') {
            continue;
        }
        long long c = stoll(encrypted_message.substr(i));
        long long m = mod_pow(c, d, N);
        decrypted_message += static_cast<char>(m);
        while (i < encrypted_message.length() && encrypted_message[i] != ' ') {
            i++;
        }
    }

    cout << "Original Message: " << message << endl;
    cout << "Encrypted Message: " << encrypted_message << endl;
    cout << "Decrypted Message: " << decrypted_message << endl;

    return 0;
}