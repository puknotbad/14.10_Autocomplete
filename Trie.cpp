#include "Trie.h"

// Возвращает новый узел с пустыми детьми
TrieNode* Trie::getNewNode(void)
{
    // Выделяем память под новый узел
    struct TrieNode* pNode = new TrieNode;
    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;
    // инициализируем детей нулевым указателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;
    return pNode;
}

TrieNode* Trie::getRoot()
{
    return _root;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает в качестве лиcтового т.е. конец слова
/*
        Взять символ от вставляемого ключа.
        Проверить, что нет дочернего узла с таким символом.
        Присвоить узлу по индексу взятого символа новый узел.
        Присвоить текущему узлу только созданный дочерний.
        Повторять с п. 1, пока в ключе есть символы.
        Установить флаг конца слова для последнего узла.
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
    // помечаем последний узлел как лист, т.е. конец слова
    currentNode->isEndOfWord = true;
    return;
}

// Возвращает true если ключ есть в дереве, иначе false
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

// Возвращает true если root имеет лист, иначе false
bool Trie::isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева
TrieNode* Trie::remove(TrieNode* root, std::string key, int depth = 0)
{
    // Если дерево пустое
    if (!root)
        return nullptr;
    // Если дошли до конца ключа
    if (depth == key.size()) {
        // Этот узел больше не конец слова
        // поэтому снимаем метку
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        // Если ключ не является префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }
        return root;
    }

    // Пока не дошли до конца ключа или определили, 
    // что его нет в дереве, рекурсивно вызываем для ребенка
    // соответствующего символа
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    // Если у корня нет дочернего слова
    // (удален только один его дочерний элемент),
    // и он не заканчивается другим словом.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // возвращаем новый корень
    return root;
}

    //функцию, для нахождения кратчайшего уникального префикса 
    //для каждого слова в дереве. На вход функция принимает уже построенное дерево.
    //Ответ запишите в строку через пробел без запятых.
    /*
    root - текущий узел дерева. Заполняется вами, нужен для рекурсии.
    buff - массив символов для формирования префикса. Заполняется вами, нужен для рекурсии.
    ind - индекс текущего элемента в массиве buff. Заполняется вами, нужен для рекурсии.
    res - итоговая строка с префиксами. Строка содержит префиксы, формат строки описан в задании.
    Выводить строку никуда не надо.
    */
void Trie::findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{
    // ваш Ёбаный кот
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

