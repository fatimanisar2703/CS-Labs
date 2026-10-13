
#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

const int MAX = 500;

// Stack for strings
class StringStack {
    string arr[MAX];
    int topIndex;

public:
    StringStack() { topIndex = -1; }

    bool isEmpty() { return topIndex == -1; }

    void push(string x) {
        if (topIndex < MAX - 1)
            arr[++topIndex] = x;
    }

    string pop() {
        if (isEmpty()) return "";
        return arr[topIndex--];
    }

    string top() {
        if (isEmpty()) return "";
        return arr[topIndex];
    }
};

// Stack for numbers
class NumberStack {
    double arr[MAX];
    int topIndex;

public:
    NumberStack() { topIndex = -1; }

    bool isEmpty() { return topIndex == -1; }

    void push(double x) {
        if (topIndex < MAX - 1)
            arr[++topIndex] = x;
    }

    double pop() {
        if (isEmpty()) throw "Invalid expression";
        return arr[topIndex--];
    }
};

// Split expression into tokens
int tokenize(string s, string tokens[]) {
    int count = 0;

    for (int i = 0; i < (int)s.length();) {
        if (isspace((unsigned char)s[i])) {
            i++;
        } else if (isdigit((unsigned char)s[i]) || s[i] == '.') {
            string number;

            while (i < (int)s.length() &&
                  (isdigit((unsigned char)s[i]) || s[i] == '.'))
                number += s[i++];

            tokens[count++] = number;
        } else if (isalpha((unsigned char)s[i])) {
            string word;

            while (i < (int)s.length() &&
                   isalpha((unsigned char)s[i]))
                word += s[i++];

            tokens[count++] = word;
        } else {
            tokens[count++] = string(1, s[i++]);
        }

        if (count >= MAX) break;
    }

    return count;
}

bool isOperator(string op) {
    return op == "+" || op == "-" || op == "*" ||
           op == "/" || op == "^";
}

int precedence(string op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool isRightAssociative(string op) {
    return op == "^";
}

string joinTokens(string arr[], int n) {
    string result;

    for (int i = 0; i < n; i++) {
        if (i > 0) result += " ";
        result += arr[i];
    }

    return result;
}

// Convert infix to postfix
string infix_to_postfix(string expr) {
    string tokens[MAX], output[MAX];
    StringStack operators;
    int n = tokenize(expr, tokens), k = 0;

    for (int i = 0; i < n; i++) {
        string t = tokens[i];

        if (!isOperator(t) && t != "(" && t != ")") {
            output[k++] = t;
        } else if (t == "(") {
            operators.push(t);
        } else if (t == ")") {
            while (!operators.isEmpty() && operators.top() != "(")
                output[k++] = operators.pop();

            if (operators.isEmpty())
                throw "Mismatched parentheses";

            operators.pop();
        } else {
            while (!operators.isEmpty() &&
                   operators.top() != "(" &&
                  (precedence(operators.top()) > precedence(t) ||
                  (precedence(operators.top()) == precedence(t) &&
                   !isRightAssociative(t)))) {
                output[k++] = operators.pop();
            }

            operators.push(t);
        }
    }

    while (!operators.isEmpty()) {
        if (operators.top() == "(")
            throw "Mismatched parentheses";

        output[k++] = operators.pop();
    }

    return joinTokens(output, k);
}

// Reverse tokens and swap parentheses
string reverseExpression(string expr) {
    string tokens[MAX], result[MAX];
    int n = tokenize(expr, tokens);

    for (int i = 0; i < n; i++) {
        result[i] = tokens[n - 1 - i];

        if (result[i] == "(") result[i] = ")";
        else if (result[i] == ")") result[i] = "(";
    }

    return joinTokens(result, n);
}

// Convert infix to prefix
string infix_to_prefix(string expr) {
    string reversed = reverseExpression(expr);
    string tokens[MAX], output[MAX];
    StringStack operators;
    int n = tokenize(reversed, tokens), k = 0;

    for (int i = 0; i < n; i++) {
        string t = tokens[i];

        if (!isOperator(t) && t != "(" && t != ")") {
            output[k++] = t;
        } else if (t == "(") {
            operators.push(t);
        } else if (t == ")") {
            while (!operators.isEmpty() && operators.top() != "(")
                output[k++] = operators.pop();

            if (operators.isEmpty())
                throw "Mismatched parentheses";

            operators.pop();
        } else {
            while (!operators.isEmpty() && operators.top() != "(" &&
                  (precedence(operators.top()) > precedence(t) ||
                  (precedence(operators.top()) == precedence(t) &&
                   isRightAssociative(t)))) {
                output[k++] = operators.pop();
            }

            operators.push(t);
        }
    }

    while (!operators.isEmpty()) {
        if (operators.top() == "(")
            throw "Mismatched parentheses";

        output[k++] = operators.pop();
    }

    for (int i = 0; i < k / 2; i++) {
        string temp = output[i];
        output[i] = output[k - 1 - i];
        output[k - 1 - i] = temp;
    }

    return joinTokens(output, k);
}

// Convert postfix to infix
string postfix_to_infix(string expr) {
    string tokens[MAX];
    StringStack operands;
    int n = tokenize(expr, tokens);

    for (int i = 0; i < n; i++) {
        string t = tokens[i];

        if (!isOperator(t)) {
            operands.push(t);
        } else {
            if (operands.isEmpty()) throw "Invalid postfix expression";
            string b = operands.pop();

            if (operands.isEmpty()) throw "Invalid postfix expression";
            string a = operands.pop();

            operands.push("(" + a + " " + t + " " + b + ")");
        }
    }

    if (operands.isEmpty()) throw "Invalid postfix expression";
    string result = operands.pop();

    if (!operands.isEmpty()) throw "Invalid postfix expression";
    return result;
}

// Convert numeric text to a number
double toNumber(string s) {
    int i = 0;
    double value = 0, fraction = 0, divisor = 10;
    bool decimal = false;

    if (s.empty()) throw "Invalid number";

    for (int j = 0; j < (int)s.length(); j++) {
        if (s[j] == '.') {
            if (decimal) throw "Invalid number";
            decimal = true;
            continue;
        }

        if (!isdigit((unsigned char)s[j]))
            throw "Evaluation requires numeric operands";

        int digit = s[j] - '0';

        if (!decimal)
            value = value * 10 + digit;
        else {
            fraction += digit / divisor;
            divisor *= 10;
        }

        i++;
    }

    if (i == 0) throw "Invalid number";
    return value + fraction;
}

// Perform calculation
double calculate(double a, double b, string op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;

    if (op == "/") {
        if (b == 0) throw "Division by zero";
        return a / b;
    }

    if (op == "^") return pow(a, b);

    throw "Invalid operator";
}

// Evaluate postfix
double evaluate_postfix(string expr) {
    string tokens[MAX];
    NumberStack numbers;
    int n = tokenize(expr, tokens);

    for (int i = 0; i < n; i++) {
        string t = tokens[i];

        if (!isOperator(t)) {
            numbers.push(toNumber(t));
        } else {
            double b = numbers.pop();
            double a = numbers.pop();
            numbers.push(calculate(a, b, t));
        }
    }

    double result = numbers.pop();

    if (!numbers.isEmpty()) throw "Invalid expression";
    return result;
}

// Evaluate prefix
double evaluate_prefix(string expr) {
    string tokens[MAX];
    NumberStack numbers;
    int n = tokenize(expr, tokens);

    for (int i = n - 1; i >= 0; i--) {
        string t = tokens[i];

        if (!isOperator(t)) {
            numbers.push(toNumber(t));
        } else {
            double a = numbers.pop();
            double b = numbers.pop();
            numbers.push(calculate(a, b, t));
        }
    }

    double result = numbers.pop();

    if (!numbers.isEmpty()) throw "Invalid expression";
    return result;
}

int main() {
    int choice;
    string expr;

    do {
        cout << "\n--- Expression Menu ---\n";
        cout << "1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Postfix to Infix\n";
        cout << "4. Evaluate Postfix\n";
        cout << "5. Evaluate Prefix\n";
        cout << "0. Exit\nChoice: ";

        cin >> choice;
        cin.ignore(10000, '\n');

        if (choice >= 1 && choice <= 5) {
            cout << "Enter expression: ";
            getline(cin, expr);

            try {
                if (choice == 1)
                    cout << infix_to_postfix(expr) << endl;
                else if (choice == 2)
                    cout << infix_to_prefix(expr) << endl;
                else if (choice == 3)
                    cout << postfix_to_infix(expr) << endl;
                else if (choice == 4)
                    cout << evaluate_postfix(expr) << endl;
                else
                    cout << evaluate_prefix(expr) << endl;
            } catch (const char* error) {
                cout << "Error: " << error << endl;
            }
        }
    } while (choice != 0);

    return 0;
}
