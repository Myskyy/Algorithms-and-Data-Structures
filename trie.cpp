/*************************************************************************
	> File Name: trie.c
	> Author: fly
	> Mail:fly@163.com 
	> Created Time: 2017年12月10日 星期日 21时48分55秒
 ************************************************************************/

#include <iostream>
#include <string>

using namespace std;

// 表示next 数组的长度， 表示26个字母。如果字符串中有其他字符的话，应相应的调整
// 如果所有的字符串都是手机号码的话，那就是10
const int MAX_NUM = 26;
struct trieNode{
    int j; //按需使用，本例子中表示从头到本字符组成的前缀出现的次数
    struct trieNode *next[MAX_NUM];
};

trieNode *createTrieNode()
{
    int i;
    trieNode *p = new trieNode;
    p->i = 1;
    for(i = 0; i < MAX_NUM; i++)
        p->next[i] = NULL;

    return p;
}

void InsertTrieTree(trieNode **root; string str)
{
    trieNode *p;
    if(*root == NULL)
    {
        p = createTrieNode();
        *root = p;
    }
    else
    {
        p = *root;
    }
    int len = str.length();
    int k, i;
    for(i = 0; i < len; i++)
    {
        k = str.at(i) - 'a';
        if(p->next[k] != NULL)
            p->next[k]->i += 1;
        else
            p->next[k] = createTrieNode();
        p = p->next[k];
    }
}

int SearchTripTree(trieNode **root, string str)
{
    trieNode *p;
    if(*root == NULL)
        return 0;
    p = *root;
    int i, k, len=str.length();
    for(i = 0; i< len; i++)
    {
        k = str.at(i) - 'a';
        if (p->next[k] == NULL)
        return 0;
        p = p->next[k];
    }

    return p->i;
}

int main()
{
    trieNode *root = NULL;
    InsertTrieTree(&root, "checking");
    InsertTrieTree(&root, "check");
    InsertTrieTree(&root, "for");
    InsertTrieTree(&root, "program");
    InsertTrieTree(&root, "programmer");
    cout << SearchTripTree(&root, "che") << endl;
}
