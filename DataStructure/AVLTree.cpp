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
    //Tree�� �̹� �ִ� key�� �Է� �޾����� ǥ��.
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

    //node�� �����ϴ� method �Դϴ�.
    Rotate insertAVL(Node* root, int key)
    {
        //tree�� ��尡 ������.
        if (root == nullptr)
        {
            this->T = new Node(key);
            return Rotate::NO;
        }

        //���� ����, ������ ����ߴ� vector�� �ʱ�ȭ �մϴ�.
        vector.clear();

        Node* p{ nullptr };
        Node* q{ nullptr };

        //ȸ�� Ÿ��.
        Rotate rotate{ Rotate::NO };

        //���Ը� ����(BFüũ�� ���� ��� ���� X)
        rotate = insertBST(root, key);
        
        //�ߺ� �����Ͱ� �������� OVERLAP type�� return �մϴ�.
        if (rotate == Rotate::OVERLAP)
            return rotate;

        //���� �� ���̸� �����ϰ� BFüũ �մϴ�.
        rotate = checkBalance(p, q);

        //�뷱���� �������� rotate�մϴ�.
        if (rotate != Rotate::NO)
            rotateTree(rotate, q, p);

        return rotate;

    }

    //��带 �����մϴ�. BST
    Rotate insertBST(Node* root, int key)
    {

        Node* parent{ nullptr };
        Node* child{ root };

        //insert position�� ã�´�.
        while (child)
        {
            //��λ��� ������ vector�� ����.
            vector.push_back(child);

            parent = child;

            if (child->key > key)
                child = child->left;

            else if (child->key < key)
                child = child->right;

            //key�� �̹� tree�� �ִ� ���.
            else
            {
                std::cout << "i " << key << " : The key already exists" << std::endl;
                return Rotate::OVERLAP;
            }

        }

        //�� ��带 ��� �������� �����ϰ� �����մϴ�.
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

        //�ߺ������Ͱ� �ƴ� ��带 ���������� �����ϸ� �ϴ� NO�� ����.
        return Rotate::NO;

    }

    //���� ����� Node�� �����Ҵ� ���ִ� method�Դϴ�.
    Node* getNode(int newKey)
    {
        Node* newNode = new Node(newKey);
        return newNode;
    }

    // BF�� üũ�ϱ� ���� ���� ���̸� �����մϴ�.
    // node�� insert�Ҷ� tree�� balance�� Ȯ���մϴ�.
    // or ��带 �����ϰ� �� �� tree�� balance�� Ȯ���մϴ�.
    // or ȸ���� �� �� tree�� balance�� Ȯ���մϴ�.
    // �ұ����� �߻��ϸ�, �߻��� ��� p�� �� ����� �θ� ��� q, �׸��� ȸ���� ����, rotationType�� ����.
    Rotate checkBalance(Node*& child, Node*& parent)
    {

        Rotate rotateType{ Rotate::NO };

        //���� ������ �� �� root node�ϳ��� �������� ����ó��.
        if (vector.size() == 0 && (this->T == nullptr) || (this->T->left == nullptr && this->T->right == nullptr))
            return Rotate::NO;

        Node* insertNode = vector.at(vector.size() - 1);

        // newKey or deleteKey���� root������ height�� bf�� �ٽ� ����մϴ�.
        for (int i = vector.size() - 1; i >= 0; --i)
        {

            Node* tmpNode = vector[i];

            //height���� BF�� ������Ʈ �մϴ�.
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

        // newKey���� root���� BF�� Ȯ���ϰ� �߰��� �뷱���� ���� node�� ������ ȸ�� Ÿ���� return �մϴ�.
        // LL / RR ���� ���� ���� parent�� left, right child�� push. LR / RL���� ���� parent�� ���� left / right child�� left->right / right->left���� push �մϴ�.
        for (int i = vector.size() - 1; i >= 0; --i)
        {

            //�� ����� BF�� -1~1 �������� Ȯ���մϴ�.
            if (abs(vector[i]->BF) > 1)
            {
                //���� if���� true�̸� �뷱���� ����. p�� ���� ��带, q�� p�� �θ��带 ����Ű�� �մϴ�.
                child = vector[i];
                //������尡 root�� ��� parent�� this->T�� ����Ű�� �մϴ�.
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

        //��� ������ �� ���� �뷱���� �ȱ����ٰ� �Ǵ�.
        child = parent = nullptr;
        return Rotate::NO;

    }

    //child�� root�� �ϴ� subtree�� rotate�մϴ�.
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

            //���� ��尡 root�϶�.
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

            //���� ��尡 root�϶�.
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

            //���� ��尡 root�϶�.
            if (child == this->T)
                this->T = tmpNode;
            else
                parent->key > tmpNode->key ? parent->left = tmpNode : parent->right = tmpNode;

        }

        rotate = checkBalance(child, parent);

    }

    // ��带 �����ϴ� method.
    Rotate deleteAVL(Node* root, int key)
    {
        //���� ����, ������ ����ߴ� vector�� �ʱ�ȭ �մϴ�.
        vector.clear();

        Node* p{ nullptr };
        Node* q{ nullptr };

        Rotate rotate{ Rotate::NO };

        //������ ����(BFüũ�� ���� ���� ���� X)
        rotate = deleteBST(root, nullptr, key);

        //�ߺ��� �����Ͱ� �������� OVERLAP type�� return �մϴ�.
        if (rotate == Rotate::OVERLAP)
            return rotate;

        //BF�� ���̸� ���� �մϴ�.
        rotate = checkBalance(p, q);

        //�뷱���� �������� rotate�մϴ�.
        if ((rotate != Rotate::NO) && (rotate != Rotate::OVERLAP))
            rotateTree(rotate, q, p);

        return rotate;

    }

    // parameter�� ���� Node�� root�� �ϴ� Tree�� Node ������ ī��Ʈ �մϴ�.
    // deleteBST���� ������ ��尡 left, right child�� ��� ������ ����մϴ�.
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
    
    // parameter�� ���� Node�� root�� �ϴ� Tree�� �ִ� key�� ������ Node�� ã���ϴ�.
    // deleteBST���� ������ ��尡 left, right child�� ��� ������ ����մϴ�.
    Node* maxNode(Node* root)
    {

        Node* maxnode = root;

        while (maxnode->right != nullptr)
            maxnode = maxnode->right;

        return maxnode;

    }

    // parameter�� ���� Node�� root�� �ϴ� Tree�� �ּ� key�� ������ Node�� ã���ϴ�.
    // deleteBST���� ������ ��尡 left, right child�� ��� ������ ����մϴ�.
    Node* minNode(Node* root)
    {

        Node* minnode = root;

        while (minnode->left != nullptr)
            minnode = minnode->left;

        return minnode;

    }

    //��带 �����ϴ� method (BST)
    Rotate deleteBST(Node* root, Node* parents, int deleteKey)
    {

        Node* parent{ parents };
        Node* me{ root };

        //������ ����� ��ġ�� ã�´�.
        while (me != nullptr && deleteKey != me->key)
        {

            vector.push_back(me);

            parent = me;

            if (deleteKey < me->key)
                me = me->left;
            else
                me = me->right;

        }

        //������ ��带 ã�� ��������.
        if (me == nullptr)
        {
            std::cout << "d " << deleteKey << " : The key does not exist" << std::endl;
            return Rotate::OVERLAP;
        }

        //������ ����� degree�� 2�϶�
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
            //������ ����� key���� rNode�� Ű������ �ٲ��ְ� rNode�� Ű�� ���� ��带 �����Ѵ�.
            me->key = rNode->key;
            //�ٲ� key�� ���� ���(������ ���)�� vector�� push�մϴ�.
            vector.push_back(me);

            //flag is left
            if (!flag)
                deleteBST(me->left, me, rNode->key);
            //flag is right
            else
                deleteBST(me->right, me, rNode->key);

        }
        //degree 1. left��� ����
        else if (me->left != nullptr && me->right == nullptr)
        {
            //root�� �����ؾ� �� ��.
            if (parent == nullptr)
            {
                this->T = root->left;
                delete root;
                root = nullptr;
            }
            //me�� parents�� left ����϶�.
            else if (parent->left == me)
            {
                parent->left = me->left;
                delete me;
                me = nullptr;
            }
            //me�� parents�� right ����϶�.
            else
            {
                parent->right = me->left;
                delete me;
                me = nullptr;
            }

        }
        //degree 1. right��� ����
        else if (me->right != nullptr && me->left == nullptr)
        {
            //root�� �����ؾ��� ��.
            if (parent == nullptr)
            {
                this->T = root->right;
                delete root;
                root = nullptr;
            }
            //me�� parents�� left ����϶�.
            else if (parent->left == me)
            {
                parent->left = me->right;
                delete me;
                me = nullptr;
            }
            //me�� parents�� right ����϶�.
            else
            {
                parent->right = me->right;
                delete me;
                me = nullptr;
            }

        }
        //leaf ����϶�
        else
        {
            //root�� �����ؾ��� ��.
            if (parent == nullptr)
            {
                this->T->left = nullptr;
                this->T->right = nullptr;
                this->T = nullptr;
                delete this->T;
            }
            //me�� parents�� left ����϶�.
            else if (parent->left == me)
            {
                parent->left = nullptr;
                delete me;
                me = nullptr;
            }
            //me�� parents�� right ����϶�.
            else
            {
                parent->right = nullptr;
                delete me;
                me = nullptr;
            }

        }

        //�ߺ��� �����Ͱ� �ƴ� ��带 �����ϰ� �� �� �ϴ� NO�� return �մϴ�.
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

    //private member T�� return �մϴ�.
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
                    //Rotate Type is OVERLAP. �ߺ� �����Ͱ� ��������.
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
                    //Rotate Type is OVERLAP. �ߺ� �����Ͱ� ��������.
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
