#include <iostream>
#include <memory>
#include <string>


namespace BMSTU {
    template<typename K, typename V>
    class dictionary;
    template<typename K, typename V>
    class BstTree {
        friend class dictionary<K, V>;
    public:
        BstTree() : root_(nullptr), size_(0) {}
// "Публичные методы"

        void Insert(K value) {
            this->Insert(value, this->root_);
        }
        bool Contains(K value) {
            return this->Contains(value, this->root_);
        }
        void Remove(K value) {
            remove(value, this->root_);
        }
        size_t Size() const{
            return size_;
        }
        size_t Height() {
            return HeightOfTree(this->root_);
        }
        void Print(int space) const {
            PrintTree(this->root_, space);
        }
        void inorderTraversal() {
            this->inorderTraversal(this->root_);
        }
        void preorderTraversal() {
            this->preorderTraversal(this->root_);
        }
        void postorderTraversal() {
            this->postorderTraversal(this->root_);
        }
        K Find_min_key(){
            return min_key();
        }
        K Find_max_key(){
            return max_key();
        }
//        void DrawShape() const{
//            DrawRect();
//        }
    private:
// "Узел дерева"
        struct TreeNode {
            TreeNode(K data) : key(data), value(V()), left(nullptr), right(nullptr) {};
            K key;
            V value;
            uint8_t height;
            std::unique_ptr<TreeNode> left;
            std::unique_ptr<TreeNode> right;
        };
// "Хелперы для публичных методов"
///левый поворот
        void RotateWithLeftChild(std::unique_ptr<TreeNode> &node) noexcept {
            std::unique_ptr<TreeNode> L = std::move(node->left);
            node->left = std::move(L->right);
            node->height = std::max(this->HeightOfTree(node->left), this->HeightOfTree(node->right)) + 1;
            L->height = std::max(this->HeightOfTree(L->left), node->height) + 1;
            L->right = std::move(node);
            node = std::move(L);
        }
/// правый поворот
        void RotateWithRightChild(std::unique_ptr<TreeNode> &node) noexcept {
            std::unique_ptr<TreeNode> R = std::move(node->right);
            node->right = std::move(R->left);
            node->height = std::max(this->HeightOfTree(node->left), this->HeightOfTree(node->right)) + 1;
            R->height = std::max(this->HeightOfTree(R->right), node->height) + 1;
            R->left = std::move(node);
            node = std::move(R);
        }
///двойной правый поворот
        void RotateDoubleWithRightChild(std::unique_ptr<TreeNode> &node) noexcept {
            this->RotateWithLeftChild(node->right);
            this->RotateWithRightChild(node);
        };
///двойной левый поворот
        void RotateDoubleWithLeftChild(std::unique_ptr<TreeNode> &node) noexcept {
            this->RotateWithRightChild(node->left);
            this->RotateWithLeftChild(node);
        };
/// Балансировка
        void Balance(std::unique_ptr<TreeNode> &node) {
            const int imbalance_value = 1;
            if (node == nullptr) {
                return;
            } else {
                if (this->HeightOfTree(node->left) - this->HeightOfTree(node) > imbalance_value) {
                    if (this->HeightOfTree(node->left->left) >= this->HeightOfTree(node->left->right)) {
                        this->RotateWithLeftChild(node);
                    } else {
                        this->RotateDoubleWithLeftChild(node);
                    }
                } else if (this->HeightOfTree(node->right) - this->HeightOfTree(node->left) > imbalance_value) {
                    if (this->HeightOfTree(node->right->right) >= this->HeightOfTree(node->right->left)) {
                        this->RotateWithRightChild(node);
                    } else {
                        this->RotateDoubleWithRightChild(node);
                    }
                }
                node->height = std::max(this->HeightOfTree(node->left), this->HeightOfTree(node->right)) + 1;
            }
        }
/// Вставка
        std::unique_ptr<TreeNode> &Insert(K value, std::unique_ptr<TreeNode> &node) {
            if (node == nullptr){
                node = std::make_unique<TreeNode>(value);
                ++size_;
                return node;
            }
            if(value < node->key){
                this->Insert(value, node->left);
            } else if (value > node->key){
                this->Insert(value, node->right);
            } else {
                return node;
            }
            this->Balance(node);
            return node;
        };
/// Проверка содержания значения в дереве
        bool Contains(K value, std::unique_ptr<TreeNode> &node) {
            if (node == nullptr){
                return false;
            } else if (node->key == value){
                return true;
            } else if (value > node->key){
                return this->Contains(value, node->right);
            } else {
                return this->Contains(value, node->left);
            }
        };
/// Поиск Ноды по значению
        TreeNode *Search(K key, std::unique_ptr<TreeNode> &node) {
            if(Contains(key, node)){
                if (node->key == key){
                    return &*node;
                } else if (key > node->key){
                    return this->Search(key, node->right);
                } else return this->Search(key, node->left);
            } else std::cout << " no node with \"" << key << "\" value found " << std::endl;
        }
/// Удаление Ноды
        void remove(K value, std::unique_ptr<TreeNode> &node) {
            ///если нода пуста слева и справа
            ///если нода пуста слева не пуста справа
            ///если нода пуста справа не пуста слева
            ///если нода не пуста слева и справа
            if (Contains(value)){
                if (node->key == value){
                    if((node->right == nullptr)&&(node->left == nullptr)){
                        node = nullptr;
                    } else if ((node->right != nullptr)&&(node->left == nullptr)){
                        node = std::move(node->right);
                    } else if ((node->right == nullptr)&&(node->left != nullptr)){
                        node = std::move(node->left);
                    } else {
                        if (node->key < this->root_->key){
                            node->right->left = std::move(node->left);
                            node = std::move(node->right);
                        } else {
                            node->left->right = std::move(node->right);
                            node = std::move(node->left);
                        }
                        Balance(node);
                    }
                } else if (node->key > value){
                    remove(value, node->left);
                    Balance(node->right);
                } else {
                    remove(value, node->right);
                    Balance(node->left);
                }
            } else std::cout << "no \"" << value << "\"value find" << std::endl;
        }
/// Поиск ноды с минимальным значением
        std::unique_ptr<TreeNode> &findMinNode( std::unique_ptr<TreeNode> &node) const {
            if (node == nullptr){
                throw "tree is empty, min_value not found";
            } else if (node->left == nullptr){
                return node;
            } else {
                return this->findMinNode(node->left);
            }
        }
///геттер ключа
        K Get_key(std::unique_ptr<TreeNode> &node){
            return node->key;
        }
/// Функция вывода минимального значения
        K min_key(){
            if (this->root_ != nullptr){
                return  findMinNode(this->root_)->key;
            }
        }
/// Поиск ноды с максимальным значением
        std::unique_ptr<TreeNode> &findMaxNode(std::unique_ptr<TreeNode> &node) const {
            if(node == nullptr){
                throw "tree is empty, max_value not found";
            } else if (node->right == nullptr){
                return node;
            } else {
                return this->findMaxNode(node->right);
            }
        }
/// Функция вывода максимального значения
        K max_key(){
            if (this->root_ != nullptr){
                return  findMaxNode(this->root_)->key;
            }
        }
///нарисовать прямоугольник вокруг кея
        void DrawRect(const std::unique_ptr<TreeNode> &node) const {
            if (node == nullptr) {
                return;
            } else {
                size_t num_length;
                K num = node->key;
                std::string num_str = std::to_string(num);
                num_length = num_str.length();
                const size_t const_num_length = num_length;
                while ((num_length + 4) != 0){
                    std::cout << "-";
                    num_length--;
                }
                std::cout << "\n| " << node->key << " |\n";
                num_length = const_num_length + 4;
                while (num_length != 0){
                    std::cout << "-";
                    num_length--;
                }
                std::cout << "\n";
                return;
            }
        }
/// "Печать на экран"
        void PrintTree(const std::unique_ptr<TreeNode> &node, int space) const {
            if (node == nullptr) {
                return;
            } else {
                space += size_;
                this->PrintTree(node->right, space);
                for (int i = size_; i < space; ++i) {
                    std::cout << " ";
                }
                std::cout << node->key << "\n";
                // DrawRect(node);
                PrintTree(node->left, space);
            }
        }
/// Высота дерева
        uint8_t HeightOfTree(std::unique_ptr<TreeNode> &node) {
            if (node == nullptr){
                return 0;
            } else {
                return 1 + std::max(HeightOfTree(node->right), HeightOfTree(node->left));
            }
        }
/// "Oбходы"
        void inorderTraversal(std::unique_ptr<TreeNode> &node) {
            if (node == nullptr){
                //throw "Node is empty";
            } else {
                inorderTraversal(node->left);
                std::cout << "[" << node->key << "]\n" ;
                inorderTraversal(node->right);
            }
        }
        void preorderTraversal(std::unique_ptr<TreeNode> &node) {
            if (node == nullptr){
                //throw "Node is empty";
            } else {
                std::cout << "[" << node->key << "]\n" ;
                preorderTraversal(node->left);
                preorderTraversal(node->right);
            }
        }
        void postorderTraversal(std::unique_ptr<TreeNode> &node) {
            if (node == nullptr){
                // throw "Node is empty";
            } else {
                postorderTraversal(node->left);
                postorderTraversal(node->right);
                std::cout << "[" << node->key << "]\n" ;
            }
        }

        std::unique_ptr<TreeNode> root_;
        size_t size_;
    };
    template<typename K, typename V>
    class dictionary {
    public:
        dictionary() : search_tree_(BstTree<K, V>()) {}
        V &operator[](K key) {
            if(search_tree_.Contains(key)){
                return search_tree_.Search(key, search_tree_.root_)->value;
            } else std::cout << "No Node with \"" << key << "\" key" << std::endl;
        }
    public:
        void Insert(K key, V value) {
            search_tree_.Insert(key);
            search_tree_.Search(key, search_tree_.root_)->value = value;
        }
        BstTree<K, V> search_tree_;
    };
}
//int main(){
//    BMSTU::dictionary<char, int> k;
//    k.Insert('h',10);
//    k.Insert('v', 15);
//    std::cout << k.search_tree_.Contains('h');
//    std::cout << k['h'] << k['v'];
//}