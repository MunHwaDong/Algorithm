/*

    20171625 박종한 화일처리 BST 리포트.
    삽입 : 성공.
    삭제 : 성공.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#define LEFT 0
#define RIGHT 1

struct Node
{

    int key{ 0 };
    int height{ 0 };
    int noNodes{ 0 };
    Node* left{ nullptr };
    Node* right{ nullptr };

    Node() {};

    Node(int newKey) : key(newKey) {};
    Node(int newKey, int heightRef) : key(newKey), height(heightRef) {};

};

class BinarySearchTree
{

public:
    void insertBST(Node* root, int newKey)
    {

        Node* parents{ nullptr };
        Node* me{ root };

        while (me != nullptr)
        {

            if (newKey == me->key)
            {
                std::cout << "i " << me->key << " : The key already exists" << std::endl;
                return;
            }

            parents = me;

            if (newKey < parents->key)
                me = parents->left;
            else
                me = parents->right;

        }

        Node* newNode = getNode(newKey);

        if (root == nullptr)
            this->root = newNode;
        else if (newKey < parents->key)
            parents->left = newNode;
        else
            parents->right = newNode;

    }

    Node* getNode(int newKey)
    {
        Node* newNode = new Node(newKey);
        return newNode;
    }

    void deleteBST(Node* root, Node* parents, int deleteKey)
    {

        Node* parent{ parents };
        Node* me{ root };

        //삭제할 노드의 위치를 찾는다.
        while (me != nullptr && deleteKey != me->key)
        {

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
            return;
        }

        //삭제할 노드의 degree가 2일때
        if (me->left != nullptr && me->right != nullptr)
        {

            int& leftHeightRef{ me->left->height };
            int& rightHeightRef{ me->right->height };

            //bool flag. 0 is left, 1 is right
            bool flag{ LEFT };

            Node* rNode;

            height(me->left, leftHeightRef, 0);
            height(me->right, rightHeightRef, 0);

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

                if (me->left->noNodes >= me->right->noNodes)
                {
                    rNode = maxNode(me->left);
                    flag = LEFT;
                }
                else
                {
                    rNode = minNode(me->right);
                    flag = RIGHT;
                }

            }

            me->key = rNode->key;

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

            if (parent == nullptr)
            {
                this->root = root->left;
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

            if (parent == nullptr)
            {
                this->root = root->right;
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

            //me가 parents의 left 노드일때.
            if (parent == nullptr)
            {
                this->root->left = nullptr;
                this->root->right = nullptr;
                this->root = nullptr;
                delete this->root;
            }
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
    }

    int height(Node* root, int& heightRef, int counter)
    {

        if (root == nullptr)
            return heightRef;

        if (heightRef <= counter)
            heightRef = counter;

        height(root->left, heightRef, counter + 1);
        height(root->right, heightRef, counter + 1);

    }

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

    Node* maxNode(Node* root)
    {

        Node* maxnode = root;

        while (maxnode->right != nullptr)
            maxnode = maxnode->right;

        return maxnode;

    }

    Node* minNode(Node* root)
    {

        Node* minnode = root;

        while (minnode->left != nullptr)
            minnode = minnode->left;

        return minnode;

    }

    void inorderBST(Node* root)
    {

        if (root == nullptr)
            return;
        else
        {
            inorderBST(root->left);
            std::cout << root->key << " ";
            inorderBST(root->right);

        }

    }

    Node* getRoot()
    {
        return this->root;
    }

private:
    Node* root{ nullptr };

};

int main()
{

    std::ifstream readFile;
    readFile.open("in.txt");

    char command{ 0 };
    int key{ 0 };
    std::string inputData;
    char buffer[20]{ 0 };
    BinarySearchTree bst;

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
                bst.insertBST(bst.getRoot(), key);
                bst.inorderBST(bst.getRoot());
            }
            else if (command == 'd')
            {
                bst.deleteBST(bst.getRoot(), nullptr, key);
                bst.inorderBST(bst.getRoot());

            }

            std::cout << '\n';
            inputData = "";

        }

    }

    readFile.close();

    return 0;


}