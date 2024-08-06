#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

#define LEFT 0;
#define RIGHT 1;

#define MAX(a, b) (a > b ? a : b)

enum class Rotate
{

    LL,
    LR,
    RR,
    RL,
    NO,
    //Tree에 이미 있는 key를 입력 받았을때 표현.
    OVERLAP,

};

struct Node
{

    Node* left{ nullptr };
    int height{ 1 };
    int key{ 0 };
    int BF{ 0 };
    int noNodes{ 0 };
    Node* right{ nullptr };

    Node(int key)
    {
        this->key = key;
    }

};

class AVLTree
{

public:

    //node를 삽입하는 method 입니다.
    Rotate insertAVL(Node* root, int key)
    {
        //tree에 노드가 없을때.
        if (root == nullptr)
        {
            this->T = new Node(key);
            return Rotate::NO;
        }

        //이전 삽입, 삭제에 사용했던 vector를 초기화 합니다.
        vector.clear();

        Node* p{ nullptr };
        Node* q{ nullptr };

        //회전 타입.
        Rotate rotate{ Rotate::NO };

        //삽입만 수행(BF체크와 높이 계산 수행 X)
        rotate = insertBST(root, key);
        
        //중복 데이터가 들어왔을때 OVERLAP type을 return 합니다.
        if (rotate == Rotate::OVERLAP)
            return rotate;

        //삽입 후 높이를 재계산하고 BF체크 합니다.
        rotate = checkBalance(p, q);

        //밸런스가 깨졌으면 rotate합니다.
        if (rotate != Rotate::NO)
            rotateTree(rotate, q, p);

        return rotate;

    }

    //노드를 삽입합니다. BST
    Rotate insertBST(Node* root, int key)
    {

        Node* parent{ nullptr };
        Node* child{ root };

        //insert position을 찾는다.
        while (child)
        {
            //경로상의 노드들을 vector에 저장.
            vector.push_back(child);

            parent = child;

            if (child->key > key)
                child = child->left;

            else if (child->key < key)
                child = child->right;

            //key가 이미 tree에 있는 경우.
            else
            {
                std::cout << "i " << key << " : The key already exists" << std::endl;
                return Rotate::OVERLAP;
            }

        }

        //새 노드를 어디에 삽일할지 결정하고 삽입합니다.
        if (parent->key > key)
        {
            parent->left = getNode(key);
            child = parent->left;
            child->BF = 0;
        }
        else
        {
            parent->right = getNode(key);
            child = parent->right;
            child->BF = 0;
        }

        //중복데이터가 아닌 노드를 성공적으로 삽입하면 일단 NO를 리턴.
        return Rotate::NO;

    }

    //삽입 연산시 Node를 동적할당 해주는 method입니다.
    Node* getNode(int newKey)
    {
        Node* newNode = new Node(newKey);
        return newNode;
    }

    // BF를 체크하기 전에 먼저 높이를 재계산합니다.
    // node를 insert할때 tree의 balance를 확인합니다.
    // or 노드를 삭제하고 난 후 tree의 balance를 확인합니다.
    // or 회전을 한 후 tree의 balance를 확인합니다.
    // 불균형이 발생하면, 발생한 노드 p와 그 노드의 부모 노드 q, 그리고 회전의 종류, rotationType을 리턴.
    Rotate checkBalance(Node*& child, Node*& parent)
    {

        Rotate rotateType{ Rotate::NO };

        //삭제 연산을 할 때 root node하나만 있을때의 예외처리.
        if (vector.size() == 0 && (this->T == nullptr) || (this->T->left == nullptr && this->T->right == nullptr))
            return Rotate::NO;

        Node* insertNode = vector.at(vector.size() - 1);

        // newKey or deleteKey부터 root까지의 height와 bf를 다시 계산합니다.
        for (int i = vector.size() - 1; i >= 0; --i)
        {

            Node* tmpNode = vector[i];

            //height값과 BF를 업데이트 합니다.
            if (tmpNode->left && tmpNode->right)
            {
                tmpNode->height = 1 + MAX(tmpNode->left->height, tmpNode->right->height);
                tmpNode->BF = tmpNode->left->height - tmpNode->right->height;
            }

            else if (tmpNode->left)
            {
                tmpNode->height = 1 + tmpNode->left->height;
                tmpNode->BF = tmpNode->left->height;
            }

            else if (tmpNode->right)
            {
                tmpNode->height = 1 + tmpNode->right->height;
                tmpNode->BF = -tmpNode->right->height;
            }
            else
            {
                tmpNode->height = 1;
                tmpNode->BF = 0;
            }

        }

        // newKey부터 root까지 BF를 확인하고 중간에 밸런스가 깨진 node가 있으면 회전 타입을 return 합니다.
        // LL / RR 같은 경우는 각각 parent의 left, right child를 push. LR / RL같은 경우는 parent의 각각 left / right child와 left->right / right->left까지 push 합니다.
        for (int i = vector.size() - 1; i >= 0; --i)
        {

            //각 노드의 BF가 -1~1 범위인지 확인합니다.
            if (abs(vector[i]->BF) > 1)
            {
                //위의 if문이 true이면 밸런스가 깨짐. p가 현재 노드를, q가 p의 부모노드를 가르키게 합니다.
                child = vector[i];
                //깨진노드가 root일 경우 parent가 this->T를 가르키게 합니다.
                if (i == 0)
                    parent = this->T;
                else
                    parent = vector[i - 1];

                // L
                if (vector[i]->BF > 1)
                {
                    // LR
                    if (vector[i]->left->BF < 0)
                    {
                        vector.insert(vector.begin() + i, vector[i]->left->right);
                        vector.insert(vector.begin() + (i + 1), vector[i + 1]->left);

                        return Rotate::LR;
                    }

                    // LL
                    else
                    {
                        vector.insert(vector.begin() + i, vector[i]->left);
                        return Rotate::LL;
                    }

                }
                // R
                else if (vector[i]->BF < -1)
                {
                    // RL
                    if (vector[i]->right->BF > 0)
                    {
                        vector.insert(vector.begin() + i, vector[i]->right->left);
                        vector.insert(vector.begin() + (i + 1), vector[i + 1]->right);

                        return Rotate::RL;
                    }

                    // RR
                    else
                    {
                        vector.insert(vector.begin() + i, vector[i]->right);
                        return Rotate::RR;
                    }

                }

            }

        }

        //모든 루프를 다 돌면 밸런스가 안깨졌다고 판단.
        child = parent = nullptr;
        return Rotate::NO;

    }

    //child를 root로 하는 subtree를 rotate합니다.
    void rotateTree(Rotate rotate, Node*& parent, Node*& child)
    {

        Node* tmpNode;
        Node* subTree;

        if (rotate == Rotate::LL)
        {
            tmpNode = child->left;

            subTree = tmpNode->right;

            tmpNode->right = child;

            tmpNode->right->left = subTree;

            //깨진 노드가 root일때.
            if (child == this->T)
                this->T = tmpNode;
            else
                parent->key > tmpNode->key ? parent->left = tmpNode : parent->right = tmpNode;

        }
        else if (rotate == Rotate::LR)
        {
            tmpNode = child->left->right;

            child->left->right = tmpNode->left;

            tmpNode->left = child->left;

            child->left = tmpNode->right;

            tmpNode->right = child;

            if (child == this->T)
                this->T = tmpNode;
            else
                parent->key > tmpNode->key ? parent->left = tmpNode : parent->right = tmpNode;

        }
        else if (rotate == Rotate::RR)
        {
            tmpNode = child->right;

            subTree = tmpNode->left;

            tmpNode->left = child;

            tmpNode->left->right = subTree;

            //깨진 노드가 root일때.
            if (child == this->T)
                this->T = tmpNode;
            else
                parent->key > tmpNode->key ? parent->left = tmpNode : parent->right = tmpNode;

        }
        else if (rotate == Rotate::RL)
        {
            tmpNode = child->right->left;

            child->right->left = tmpNode->right;

            tmpNode->right = child->right;

            child->right = tmpNode->left;

            tmpNode->left = child;

            //깨진 노드가 root일때.
            if (child == this->T)
                this->T = tmpNode;
            else
                parent->key > tmpNode->key ? parent->left = tmpNode : parent->right = tmpNode;

        }

        rotate = checkBalance(child, parent);

    }

    // 노드를 삭제하는 method.
    Rotate deleteAVL(Node* root, int key)
    {
        //이전 삽입, 삭제에 사용했던 vector를 초기화 합니다.
        vector.clear();

        Node* p{ nullptr };
        Node* q{ nullptr };

        Rotate rotate{ Rotate::NO };

        //삭제만 수행(BF체크와 높이 재계산 수행 X)
        rotate = deleteBST(root, nullptr, key);

        //중복된 데이터가 들어왔을때 OVERLAP type을 return 합니다.
        if (rotate == Rotate::OVERLAP)
            return rotate;

        //BF와 높이를 재계산 합니다.
        rotate = checkBalance(p, q);

        //밸런스가 깨졌으면 rotate합니다.
        if ((rotate != Rotate::NO) && (rotate != Rotate::OVERLAP))
            rotateTree(rotate, q, p);

        return rotate;

    }

    // parameter로 들어온 Node를 root로 하는 Tree의 Node 개수를 카운트 합니다.
    // deleteBST에서 삭제할 노드가 left, right child가 모두 있을때 사용합니다.
    int noNodes(Node* root, int& noNodesRef)
    {

        if (root == nullptr)
            return noNodesRef;
        else
        {
            noNodes(root->left, noNodesRef);
            ++noNodesRef;
            noNodes(root->right, noNodesRef);
        }

        return noNodesRef;

    }
    
    // parameter로 들어온 Node를 root로 하는 Tree의 최대 key를 가지는 Node를 찾습니다.
    // deleteBST에서 삭제할 노드가 left, right child가 모두 있을때 사용합니다.
    Node* maxNode(Node* root)
    {

        Node* maxnode = root;

        while (maxnode->right != nullptr)
            maxnode = maxnode->right;

        return maxnode;

    }

    // parameter로 들어온 Node를 root로 하는 Tree의 최소 key를 가지는 Node를 찾습니다.
    // deleteBST에서 삭제할 노드가 left, right child가 모두 있을때 사용합니다.
    Node* minNode(Node* root)
    {

        Node* minnode = root;

        while (minnode->left != nullptr)
            minnode = minnode->left;

        return minnode;

    }

    //노드를 삭제하는 method (BST)
    Rotate deleteBST(Node* root, Node* parents, int deleteKey)
    {

        Node* parent{ parents };
        Node* me{ root };

        //삭제할 노드의 위치를 찾는다.
        while (me != nullptr && deleteKey != me->key)
        {

            vector.push_back(me);

            parent = me;

            if (deleteKey < me->key)
                me = me->left;
            else
                me = me->right;

        }

        //삭제할 노드를 찾지 못했을때.
        if (me == nullptr)
        {
            std::cout << "d " << deleteKey << " : The key does not exist" << std::endl;
            return Rotate::OVERLAP;
        }

        //삭제할 노드의 degree가 2일때
        if (me->left != nullptr && me->right != nullptr)
        {
            //bool flag. 0 is left, 1 is right
            bool flag = LEFT;

            Node* rNode;

            if (me->left->height > me->right->height)
            {
                rNode = maxNode(me->left);
                flag = LEFT;
            }
            else if (me->left->height < me->right->height)
            {
                rNode = minNode(me->right);
                flag = RIGHT;
            }
            else
            {

                int& leftNoRef{ me->left->noNodes };
                int& rightNoRef{ me->right->noNodes };

                noNodes(me->left, leftNoRef);
                noNodes(me->right, rightNoRef);

                if (me->left->noNodes <= me->right->noNodes)
                {
                    rNode = minNode(me->right);
                    flag = RIGHT
                }
                else
                {
                    rNode = maxNode(me->left);
                    flag = LEFT;

                }
            }
            //삭제할 노드의 key값을 rNode의 키값으로 바꿔주고 rNode의 키를 가진 노드를 삭제한다.
            me->key = rNode->key;
            //바뀐 key를 가진 노드(삭제한 노드)도 vector에 push합니다.
            vector.push_back(me);

            //flag is left
            if (!flag)
                deleteBST(me->left, me, rNode->key);
            //flag is right
            else
                deleteBST(me->right, me, rNode->key);

        }
        //degree 1. left노드 존재
        else if (me->left != nullptr && me->right == nullptr)
        {
            //root를 삭제해야 할 때.
            if (parent == nullptr)
            {
                this->T = root->left;
                delete root;
                root = nullptr;
            }
            //me가 parents의 left 노드일때.
            else if (parent->left == me)
            {
                parent->left = me->left;
                delete me;
                me = nullptr;
            }
            //me가 parents의 right 노드일때.
            else
            {
                parent->right = me->left;
                delete me;
                me = nullptr;
            }

        }
        //degree 1. right노드 존재
        else if (me->right != nullptr && me->left == nullptr)
        {
            //root를 삭제해야할 때.
            if (parent == nullptr)
            {
                this->T = root->right;
                delete root;
                root = nullptr;
            }
            //me가 parents의 left 노드일때.
            else if (parent->left == me)
            {
                parent->left = me->right;
                delete me;
                me = nullptr;
            }
            //me가 parents의 right 노드일때.
            else
            {
                parent->right = me->right;
                delete me;
                me = nullptr;
            }

        }
        //leaf 노드일때
        else
        {
            //root를 삭제해야할 때.
            if (parent == nullptr)
            {
                this->T->left = nullptr;
                this->T->right = nullptr;
                this->T = nullptr;
                delete this->T;
            }
            //me가 parents의 left 노드일때.
            else if (parent->left == me)
            {
                parent->left = nullptr;
                delete me;
                me = nullptr;
            }
            //me가 parents의 right 노드일때.
            else
            {
                parent->right = nullptr;
                delete me;
                me = nullptr;
            }

        }

        //중복된 데이터가 아닌 노드를 삭제하고 난 후 일단 NO를 return 합니다.
        return Rotate::NO;

    }

    //inorder traversal
    void inorder(Node* root)
    {

        if (root == nullptr)
            return;
        else
        {

            inorder(root->left);
            std::cout << "(" << root->key << ", " << root->BF << ") ";
            inorder(root->right);

        }

    }

    //private member T를 return 합니다.
    Node* getRootNode()
    {
        return this->T;
    }

private:

    Node* T{ nullptr };

    std::vector<Node*>vector;

};

int main()
{

    std::ifstream readFile;
    readFile.open("in.txt");

    char command{ 0 };
    int key{ 0 };
    std::string inputData;
    char buffer[20]{ 0 };

    AVLTree tree;
    Rotate type{ Rotate::NO };

    if (readFile.is_open())
    {

        while (readFile)
        {

            readFile.getline(buffer, 20);

            for (int i = 2; buffer[i] != '\0'; ++i)
            {

                command = buffer[0];

                inputData += buffer[i];

            }

            key = stoi(inputData);

            if (command == 'i')
            {
                type = tree.insertAVL(tree.getRootNode(), key);
                switch (type)
                {
                case Rotate::LL:
                    std::cout << "LL ";
                    break;
                case Rotate::LR:
                    std::cout << "LR ";
                    break;
                case Rotate::RR:
                    std::cout << "RR ";
                    break;
                case Rotate::RL:
                    std::cout << "RL ";
                    break;
                case Rotate::NO:
                    std::cout << "NO ";
                    break;
                    //Rotate Type is OVERLAP. 중복 데이터가 들어왔을때.
                case Rotate::OVERLAP:
                    break;
                }
                tree.inorder(tree.getRootNode());
                std::cout << std::endl;
            }
            else if (command == 'd')
            {
                type = tree.deleteAVL(tree.getRootNode(), key);
                switch (type)
                {
                case Rotate::LL:
                    std::cout << "LL ";
                    break;
                case Rotate::LR:
                    std::cout << "LR ";
                    break;
                case Rotate::RR:
                    std::cout << "RR ";
                    break;
                case Rotate::RL:
                    std::cout << "RL ";
                    break;
                case Rotate::NO:
                    std::cout << "NO ";
                    break;
                    //Rotate Type is OVERLAP. 중복 데이터가 들어왔을때.
                default:
                    break;
                }
                tree.inorder(tree.getRootNode());
                std::cout << std::endl;
            }

            inputData = "";

        }

    }

    readFile.close();

    return 0;

}
