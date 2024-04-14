#include <list>
#include <queue>
#include<iostream>
#include <fstream>
using namespace std;
class BST {
    struct node {
        int data;
        node *left;
        node *right;
    };
    node* root;
    struct Node_Level{
        node* node;
        int level;
    };
    Node_Level *e;

    void makeEmpty(node *t) { //удаление дерева
        if (t->left)
            makeEmpty(t->left);
        if (t->right)
            makeEmpty(t->right);
        delete t;
    }

    node *insert(int x, node *t) //добавление узла в бинарное дерево
    {
        if (t == NULL) {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        } else if (x < t->data)
            t->left = insert(x, t->left);
        else if (x > t->data)
            t->right = insert(x, t->right);
        return t;
    }
    struct Trunk {
        Trunk *prev;
        string str;

        Trunk(Trunk *prev, string str) {
            this->prev = prev;
            this->str = str;
        }
    };

    // Вспомогательная функция для печати ветвей бинарного дерева
    void showTrunks(Trunk *p) {
        if (p == nullptr) {
            return;
        }
        showTrunks(p->prev);
        cout << p->str;
    }

    //Вывод дерева
    void printTree(node *root, Trunk *prev, bool isLeft) {
        if (root == nullptr) {
            return;
        }
        string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);
        printTree(root->right, trunk, true);
        if (!prev) {
            trunk->str = "---";
        } else if (isLeft) {
            trunk->str = ".---";
            prev_str = "   |";
        } else {
            trunk->str = "`---";
            prev->str = prev_str;
        }

        showTrunks(trunk);
        cout << " " << root->data << endl;

        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        printTree(root->left, trunk, false);
    }

    void entry(node *t, ofstream &f) { //запись дерева в файл
        if (t) {
            entry(t->left, f);
            f << t->data << " ";
            entry(t->right, f);
        }
    }
    int SearchDescendentsCount(node* uz, int lev_count)
    {
        int count = 0;
        lev_count++;
        if (uz != NULL)
        {
            count = 1;

            if (lev_count < 3)
            {
                count += SearchDescendentsCount(uz->left, lev_count);
                count += SearchDescendentsCount(uz->right, lev_count);
            }
        }
        return count;
    }

    void SearchMaxDescendentsCount(node* Node, int* max_count, int level, int* max_level)
    {
        level++;
        if (Node != NULL)
        {
            int count = SearchDescendentsCount(Node, 0);

            SearchMaxDescendentsCount(Node->left, max_count, level, max_level);
            SearchMaxDescendentsCount(Node->right, max_count, level, max_level);

            if ((count - 1) > *max_count)
            {
                *max_count = count - 1;
                *max_level = level;
            }
        }
    }
public:
    BST() {
        root = NULL;
    }
    ~BST() {
        makeEmpty(root);
        root = nullptr;
    }
    void insert(int x) {
        root = insert(x, root);
    }
    void algoritm(int *max_c, int *max_lev) {
        SearchMaxDescendentsCount(root, max_c, 0, max_lev);
        cout << "Уровень, на котором число потомков максимальное: " << *max_lev << std::endl;
        cout << "Максимальное число потомков: " << *max_c << std::endl;
    }
    void display_tree() {
        printTree(root,nullptr, false);
        cout << endl << endl;
    }
    void entry_tree(ofstream& f) {
        entry(root, f);
    }
};
int main() {
    BST *tree = new BST();
    int number;
    int max_count = 0, max_level = 0;
    try {
        ifstream ifs("/Users/daria/CLionProjects/binary_tree/input.dat");
        if (!ifs) // если не открыли файл, "выбрасывается"  404
            throw 404;
        else {
            while (ifs >> number) {
                tree->insert(number);
            }
            ifs.close();
        }
    }
    catch (int)
    {
        cout << "File not exists" << endl;
        exit(404);
    }

    cout << "Tree:" << endl;
    tree->display_tree(); //вывод дерева
    tree->algoritm(&max_count, &max_level);//выполнение алгоритма
    ofstream out;
    out.open("output.dat");
    if (out.is_open()) //запись данных в файл
    {
        tree->entry_tree(out);
        out << endl;
        out <<"Уровень, на котором число потомков максимальное: " <<max_level<<endl;
        out << "Максимальное число потомков: "<< max_count << endl;

    }
    out.close();
    delete tree;
}




//    if (root == NULL) {
    //        return -1;
    //    }
    //    queue<node *> q; // Создаем очередь
    //    q.push(root); // Вставляем корень в очередь
    //
    //    while (!q.empty()) // пока очередь не пуста
    //    {
    //        node *temp = q.front(); // Берем первый элемент в очереди
    //        // Удаляем первый элемент в очереди
    //        cout << temp->data << " "; // Печатаем значение первого элемента в очереди
    //
    //        if (temp->left != NULL)
    //            q.push(temp->left);  // Вставляем  в очередь левого потомка
    //
    //        if (temp->right != NULL)
    //            q.push(temp->right);  // Вставляем  в очередь правого потомка
    //    }
    //    int NodeCount(node* p)
    //    {
    //        int v;
    //        while(p!=NULL){
    //           v = NodeCount(p->left) + NodeCount(p->right);
    //           p = p->left;
    //           p= p->right;
    //        }
    //        return v;
    //
    //    }
    //    int  TreeCalc(node **n, int  allChild) {
    //        int ChLeft, ChRigth;
    //        if (*n == NULL) //дойдя до дна(низа древа).
    //        {
    //            return allChild = 0;//потомков нет.
    //        }
    //         else{           //Если узел существует.
    //
    ////Подсчёт количества потомков для текущего узла.
    //            ChLeft = TreeCalc(&(*n)->left, allChild);  //Для левой ветви.
    //            ChRigth = TreeCalc(&(*n)->right, allChild); //Для правой ветви.
    //           }
    //            if (ChLeft > ChRigth){
    //                return ChLeft;
    //            }
    //            else
    //                return ChRigth;
    //
    //    }
    //    int descendants(node* root)
    //    {
    //        if (!root)
    //        {
    //            return 0;
    //        }
    //          return 1+descendants(root->left) + descendants(root->right);
    //    }
    //    int dfs(node* node,  int& count)
    //    {
    //        // Base case
    //        static int level;
    //        if (node == NULL) {
    //            return -1;
    //        }
    //        else {
    //            while(level < 2) {
    //                if (node->right && node->left) {
    //                    count += 2;
    //                } else if (node->left || node->right)
    //                {    count++;
    //                     level++;
    //                }
    //
    //
    //            }
    //        }
    //    }
    //    void maxdeti(node* node) {
    //        int val,val1, maxi = 0;
    //        int count  = 0;
    //        if(node){
    //
    //            val = dfs(node , count);
    //            maxi = val;
    //            if (val > maxi) { maxi = val; }
    //        }
    //        cout << maxi;
    //    }
    //
    //
    //    int countTree(node* root) {
    //        if (root == NULL)
    //            return -1;
    //        queue<node *> q;
    //        q.push(root);
    //        // текущий уровень
    //        int level = 0;
    //        int max = INT_MIN;
    //        int counter,counter1 = 0;
    //
    //        // Уровень, где узел
    //        int level_no = 0;
    //
    //        while (1)
    //        {
    //            // Count Nodes in a level
    //            int NodeCount = q.size();
    //            int current_level = 0;
    //
    //            if (NodeCount == 0)
    //                break;
    //            while (NodeCount > 0) {
    //                    node *Node = q.front();
    //                    q.pop();
    //                    if (Node->left != NULL) {
    //                         q.push(Node->left);
    //
    //                    }
    //                    if (Node->right != NULL) {
    //                        q.push(Node->right);
    //
    //                    }
    //                    NodeCount--;
    //            }
    //
    //            // Increment for next level
    //            level++;
    //        }
    //        return level;
    //    }

