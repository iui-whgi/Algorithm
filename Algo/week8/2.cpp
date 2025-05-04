#include <bits/stdc++.h>
using namespace std;

struct Node {
    char data;  int freq;
    Node *left, *right;
    Node(char d, int f): data(d), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) const {
        if (a->freq != b->freq) return a->freq > b->freq;
        bool aLeaf = a->data != '\0', bLeaf = b->data != '\0';
        if (aLeaf && bLeaf) return a->data > b->data;
        if (aLeaf != bLeaf) return !aLeaf;      // leaf 가 먼저
        return false;
    }
};

void preorder(Node* r){
    if (!r) return;
    cout << (r->data ? r->data : '+') << ':' << r->freq;
    if (r->left || r->right){ cout << ' '; preorder(r->left);
        if (r->right) cout << ' '; preorder(r->right); }
}
void inorder(Node* r){
    if (!r) return;
    if (r->left){ inorder(r->left); cout << ' '; }
    cout << (r->data ? r->data : '+') << ':' << r->freq;
    if (r->right){ cout << ' '; inorder(r->right); }
}
void makeCode(Node* r,string s, unordered_map<char,string>& mp){
    if(!r) return;
    if(!r->left && !r->right){ mp[r->data]=s; return; }
    makeCode(r->left, s+'0', mp);
    makeCode(r->right,s+'1', mp);
}
string encode(const string& t,const unordered_map<char,string>& mp){
    string out; for(char c:t) out+=mp.at(c); return out;
}
string decode(const string& bits, Node* root){
    string out; Node* cur=root;
    for(char b:bits){
        cur=(b=='0'?cur->left:cur->right);
        if(!cur->left&&!cur->right){ out+=cur->data; cur=root; }
    } return out;
}

int main(){
    // freopen("input2.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;                cin >> N;
    vector<char> ch(N);   for(auto& c:ch) cin >> c;
    vector<int>  fr(N);   for(auto& f:fr) cin >> f;

    priority_queue<Node*,vector<Node*>,Compare> pq;
    for(int i=0;i<N;++i) pq.push(new Node(ch[i],fr[i]));

    while(pq.size()>1){
        Node* l=pq.top(); pq.pop();
        Node* r=pq.top(); pq.pop();
        Node* p=new Node('\0',l->freq+r->freq);
        p->left=l; p->right=r; pq.push(p);
    }
    Node* root=pq.top();

    unordered_map<char,string> code;
    makeCode(root,"",code);

    preorder(root); cout << '\n';
    inorder(root);  cout << '\n';

    int M; cin >> M;
    for(int i=0;i<M;++i){
        string s; cin >> s;
        cout << encode(s,code) << '\n';
    }
    int K; cin >> K;
    for(int i=0;i<K;++i){
        string bits; cin >> bits;
        cout << decode(bits,root) << '\n';
    }
    return 0;
}
