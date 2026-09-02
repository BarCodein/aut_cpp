#include "bst.h"

void bst_delete(BST::Node*& node);


BST::Node::Node(int value, Node* left, Node* right)
    :value(value),left(left),right(right){}

BST::Node::Node():value(0),left(nullptr),right(nullptr){}

BST::Node::Node(const Node& node):
value(node.value),left(node.left),right(node.right){}


std::ostream& operator<<(std::ostream& os,BST::Node& node){
    os << &node << " " << node.value << " " << node.left <<" " << node.right
        <<std::endl;
    return os;

}

bool operator==(const BST::Node& a, const int& b){return a.value==b;}

bool operator>=(const BST::Node& a, const int& b){return a.value>=b;}

bool operator<=(const BST::Node& a, const int& b){return a.value<=b;}

bool operator<(const BST::Node& a, const int& b){return a.value<b;}

bool operator>(const BST::Node& a, const int& b){return a.value>b;}


bool operator==(const int& a, const BST::Node& b){return a==b.value;}

bool operator<=(const int& a, const BST::Node& b){return a<=b.value;}

bool operator>=(const int& a, const BST::Node& b){return a>=b.value;}

bool operator<(const int& a, const BST::Node& b){return a<b.value;}

bool operator>(const int& a, const BST::Node& b){return a>b.value;}





BST::BST(){
    root = nullptr;
}

BST::BST(std::initializer_list<int> list){
    root = nullptr;
    for(int item : list)
        add_node(item);
}

void traverse(std::vector<int>& values,const BST::Node* node){
    if (node == nullptr)return;
    if (node!=nullptr)values.push_back(node->value);
    if (node->left!=nullptr)
        traverse(values,node->left);
    if (node->right!=nullptr)
        traverse(values,node->right);
}

BST& BST::operator=(const BST& other){
    if (this == &other)return *this;
    bst_delete(root);
    root =  nullptr;
    std::vector<int> values;
    traverse(values,other.root);
    for(auto val : values){
        add_node(val);
    }
    return *this;
}

BST& BST::operator=(BST&& other){
    root = other.root;
    other.root = nullptr;
    return *this;
}

BST::BST(const BST& other){
    if (this == &other)return;
    root =  nullptr;
    std::vector<int> values;
    traverse(values,other.root);
    for(auto val : values){
        add_node(val);
    }
}

BST::BST(BST&& other){
    root = other.root;
    other.root = nullptr;
}

BST::Node*& BST::get_root(){
    return root;
}

void bfs_helper(std::function<void(BST::Node*& node)> fuc,BST::Node*& node){
    if (node == nullptr)return;
    fuc(node);
    if (node->left!=nullptr)
        bfs_helper(fuc,node->left);
    if (node->right!=nullptr)
        bfs_helper(fuc,node->right);
    
}


void BST::bfs(std::function<void(Node*& node)> fuc){
    bfs_helper(fuc,root);
}

size_t length_helper(BST::Node*& node){
    if(node==nullptr)return 0;
    return length_helper(node->left)+length_helper(node->right)+1;
}

size_t BST::length(){
    return length_helper(root);
}


bool BST::add_node(int value){
    if (BST::find_node(value)!=nullptr)return false;
    if(length()==0){
        root = new Node(value,nullptr,nullptr);
    }
    else{
        Node* parent = *(BST::find_parrent(value));
        Node* node = new Node(value,nullptr,nullptr);
        if(value>parent->value)parent->right = node;
        else parent->left = node;
    }
    return true;
}

BST::Node** BST::find_node(int value){
    if (root==nullptr)return nullptr;
    Node* node = root;
    while(node!=nullptr && node->value!=value){
        if (value>*node)node = node->right;
        else node = node->left;
    }
    if(node==nullptr)return nullptr;
    return new Node*(node);
}


BST::Node** BST::find_parrent(int value){
    Node* node = root;
    Node* parent = nullptr;
    while(node!=nullptr && node->value!=value){
        if (value>*node){
            parent = node;
            node = node->right;
        }
        else{
            parent = node;
            node = node->left;
        }
    }
    return new Node*(parent);
}

BST::Node** BST::find_successor(int value){
    Node** node = find_node(value);
    if(node==nullptr)return nullptr;
    if((*node)->left!=nullptr){
        node = &(*node)->left;
        while((*node)->right!=nullptr)
            node = &(*node)->right;
        return node;
    }
    else if((*node)->right!=nullptr){
        node = &(*node)->right;
        while((*node)->left!=nullptr)
            node = &(*node)->left;
        return node;
    }
    else return nullptr;
}

bool BST::delete_node(int value){
    Node** node = find_node(value);
    if (node == nullptr)return false;
    Node** successor = find_successor(value);
    if (successor == nullptr){
        if (*node == root)
            root = nullptr;
        else{
            Node** parent = find_parrent(value);
            delete (*node);
            if (value>**parent)
                (*parent)->right = nullptr;
            else
                (*parent)->left = nullptr;
            delete parent;
        }
    }
    else{
        int svalue = (*successor)->value;
        Node** successor_parent = find_parrent(svalue);
        if (svalue > **successor_parent)
            (*successor_parent)->right = nullptr;
        else
            (*successor_parent)->left = nullptr;
        (*node)->value = svalue;
        delete (*successor);
        delete successor_parent;
    }
    delete node;
    return true;
}

std::ostream& operator<<(std::ostream& os,BST& bst){
    printf("*************************************\n");
    auto fuc = [](BST::Node*& node)->void{std::cout<<(*node);};
    bst.bfs(fuc);
    std::cout<<"binary search tree size: "<<bst.length()<<std::endl;
    printf("*************************************\n");
    return os;
}

BST& BST::operator++(){
    auto fuc = [](BST::Node*& node)->void{node->value+=1;};
    bfs(fuc);
    return *this;
}

BST BST::operator++(int){
    BST tmp = *this;
    auto fuc = [](BST::Node*& node)->void{node->value+=1;};
    bfs(fuc);
    return tmp;
}

void bst_delete(BST::Node*& node){
    if(node==nullptr)return;
    if(node->left!=nullptr)bst_delete(node->left);
    if(node->right!=nullptr)bst_delete(node->right);
    delete node;
}

BST::~BST(){
    bst_delete(root);
}