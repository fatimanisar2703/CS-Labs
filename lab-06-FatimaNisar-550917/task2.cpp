
#include <iostream>
#include <string>
using namespace std;

const int MAX = 1000;

// Stack for strings
class StringStack {
    string data[MAX];
    int topIndex;

public:
    StringStack() { topIndex = -1; }

    bool empty() {
        return topIndex == -1;
    }

    bool push(string s) {
        if (topIndex == MAX - 1) return false;
        data[++topIndex] = s;
        return true;
    }

    string pop() {
        if (empty()) return "";
        return data[topIndex--];
    }

    string top() {
        if (empty()) return "";
        return data[topIndex];
    }
};

// Part A: Bracket validator
bool isValidBrackets(string s) {
    char stack[MAX];
    int top = -1;

    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];

        if (c == '(' || c == '{' || c == '[') {
            if (top == MAX - 1) return false;
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) return false;

            char opening = stack[top--];

            if ((c == ')' && opening != '(') ||
                (c == '}' && opening != '{') ||
                (c == ']' && opening != '['))
                return false;
        }
    }

    return top == -1;
}

// Check if character can be part of a tag name
bool isNameChar(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           c == '-' || c == '_' || c == ':' || c == '.';
}

// Part B: Simplified HTML/XML validator
bool validate_markup(string s) {
    StringStack tags;
    bool valid = true;
    int errors = 0;

    for (int i = 0; i < (int)s.length();) {
        if (s[i] != '<') {
            i++;
            continue;
        }

        // Skip comments: <!-- ... -->
        if (s.substr(i, 4) == "<!--") {
            size_t end = s.find("-->", i + 4);
            if (end == string::npos) {
                cout << "Error: Unclosed comment\n";
                return false;
            }
            i = (int)end + 3;
            continue;
        }

        int end = i + 1;
        char quote = '\0';

        // Find > while ignoring > inside quotes
        while (end < (int)s.length()) {
            if (quote != '\0') {
                if (s[end] == quote) quote = '\0';
            } else if (s[end] == '"' || s[end] == '\'') {
                quote = s[end];
            } else if (s[end] == '>') {
                break;
            }
            end++;
        }

        if (end == (int)s.length()) {
            cout << "Error: Tag is missing >\n";
            return false;
        }

        string tag = s.substr(i + 1, end - i - 1);

        // Ignore declarations such as <!DOCTYPE html>
        if (tag.length() > 0 && tag[0] == '!') {
            i = end + 1;
            continue;
        }

        // Ignore processing instructions such as <?xml ...?>
        if (tag.length() > 0 && tag[0] == '?') {
            i = end + 1;
            continue;
        }

        bool closing = false;
        bool selfClosing = false;
        int p = 0;

        while (p < (int)tag.length() && tag[p] == ' ')
            p++;

        if (p < (int)tag.length() && tag[p] == '/') {
            closing = true;
            p++;
        }

        while (p < (int)tag.length() && tag[p] == ' ')
            p++;

        int start = p;

        while (p < (int)tag.length() && isNameChar(tag[p]))
            p++;

        if (start == p) {
            cout << "Error: Invalid tag near position " << i << endl;
            valid = false;
            errors++;
            i = end + 1;
            continue;
        }

        string name = tag.substr(start, p - start);

        // Self-closing tag ends with /
        int last = (int)tag.length() - 1;
        while (last >= 0 && tag[last] == ' ') last--;

        if (last >= 0 && tag[last] == '/')
            selfClosing = true;

        if (closing) {
            if (selfClosing) {
                cout << "Error: Invalid closing tag </"
                     << name << "/>\n";
                valid = false;
                errors++;
            } else if (tags.empty()) {
                cout << "Error: Unexpected closing tag </"
                     << name << ">\n";
                valid = false;
                errors++;
            } else if (tags.top() != name) {
                cout << "Error: Mismatched closing tag </"
                     << name << ">, expected </"
                     << tags.top() << ">\n";
                valid = false;
                errors++;
            } else {
                tags.pop();
            }
        } else if (!selfClosing) {
            if (!tags.push(name)) {
                cout << "Error: Tag stack overflow\n";
                return false;
            }
        }

        i = end + 1;
    }

    while (!tags.empty()) {
        cout << "Error: Missing closing tag for <"
             << tags.pop() << ">\n";
        valid = false;
        errors++;
    }

    if (valid)
        cout << "Markup is valid.\n";
    else
        cout << "Markup has " << errors << " error(s).\n";

    return valid;
}

int main() {
    int choice;
    string input;

    do {
        cout << "\n--- Validator Menu ---\n";
        cout << "1. Validate brackets\n";
        cout << "2. Validate HTML/XML markup\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        if (choice == 1) {
            cout << "Enter expression: ";
            getline(cin, input);

            if (isValidBrackets(input))
                cout << "Brackets are balanced.\n";
            else
                cout << "Brackets are NOT balanced.\n";
        } else if (choice == 2) {
            cout << "Enter markup on one line: ";
            getline(cin, input);
            validate_markup(input);
        }
    } while (choice != 0);

    return 0;
}
