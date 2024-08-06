/*

    20171625 박종한 화일처리 B-Tree 리포트.
    삽입 : 성공.
    삭제 : 성공.

*/


#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct Node
{

    int numOfKey{ 0 };
    int mWay{ 0 };

    vector<int> keys;
    vector<Node*> childPtr;


    Node()
    {
        numOfKey = 0;
        mWay = 0;
        keys.resize(mWay);
        childPtr.resize(mWay);

    }

    Node(int m)
    {
        numOfKey = 0;
        mWay = m;
        keys.resize(mWay - 1);
        childPtr.resize(mWay);

    }

};

class BTree
{

public:

    //insert 관련 메서드들
    void insertBT(int m, int newKey)
    {
        //루트 노드 생성
        if (this->T == nullptr)
        {
            this->T = getNode();
            this->T->keys[0] = newKey;
            this->T->numOfKey = 1;
            return;
        }

        //newKey를 삽입할 노드의 경로를 탐색하며, 스택에 경로 저장.
        stack<Node*> path;

        bool found = searchPath(this->T, m, newKey, path);

        //newKey를 btree에서 발견함.
        if (found)
        {
            std::cout << "i " << newKey << " : The key already exists" << std::endl;
            return;
        }

        //newKey가 tree에 없으니 T에 삽입.
        bool finished = false;

        Node* x = path.top();
        path.pop();

        //새로 분할된 노드를 담을 변수.
        Node* y{ nullptr };

        do
        {
            //overflow 검사
            if (x->numOfKey < m - 1)
            {
                //overflow 발생하지 않음.
                insertKey(m, x, y, newKey);
                finished = true;
            }
            else
            {
                //overflow 발생.
                //x를 newKey을 기준으로 분할, 분할된 노드 반환.
                newKey = splitNode(m, *&x, *&y, newKey);

                if (!path.empty())
                {
                    x = path.top();
                    path.pop();
                }
                else
                {
                    this->T = getNode();
                    this->T->keys[0] = newKey;
                    this->T->childPtr[0] = x;
                    this->T->childPtr[1] = y;
                    this->T->numOfKey = 1;
                    finished = true;
                }
            }
        } while (!finished);

    }

    //새 노드를 동적할당하여 주소를 return 합니다.
    Node* getNode()
    {
        return new Node(this->m);
    }

    //key를 찾아가면서 stack에 노드들을 쌓아서 path를 구성합니다.
    bool searchPath(Node* t, int m, int key, stack<Node*>& path)
    {

        int i{ 0 };

        Node* x = t;

        do
        {
            i = 0;

            //현재 노드에서 어느 child 노드로 내려가야 하는지 찾습니다.
            while (i < x->numOfKey && key > x->keys[i])
                ++i;

            path.push(x);

            //키를 찾으면 true를 return 합니다.
            if (i < x->numOfKey && key == x->keys[i])
                return true;

        } while ((x = x->childPtr[i]) != nullptr);

        return false;

    }

    //newKey 보다 크 키들을, 오른쪽으로 한 칸씩 이동.
    void insertKey(int m, Node*& x, Node*& y, int newKey)
    {

        int i = x->numOfKey - 1;

        while (i >= 0 && newKey < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i];
            x->childPtr[i + 2] = x->childPtr[i + 1];
            --i;
        }

        x->keys[i + 1] = newKey;

        x->childPtr[i + 2] = y;
        ++x->numOfKey;

    }

    //노드 y를 노드 x에 깊은 복사.
    void deepNodeCopy(Node*& x, Node*& y)
    {

        x->numOfKey = y->numOfKey;

        for (int i = 0; i < this->m; ++i)
        {
            if (i < this->m - 1)
            {
                x->keys.at(i) = y->keys.at(i);
                x->childPtr.at(i) = y->childPtr.at(i);
            }
            else
                x->childPtr.at(i) = y->childPtr.at(i);
        }
    }

    /*분할해야 하는 노드 x를 tmp로 깊은 복사 후
      x에는 center key보다 작은 키만을 남기고
      새로운 노드 y에는 center 보다 큰 키들만 남깁니다.
      그리고 y와 centerKey를 return 합니다.*/
    int splitNode(int m, Node*& x, Node*& y, int newKey)
    {
        //overflow를 위한 임시 노드. (x와 newKey를 저장)
        Node* tmpNode = new Node(m + 1);

        deepNodeCopy(tmpNode, x);

        insertKey(m, tmpNode, y, newKey);

        int i = 0;
        int centerIndex = static_cast<int>(ceil(tmpNode->numOfKey / 2));
        int centerKey = tmpNode->keys[centerIndex];

        //x에 키들을 다시 넣기전에 초기화 해서 이전 값들을 삭제시켜 줍니다.
        x->numOfKey = 0;
        x->keys.clear();
        x->keys.resize(this->m - 1);
        x->childPtr.clear();
        x->childPtr.resize(this->m);

        while (tmpNode->keys[i] < centerKey)
        {
            x->keys[i] = tmpNode->keys[i];
            x->childPtr[i] = tmpNode->childPtr[i];
            ++i;
            ++x->numOfKey;
        }

        x->childPtr[i] = tmpNode->childPtr[i];

        y = getNode();

        ++i;

        while (i < tmpNode->numOfKey)
        {
            y->keys[y->numOfKey] = tmpNode->keys[i];
            y->childPtr[y->numOfKey] = tmpNode->childPtr[i];
            ++i;
            ++y->numOfKey;
        }

        y->childPtr[y->numOfKey] = tmpNode->childPtr[i];

        delete tmpNode;

        return centerKey;

    }

    //삭제할 키(oldKey == x)가 있는 노드가 terminal node인지 확인합니다.
    //삭제할 키가 internal node에 있으면 false와 index를 return 합니다.
    bool isTerminalNode(Node* x, int* index, int oldKey)
    {

        int i{ 0 };

        bool result{ false };

        //m - 1만큼 반복하는데 모두 nullptr이면 terminal Node로 판단
        while (x->childPtr.at(i++) == nullptr && i < this->m - 1);

        if (i == this->m - 1)
            result = true;

        for (int j = 0; j < x->numOfKey; ++j)
            if (x->keys.at(j) == oldKey)
                *index = j;

        return result;

    }

    //delete관련 메서드들.
    void deleteBT(int m, int oldKey)
    {

        stack<Node*> path;
        
        bool found = searchPath(this->T, m, oldKey, path);

        //oldKey를 찾지 못했을때.
        if (!found)
        {
            std::cout << "d " << oldKey << " : The key dose not exist" << std::endl;
            return;
        }

        Node* x = path.top();
        path.pop();

        int index{ 0 };

        Node* y{ nullptr };

        //termianl node인지 확인합니다. oldKey의 위치를 return합니다.
        if (!isTerminalNode(x, &index, oldKey))
        {
            //oldKey가 존재하는 위치를 저장해놓고 후행키까지 searchPath 합니다.
            //shallow copy
            Node* internalNode = x;

            int i = index;

            path.push(x);

            searchPath(x->childPtr.at(i + 1), m, x->keys.at(i), path);

            //x는 이제 terminal node
            x = path.top();
            path.pop();

            //swap.
            std::swap(internalNode->keys.at(i), x->keys.at(0));

        }

        bool finished{ false };

        //노드에서 oldKey 삭제.
        deleteKey(this->T, m, x, oldKey);

        //y는 삭제된 oldKey의 parent 노드
        if (!path.empty())
        {
            y = path.top();
            path.pop();
        }

        int underFlow = static_cast<int>(ceil(m / 2.0f)) - 1;

        do {

            //삭제할 키가 있는 노드가 root이거나 삭제할 키가 있는 노드가 underflow가 아니면 끝냅니다.
            if (this->T == x || x->numOfKey >= underFlow)
                finished = true;
            else
            {
                //어떤 노드에서 키를 가져와야하는지 or 어느 노드로 합쳐야 하는지 child의 index를 return 합니다.
                int bestSib = bestSibling(m, x, y);

                //키를 나눠줄 node가 underflow가 아니면 키를 재분배 합니다.
                if (y->childPtr[bestSib]->numOfKey > underFlow)
                {
                    redistributeKeys(m, x, y, bestSib);

                    finished = true;

                }
                else
                {
                    mergeNode(m, x, y, bestSib);

                    //shallow copy
                    x = y;

                    if (!path.empty())
                    {
                        y = path.top();
                        path.pop();
                    }
                    else
                        finished = true;

                }
            }

        } while (!finished);

        if (y != nullptr && y->numOfKey == 0)
        {
            this->T = y->childPtr.at(0);
            delete y;
        }
    }

    void deleteKey(Node* t, int m, Node* x, int oldKey)
    {

        int i{ 0 };

        //oldKey의 위치를 탐색.
        while (oldKey > x->keys.at(i))
            ++i;

        //oldKey보다 큰 값들을 왼쪽으로 한 칸 씩 이동.
        while (i < x->numOfKey - 1)
        {
            x->keys.at(i) = x->keys.at(i + 1);
            x->childPtr.at(i + 1) = x->childPtr.at(i + 2);

            //옆으로 한 칸 씩 옮겼으니깐 마지막 child는 삭제시켜줍니다.
            if (i + 2 == x->numOfKey && x->childPtr.at(i + 2) != nullptr)
                x->childPtr.at(i + 2) = nullptr;

            ++i;

        }

        //키를 삭제했으니 -1
        --x->numOfKey;

    }

    //재분배 실행 시 어떤 노드에서 키를 가져와야하는지 결정하고 poiner index를 return 합니다.
    int bestSibling(int m, Node* x, Node* y)
    {
        int i{ 0 };
        
        //oldKey가 있던 노드를 찾을때 까지 index를 ++
        while (y->childPtr.at(i) != x)
            ++i;

        //왼쪽 형제가 없음.
        if (i == 0)
            return i + 1;
        //오른쪽 형제가 없음.
        else if (i == y->numOfKey)
            return i - 1;
        else if (y->childPtr.at(i)->numOfKey >= y->childPtr.at(i + 1)->numOfKey)
            return i - 1;
        else
            return i + 1;

    }

    //키를 재분배 해줍니다.
    void redistributeKeys(int m, Node* x, Node* y, int bestSibling)
    {

        int i{ 0 };

        while (y->childPtr.at(i) != x)
            ++i;

        //y = parent, x = y's children
        Node* bestNode{ y->childPtr.at(bestSibling) };

        //insertKey가 call by reference라서 선언
        Node* dummy{ nullptr };

        //bestSibling이 왼쪽.
        if (bestSibling < i)
        {
            int lastKey{ bestNode->keys.at(bestNode->numOfKey - 1) };

            insertKey(m, x, dummy, y->keys.at(i - 1));

            x->childPtr.at(1) = x->childPtr.at(0);

            x->childPtr.at(0) = bestNode->childPtr.at(bestNode->numOfKey);

            bestNode->childPtr.at(bestNode->numOfKey) = nullptr;

            deleteKey(this->T, m, bestNode, lastKey);

            y->keys.at(i - 1) = lastKey;

        }
        else
        {

            int firstKey{ bestNode->keys.at(0) };

            insertKey(m, x, dummy, y->keys.at(i));

            //x노드의 맨 끝에 child를 붙여준다.
            x->childPtr.at(x->numOfKey) = bestNode->childPtr.at(0);

            bestNode->childPtr.at(0) = bestNode->childPtr.at(1);

            deleteKey(this->T, m, bestNode, firstKey);

            y->keys.at(i) = firstKey;

        }

    }

    //x와 y노드 둘을 병합 합니다.
    void mergeNode(int m, Node* x, Node* y, int bestSibling)
    {

        int i{ 0 };

        while (y->childPtr.at(i) != x)
            ++i;

        Node* bestNode{ y->childPtr.at(bestSibling) };

        if (bestSibling > i)
        {

            std::swap(i, bestSibling);

            std::swap(x, bestNode);

        }

        //왼쪽 형제 노드와 병합.
        bestNode->keys.at(bestNode->numOfKey) = y->keys.at(i - 1);

        ++bestNode->numOfKey;

        int j{ 0 };

        while (j < x->numOfKey)
        {
            bestNode->keys.at(bestNode->numOfKey) = x->keys.at(j);
            bestNode->childPtr.at(bestNode->numOfKey) = x->childPtr.at(j);
            ++bestNode->numOfKey;
            ++j;
        }

        bestNode->childPtr.at(bestNode->numOfKey) = x->childPtr.at(x->numOfKey);

        deleteKey(this->T, m, y, y->keys.at(i - 1));

        delete x;
        x = nullptr;

    }

    //inorder traversal
    void inOrderBT(Node* root)
    {

        if (root == nullptr)
            return;
        else
        {

            for (int i = 0; i < m && (root->childPtr.size() || i < root->numOfKey); ++i)
            {
                if(root->childPtr[i] != nullptr)
                    inOrderBT(root->childPtr.at(i));

                if(i < root->numOfKey)
                    std::cout << root->keys.at(i) << " ";
            }

        }
    }

    void setMway(int mWay)
    {
        this->m = mWay;
    }

    Node* getRootNode()
    {
        return this->T;
    }

private:

    Node* T{ nullptr };
    int m{ 0 };


};

int main()
{

    std::ifstream readFile;
    char command{ 0 };
    int key{ 0 };
    std::string inputData;
    char buffer[20]{ 0 };

    for (int m = 3; m < 5; ++m)
    {

        BTree tree;

        tree.setMway(m);

        readFile.open("in.txt");

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
                    tree.insertBT(m, key);
                    tree.inOrderBT(tree.getRootNode());
                    std::cout << std::endl;
                }
                else if (command == 'd')
                {
                    tree.deleteBT(m, key);
                    tree.inOrderBT(tree.getRootNode());
                    std::cout << std::endl;
                }

                inputData = "";

            }

        }

        readFile.close();

    }

    return 0;

}
