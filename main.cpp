#include <iostream>
#include <queue>

using namespace std;

char desc[1000000];
char keyword[51];

class Node {
public:
    bool m_isLeaf;
    Node *nodes[26];
   
    Node *falure;
    char m_val;
    int count;

public:
    Node(char val='\0', bool leaf = false) {
        m_val = val;
        m_isLeaf = leaf;
       
        falure = NULL;
        count = 0;
        memset(nodes, 0, sizeof(nodes));
    }
    
    ~Node() {
        for (int i = 0; i < 26; ++i)
            if (nodes[i])
                delete nodes[i];
    }

};

class ACTree {
    Node root;
public:
    void insert(char* str) {
        Node *head = &root;
        while(*str) {
            int i = *str - 'a';
            if(head->nodes[i] != NULL) head = head->nodes[i];
            else {
                head->nodes[i] = new Node(*str);
                head = head->nodes[i];
            }
            ++str;
        }
        head->m_isLeaf = true;
        head->count += 1;
    }
    void constructACTree() {
        queue<Node *> qu;
        qu.push(&root);
        
        while(!qu.empty()) {
            Node * tmp = qu.front();
            qu.pop();
            for(int i = 0; i < 26; ++i) {
                //tmp就是待处理节点的父节点
                if (tmp->nodes[i]) {
                    if (tmp == &root) {
                        tmp->nodes[i]->falure = &root;
                    }
                    else {
                        Node * p = tmp->falure;
                        while (p) {
                            if (p->nodes[i]) {
                                tmp->nodes[i]->falure = p->nodes[i];
                                break;
                            }
                            p = p->falure;
                        }
                        if (p == NULL)
                            tmp->nodes[i]->falure = &root;
                    }//if else

                    qu.push(tmp->nodes[i]);
                }//if
                    
            }//for
            
        }//while

    }

    //假设不存在一个模式串是另一个模式串的子串
    //不能统计匹配的关键词的个数
    int match(char *str) {
        int count = 0;
        while (*str) {
            char *p = str;
            Node *n = &root;
            while (n && p) {
                int i = *p - 'a';
                if (n->nodes[i]) {
                    n = n->nodes[i];
                    ++p;
                    
                    if (n->m_isLeaf) {
                        ++count;

                        str = p;
                        break;
                    }
                }
                else {
                    n = n->falure;
                }

            }

            if (n == NULL) {
                ++str;
            }
        }

        return count;
    }

    //如果字符串s1..n匹配到trie树中的某个节点ni，设此时匹配的字符是sh...i, 那么ni的失败指针所指向的节点nj，必然可以匹配sk...i，其中，k>h
    //即失败指针所指向的节点，这个节点到root的路径，必然是已经匹配字符串的子串
    int countKeys(char *str) {
        int count = 0;
        Node *p = &root;//这个可以看做是主线查询
        while(*str) {
            int i = *str - 'a';
            //如果p->nodes[i]不等于null，则跳出循环，继续在这个分支上查找；否则，就跳到另一个分支
            while(p->nodes[i] == NULL && p != &root) p = p->falure;
            
            p = p->nodes[i];//

            //所有分支均不能匹配这个字串，所以要从头开始匹配
            if(p == NULL)
                p = &root;
           

            Node *tmp = p;
            while(tmp != &root && tmp->count != -1) {
                
                    count += tmp->count;
                    tmp->count = -1;//删除这个叶子
                
                tmp = tmp->falure;
            }
            ++str;

        }

        return count;

    }

    ~ACTree() {
       /* for (int i = 0; i < 26; ++i)
            if (root.nodes[i])
                delete root.nodes[i];*/
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        ACTree tree;
        int n;
        scanf("%d", &n);
        while(n--) {
            scanf("%s", keyword);
            tree.insert(keyword);
        }
        tree.constructACTree();
        scanf("%s", desc);
        printf("%d\n", tree.countKeys(desc));
    }
    return 0;
}