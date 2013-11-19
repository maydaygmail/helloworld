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
                //tmp���Ǵ�����ڵ�ĸ��ڵ�
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

    //���費����һ��ģʽ������һ��ģʽ�����Ӵ�
    //����ͳ��ƥ��Ĺؼ��ʵĸ���
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

    //����ַ���s1..nƥ�䵽trie���е�ĳ���ڵ�ni�����ʱƥ����ַ���sh...i, ��ôni��ʧ��ָ����ָ��Ľڵ�nj����Ȼ����ƥ��sk...i�����У�k>h
    //��ʧ��ָ����ָ��Ľڵ㣬����ڵ㵽root��·������Ȼ���Ѿ�ƥ���ַ������Ӵ�
    int countKeys(char *str) {
        int count = 0;
        Node *p = &root;//������Կ��������߲�ѯ
        while(*str) {
            int i = *str - 'a';
            //���p->nodes[i]������null��������ѭ���������������֧�ϲ��ң����򣬾�������һ����֧
            while(p->nodes[i] == NULL && p != &root) p = p->falure;
            
            p = p->nodes[i];//

            //���з�֧������ƥ������ִ�������Ҫ��ͷ��ʼƥ��
            if(p == NULL)
                p = &root;
           

            Node *tmp = p;
            while(tmp != &root && tmp->count != -1) {
                
                    count += tmp->count;
                    tmp->count = -1;//ɾ�����Ҷ��
                
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