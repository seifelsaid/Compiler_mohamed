#include <iostream>
#include <stack>
#include <vector>
using namespace std;
string terminals = {
    '=', '+', '-', '*', '/', '%', '|', '\\', '&', '^', '!', '#', '(', ')', '{', '}', '[', ']', '\'', ';', ':', ',', '.',
    '\"', '~', '`', '_'
};
stack<char> st;
int idx;
string input;
vector<pair<char, string>> grammar(4);

bool is_terminal(char n){
    return (islower(n) || isdigit(n) || terminals.find(n) != string::npos);
}

bool is_simple_grammar(){
    for (auto i : grammar){
        if (is_terminal(i.first) || !is_terminal(i.second[0])){
            return false;
        }
    }
    if (grammar[0].second[0] == grammar[1].second[0] || grammar[2].second[0] == grammar[3].second[0]){
        return false;
    }
    return true;
}

bool solve(){

    while (!st.empty()){
        if (idx==input.size()){break;}
        char top = st.top();
        if (is_terminal(top)){
            if (top == input[idx]){
                st.pop();
                idx++;
            }
            else
                return false;
        }
        else if (!is_terminal(top)){
            int non_terminal;
            int rule;
            if (top == 'S')
                non_terminal = 0;
            else if (top == 'B')
                non_terminal = 2;
            else
                return false;
            if (input[idx] == grammar[non_terminal].second[0])
                rule = 0;
            else if (input[idx] == grammar[non_terminal + 1].second[0])
                rule = 1;
            else
                return false;
            st.pop();
            for (int i = (int)grammar[non_terminal + rule].second.size()-1; i >= 0; i--){
                st.push(grammar[non_terminal + rule].second[i]);
            }
        }
        else
            return false;
    }
    if (st.empty() && idx == input.size())
        return true;
    return false;
}

int main(){
    while (true){
        grammar[0].first = 'S';
        grammar[1].first = 'S';
        grammar[2].first = 'B';
        grammar[3].first = 'B';

        for (int i = 1; i <= 4; i++){
            char non_terminal = i < 3 ? 'S' : 'B';
            cout << "Enter rule number " << i << " for non-terminal \'" << non_terminal << "\': ";
            cin >> grammar[i - 1].second;
            cout << endl;
        }

        if (!is_simple_grammar()){
            cout << "Not a simple grammar" << endl;
            continue;
        }
        while (true){
            cout << "Enter the string to be checked: ";
            cin >> input;
            cout << "The input string: ";
            cout << " [";
            for (int i=0;i<input.size();i++){ cout << '\'' << input[i] << '\'';if (i!=input.size()-1) cout << ", "; }
            cout << "]";
            cout << endl;
            while (!st.empty()){st.pop();}
            idx = 0;
            st.push('S');

            bool f = solve();
            cout << "Stack after checking: " << "[ ";
            while (!st.empty()){
                char i = st.top();
                st.pop();
                cout << '\'' << i << '\'';
                if (!st.empty()) cout << ", ";
            }
            cout << "]";
            cout << endl;
            cout << "The rest of the unchecked string: ";
            cout << " [";
            for (int i = idx; i < input.size(); i++){ cout << '\'' << input[i] << '\''; if (i!=input.size()-1) cout << ", "; }
            cout << "]";
            cout << endl;
            if (f)
                cout << "The input string is Accepted.\n";
            else
                cout << "The input string is Rejected.\n";
            cout << "1- Another grammar.\n";
            cout << "2- Another string.\n";
            cout << "3- Exit.\n";
            int t;
            cin >> t;
            if (t == 1)
                break;
            if (t == 3)
                return 0;
        }
    }
}
