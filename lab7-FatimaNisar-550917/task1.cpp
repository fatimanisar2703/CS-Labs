#include <iostream>
#include <string>
#include <stack>
using namespace std;
 
struct Node {
    char data;
    Node* left;
    Node* right;
};
 
Node* makeNode(char c) {
    Node* n = new Node;
    n->data = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}
 
Node* buildTree(string s, int &i) {
    if (i >= s.size() || s[i] == ',' || s[i] == ')')
        return NULL;
 
    Node* root = makeNode(s[i]);
    i++;
 
    if (i < s.size() && s[i] == '(') {
        i++;
        root->left = buildTree(s, i);
        i++;
        root->right = buildTree(s, i);
        i++;
    }
    return root;
}
 
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data;
    if (root->left != NULL || root->right != NULL) {
        cout << "(";
        preorder(root->left);
        cout << ",";
        preorder(root->right);
        cout << ")";
    }
}
 
void inorder(Node* root) {
    stack<Node*> st;
    Node* cur = root;
    while (cur != NULL || !st.empty()) {
        while (cur != NULL) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top();
        st.pop();
        cout << cur->data << " ";
        cur = cur->right;
    }
}
 
void postorder(Node* root) {
    stack<Node*> st;
    Node* cur = root;
    Node* last = NULL;
    while (cur != NULL || !st.empty()) {
        while (cur != NULL) {
            st.push(cur);
            cur = cur->left;
        }
        Node* top = st.top();
        if (top->right != NULL && top->right != last) {
            cur = top->right;
        } else {
            cout << top->data << " ";
            last = top;
            st.pop();
        }
    }
}
 
bool isValid(string s) {
    if (s.size() == 0 || !isalpha(s[0])) return false;
 
    stack<int> st;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
 
        if (isalpha(c)) {
            if (i > 0 && (isalpha(s[i - 1]) || s[i - 1] == ')')) return false;
        }
        else if (c == '(') {
            if (!isalpha(s[i - 1])) return false;
            st.push(0);
        }
        else if (c == ',') {
            if (st.empty() || st.top() != 0) return false;
            st.pop();
            st.push(1);
        }
        else if (c == ')') {
            if (st.empty() || st.top() != 1) return false;
            st.pop();
        }
        else {
            return false;
        }
    }
    return st.empty();
}
 
int height(Node* root) {
    if (root == NULL) return -1;
    int lh = height(root->left);
    int rh = height(root->right);
    if (lh > rh) return lh + 1;
    return rh + 1;
}
 
void printDepth(Node* root, int depth) {
    if (root == NULL) return;
    cout << "Node " << root->data << " -> depth " << depth << endl;
    printDepth(root->left, depth + 1);
    printDepth(root->right, depth + 1);
}
 
int main() {
    string s = "a(b(d,e),c(,f(g,)))";
    cout << "Given string: " << s << endl << endl;
 
    // Task 5
    cout << "Is the string valid? " << (isValid(s) ? "Yes" : "No") << endl;
    cout << "a(b(d,e),c(,f(g,)  -> " << (isValid("a(b(d,e),c(,f(g,))") ? "Valid" : "Invalid") << endl;
    cout << "a(b,c))            -> " << (isValid("a(b,c))") ? "Valid" : "Invalid") << endl;
    cout << "a(b,c,d)           -> " << (isValid("a(b,c,d)") ? "Valid" : "Invalid") << endl << endl;
 
    // Task 1
    int i = 0;
    Node* root = buildTree(s, i);
    cout << "Tree built successfully." << endl << endl;
 
    // Task 2, 3, 4
    cout << "Preorder  (recursive) : "; preorder(root);  cout << endl;
    cout << "Inorder   (stack)    : "; inorder(root);   cout << endl;
    cout << "Postorder (stack)     : "; postorder(root); cout << endl << endl;
 
    // Task 6
    cout << "Height of the tree: " << height(root) << endl;
    printDepth(root, 0);
 
    return 0;
}