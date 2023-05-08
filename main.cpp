#include <iostream>
#include "EngRusDict.h"
#include "RedBlackTree.h"
#include "DoubleList.h"
#include "RBTNode.h"

DoubleList<std::string> create(std::string str);
RBTNode createNode(std::string str, std::string trans);
void checkDoubleList();
void checkRBTNode();
void checkRBTreee();
void checkDictionaryBase();

void checkDictionaryFichi();

int main() {
    try {
        setlocale(LC_ALL, "Russian");
        checkDictionaryFichi();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what();
        exit(-1);
    }
    return 0;
}

DoubleList<std::string> create(std::string str) {
    DoubleList<std::string> funcList;
    funcList.insert(str);
    return funcList;
}

RBTNode createNode(std::string str, std::string trans) {
    RBTNode temp(str);
    temp.insertTranslate(trans);
    return temp;
}

void checkDictionaryFichi() {
    EngRusDict test;

    std::string temp = "one";
    test.insertWord(temp);
    DoubleList<std::string> list1;
    list1.insert("���");
    list1.insert("����");
    list1.insert("������������");
    list1.insert("������");
    list1.insert("����");
    test.insertManyTrans(temp, list1);
    list1.clear();

    temp = "two";
    test.insertWord(temp);
    list1.insert("���");
    list1.insert("����");
    list1.insert("����");
    list1.insert("������");
    list1.insert("���");
    test.insertManyTrans(temp, list1);
    list1.clear();

    temp = "three";
    test.insertWord(temp);
    list1.insert("���");
    list1.insert("����");
    list1.insert("������");
    list1.insert("�����");
    list1.insert("�������");
    test.insertManyTrans(temp, list1);
    list1.clear();

    temp = "four";
    test.insertWord(temp);
    list1.insert("������");
    list1.insert("��������");
    list1.insert("�������");
    list1.insert("���������");
    list1.insert("��������");
    test.insertManyTrans(temp, list1);
    list1.clear();

    temp = "five";
    test.insertWord(temp);
    list1.insert("����");
    list1.insert("������");
    list1.insert("�����");
    list1.insert("������");
    list1.insert("�������");
    test.insertManyTrans(temp, list1);
    list1.clear();

    temp = "six";
    test.insertWord(temp);
    list1.insert("�����");
    list1.insert("������");
    list1.insert("�������");
    list1.insert("�������");
    list1.insert("������");
    test.insertManyTrans(temp, list1);
    list1.clear();

    std::cout << test << "\n=============================================\n";

    std::cout << test.getTranslate(temp) << "\n=============================================\n";

    std::cout << (test.getNodeColor(temp) ? "RED" : "BLACK") << "\n=============================================\n";

    test.deleteAllTransl(temp);
    std::cout << test << "\n=============================================\n";
  
}

void checkDictionaryBase() {
    EngRusDict test;
    std::string temp = "first";
    test.insertWord(temp);
    std::cout << test << "\n=============================================\n";
    test.insertWord(temp);
    std::cout << test << "\n=============================================\n";

    std::string trans = "������";
    test.insertTranslate(temp, trans);
    trans = "������";
    test.insertTranslate(temp, trans);
    std::cout << test << "\n=============================================\n";

    temp = "second";
    test.insertWord(temp);
    trans = "������";
    test.insertTranslate(temp, trans);
    std::cout << test << "\n=============================================\n";

    temp = "first";
    test.deleteWord(temp);
    std::cout << test << "\n=============================================\n";

    temp = "first";
    test.deleteWord(temp);
    std::cout << test << "\n=============================================\n";

    temp = "second";
    trans = "������";
    test.deleteTranslate(temp, trans);
    std::cout << test << "\n=============================================\n";
}

void checkRBTNode() {
    std::cout << "2. Check const&oper RBTNode\n";

    std::string temp = "one";

    std::cout << "Base constructor\n";
    RBTNode node1(temp);
    std::cout << "node1: " << node1;
    temp = "������";
    node1.insertTranslate(temp);

    std::cout << "\nCopy constructor\n";
    RBTNode node2(node1);
    std::cout << "node1: " << node1;
    std::cout << "node2: " << node2;
    std::cout << "\nSome changes\n";
    temp = "����";
    node1.insertTranslate(temp);
    std::cout << "node1: " << node1;
    std::cout << "node2: " << node2 << '\n';
    std::cout << "\nSome changes\n";
    temp = "���";
    node2.insertTranslate(temp);
    std::cout << "node1: " << node1;
    std::cout << "node2: " << node2;


    std::cout << "\nCopy-move constructor\n";
    temp = "two";
    std::string trans = "���";
    RBTNode node3 = createNode(temp, trans);
    std::cout << "node3: " << node3;

    std::cout << "\nCopy operator\n";
    std::cout << "Befor\n";
    std::cout << "node1: " << node1;
    std::cout << "node3: " << node3;
    node3 = node1;
    std::cout << "After\n";
    std::cout << "node1: " << node1;
    std::cout << "node3: " << node3;
    std::cout << "\nSome changes\n";
    temp = "������������";
    node1.insertTranslate(temp);
    std::cout << "node1: " << node1;
    std::cout << "node3: " << node3 << '\n';
    std::cout << "Some changes\n";
    temp = "���";
    node3.insertTranslate(temp);
    std::cout << "node1: " << node1;
    std::cout << "node3: " << node3;

    std::cout << "\nMove operator\n";
    temp = "three";
    trans = "���";
    node3 = createNode(temp, trans);
    std::cout << "node3: " << node3;
}

void checkDoubleList() {
    std::cout << "1. Check constr&oper DoubleList\n";

    std::cout << "Base constructor:\n";
    std::string temp = "hello";
    DoubleList<std::string> list1;
    list1.insert(temp);
    temp = "newWord";
    list1.insert(temp);
    list1.print();

    std::cout << "\nCopy constructor:\n";
    DoubleList<std::string> list2(list1);
    std::cout << "list2: ";
    list2.print();
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nSome changes\n";
    temp = "killmeee";
    list1.insert(temp);
    std::cout << "list2: ";
    list2.print();
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nSome chages\n";
    temp = "tresh";
    list2.insert(temp);
    std::cout << "list2: ";
    list2.print();
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nCopy operator:\n";
    DoubleList<std::string> list3;
    list3 = list1;
    std::cout << "list3: ";
    list3.print();
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nSome changes\n";
    temp = "bla-bla";
    list1.insert(temp);
    std::cout << "list3: ";
    list3.print();
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nSome chages\n";
    temp = "paradis";
    list3.insert(temp);
    std::cout << "list3: ";
    list3.print();
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nCopy-move constractor\n";
    DoubleList<std::string> list4 = create("copy-move");
    std::cout << "list4: ";
    list4.print();

    std::cout << "\nMove operator\n";
    std::cout << "list5: ";
    list3 = create("goodbay");
    list3.print();
}

void checkRBTreee() {
    RedBlackTree<RBTNode> test;
    std::string temp = "tree";
    RBTNode word(temp);
    temp = "������";
    word.insertTranslate(temp);
    temp = "�����";
    word.insertTranslate(temp);
    test.insert(word);
    test.preorder();
    std::cout << "\n=========================================\n";
    temp = "hello";
    RBTNode word2(temp);
    temp = "������";
    word2.insertTranslate(temp);
    temp = "������������";
    word2.insertTranslate(temp);
    test.insert(word2);
    test.preorder();

    std::cout << "\n=========================================\n";
    RedBlackTree<RBTNode> test2(test);
    test.preorder();
    test2.preorder();
}