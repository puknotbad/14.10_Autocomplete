#include "Trie.h"

// ���������� ����� ���� � ������� ������
TrieNode* Trie::getNewNode(void)
{
    // �������� ������ ��� ����� ����
    struct TrieNode* pNode = new TrieNode;
    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;
    // �������������� ����� ������� ����������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;
    return pNode;
}

TrieNode* Trie::getRoot()
{
    return _root;
}

// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� � �������� ��c������ �.�. ����� �����
/*
        ����� ������ �� ������������ �����.
        ���������, ��� ��� ��������� ���� � ����� ��������.
        ��������� ���� �� ������� ������� ������� ����� ����.
        ��������� �������� ���� ������ ��������� ��������.
        ��������� � �. 1, ���� � ����� ���� �������.
        ���������� ���� ����� ����� ��� ���������� ����.
*/
void Trie::insert(TrieNode* root, std::string& key)
{
    TrieNode* currentNode = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = key.at(i) - 'a';
        if (currentNode->children[index] == NULL) { // if branch does not exist at the trie
            currentNode->children[index] = getNewNode(); // new TrieNode;
            currentNode->children[index]-> nWords = 1;
        }
        else currentNode->children[index]->nWords++;
        currentNode = currentNode->children[index];
    }
    // �������� ��������� ����� ��� ����, �.�. ����� �����
    currentNode->isEndOfWord = true;
    return;
}

// ���������� true ���� ���� ���� � ������, ����� false
bool Trie::search(struct TrieNode* root, std::string key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false
bool Trie::isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������
TrieNode* Trie::remove(TrieNode* root, std::string key, int depth = 0)
{
    // ���� ������ ������
    if (!root)
        return nullptr;
    // ���� ����� �� ����� �����
    if (depth == key.size()) {
        // ���� ���� ������ �� ����� �����
        // ������� ������� �����
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }
        return root;
    }

    // ���� �� ����� �� ����� ����� ��� ����������, 
    // ��� ��� ��� � ������, ���������� �������� ��� �������
    // ���������������� �������
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    // ���� � ����� ��� ��������� �����
    // (������ ������ ���� ��� �������� �������),
    // � �� �� ������������� ������ ������.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // ���������� ����� ������
    return root;
}

    //�������, ��� ���������� ����������� ����������� �������� 
    //��� ������� ����� � ������. �� ���� ������� ��������� ��� ����������� ������.
    //����� �������� � ������ ����� ������ ��� �������.
    /*
    root - ������� ���� ������. ����������� ����, ����� ��� ��������.
    buff - ������ �������� ��� ������������ ��������. ����������� ����, ����� ��� ��������.
    ind - ������ �������� �������� � ������� buff. ����������� ����, ����� ��� ��������.
    res - �������� ������ � ����������. ������ �������� ��������, ������ ������ ������ � �������.
    �������� ������ ������ �� ����.
    */
void Trie::findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{
    // ��� ������ ���
    if (root == nullptr) return;
    if (root->nWords == 1) {
        buf[ind] = '\0';
        res += buf;
        res += ' ';
        if (root->nWords == 1) return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i]) {
            buf[ind] = i + 'a';
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
}

std::string Trie::searchWordByPrefix(std::string prefix)
{
    std::string result;
    TrieNode* node = _root;
    for (int i = 0; i < prefix.size(); i++)
    {
        int index = prefix[i] - 'a';
        if (!node->children[index])
            return "";
        result += prefix[i];
        node = node->children[index];
    }
    // prefix found. Continue extracting the word
    while (!node->isEndOfWord) {
            char ch = 0; // 0 equals to 'a'
            while (node->children[ch] == NULL) {
                ch++;
            }
            result += ch + 'a';
            node = node->children[ch];
    }
    return result;
}

std::string Trie::completeWordByPrefix(std::string prefix)
{
    TrieNode* node = _root;
    for (int i = 0; i < prefix.size(); i++)
    {
        int index = prefix[i] - 'a';
        if (!node->children[index])
            return "";
        node = node->children[index];
    }
    // prefix found. Continue extracting the word
    std::string result;
    while (!node->isEndOfWord) {
        char ch = 0; // 0 equals to 'a'
        while (node->children[ch] == NULL) {
            ch++;
        }
        result += ch + 'a';
        node = node->children[ch];
    }
    return result;
}

