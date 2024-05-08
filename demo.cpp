#include <iostream>
#include <string>
using namespace std;
bool equal0(string a) {
    string newString;
    string z = "0";
    for (auto i = a.begin(); i <= a.end(); i++) {
        if (!isspace(*i) && *i != '\0') {
            newString.push_back(*i);
        }
    }

    return newString.compare(z) == 0;
}
int main() {
    std::string s = "s ";
    std::string t = "s";
    s += ' ';
    s += 'f';
    cout << s << endl;;
    std::string a = "sfd g sgf fdg s hfd g hf ";
    for (auto i = a.begin(); i <= a.end(); i++) {
        if (!isspace(*i)) {
            cout << *i;
        }
    }
    const auto sl = equal0("  0         ");
    cout << (sl ? "true" : "false") << endl;
    cout << (char)48 << endl;
}