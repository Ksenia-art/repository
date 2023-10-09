#include <iostream>

using namespace std;

#include <iostream>
#include <string>
#include <unordered_map>

string shiftText(const string& text, int shift) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            char shiftedChar = ((c - base + shift) % 26 + 26) % 26 + base;
            result += shiftedChar;
        }
        else {
            result += c;
        }
    }
    return result;
}

string encodeText(const string& text, int shift) {
    return shiftText(text, shift);
}

string decodeText(const string& text, int shift) {
    return shiftText(text, -shift);
}

int findCharDifference(const string& text) {
    string lowercaseText = text;
    for (char& c : lowercaseText) {
        c = tolower(c);
    }

    unordered_map<char, int> charCounts;
    for (char c : lowercaseText) {
        if (isalpha(c)) {
            charCounts[c]++;
        }
    }

    char mostFrequentChar = 'e'; // Default value if the text is empty
    int maxCount = 0;

    for (const auto& entry : charCounts) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mostFrequentChar = entry.first;
        }
    }

    return abs('e' - mostFrequentChar);
}

int main() {
    string text = "Either the well was very deep, or she fell very slowly, for she had plenty of time as she went down to look about her and to wonder what was going to happen next. First, she tried to look down and make out what she was coming to, but it was too dark to see anything; then she looked at the sides of the well, and noticed that they were filled with cupboards and book-shelves; here and there she saw maps and pictures hung upon pegs. She took down a jar from one of the shelves as she passed; it was labelled 'ORANGE MARMALADE', but to her great disappointment it was empty: she did not like to drop the jar for fear of killing somebody, so managed to put it into one of the cupboards as she fell past it.'Well!' thought Alice to herself, 'after such a fall as this, I shall think nothing of tumbling down stairs! How brave they'll all think me at home! Why, I wouldn't say anything about it, even if I fell off the top of the house!' (Which was very likely true.)";
    string encodedMessage = encodeText(text, 5);
    int charDifference = findCharDifference(encodedMessage);
    string decodedMessage = decodeText(encodedMessage, charDifference);

    cout << "Encoded Message: " << encodedMessage << endl;
    cout << "Decoded Message: " << decodedMessage << endl;
    cout << "Character Difference: " << charDifference << endl;

    return 0;
}