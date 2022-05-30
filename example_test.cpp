#include <gtest/gtest.h>
#include <string>
#include "tree.cpp"

TEST(TREE, Contains){
    BMSTU::BstTree<int,int> tree;
    tree.Insert(12);
    ASSERT_TRUE(tree.Contains(12));
}
TEST(TREE, Insert){
    BMSTU::BstTree<int, int> tree;
    for (int i = 0; i < 15; ++i) {
        tree.Insert(i);
    }
    bool contains = false;
    for (int i = 0; i < 15; ++i) {
        if (tree.Contains(i)) contains = true; else contains = false;
    }
    ASSERT_TRUE(contains);
}
TEST(TREE, Remove){
    BMSTU::BstTree<int, int> tree;
    for (int i = 0; i < 16; ++i) {
        tree.Insert(i);
    }
    size_t Height_before_remove = tree.Height();
    tree.Remove(7);
    size_t Height_after_remove = tree.Height();
    ASSERT_FALSE(tree.Contains(7));
    ASSERT_EQ(Height_before_remove, 5);
    ASSERT_EQ(Height_after_remove, 4);
}

TEST(TREE, Size){
    BMSTU::BstTree<int, int> tree;
    size_t first_size = tree.Size();
    for (int i = 0; i < 15; ++i) {
        tree.Insert(i);
    }
    size_t second_size = tree.Size();
    ASSERT_EQ(first_size, 0);
    ASSERT_EQ(second_size, 15);
}
TEST(TREE, Height){
    BMSTU::BstTree<int, int> tree;
    size_t first_height = tree.Height();
    for (int i = 0; i < 15; ++i) {
        tree.Insert(i);
    }
    size_t second_height = tree.Height();
    ASSERT_EQ(first_height, 0);
    ASSERT_EQ(second_height, 4);
}
TEST(TREE, Find_min_key){
    BMSTU::BstTree<int, int> tree;
    for (int i = 0; i < 15; ++i) {
        tree.Insert(i);
    }
    size_t min_key = tree.Find_min_key();
    ASSERT_EQ(min_key, 0);
}
TEST(TREE, Find_max_key){
    BMSTU::BstTree<int, int> tree;
    for (int i = 0; i < 15; ++i) {
        tree.Insert(i);
    }
    size_t max_key = tree.Find_max_key();
    ASSERT_EQ(max_key, 14);
}
TEST(Dictionary, Index_operator){
    BMSTU::dictionary<char, int> Dict_with_char_key;
    Dict_with_char_key.Insert('a',345);
    BMSTU::dictionary<std::string , int> Dict_with_string_key;
    Dict_with_string_key.Insert("bababa",1000);
    ASSERT_EQ(Dict_with_char_key['a'], 345);
    ASSERT_EQ(Dict_with_string_key["bababa"], 1000);
}
TEST(Dictionary, Insert){
    BMSTU::dictionary<std::string , int> Dict_with_string_key;
    Dict_with_string_key.Insert("bababa",1000);
    ASSERT_EQ(Dict_with_string_key["bababa"], 1000);
}

