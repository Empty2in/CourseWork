#include <iostream>
#include <fstream>
#include <locale>
#include <Windows.h>
#include "EngRusDict.h"
#include "DoubleList.h"

void openFile(std::fstream& in, std::string& fileName);
void readDictFromFail(std::fstream& in, EngRusDict& dictionary);
bool checkWord(std::string word);
std::string enterWord(std::istream& in);

void mainMenu();
void actWithDict(EngRusDict& dictionary);

void checkEmptyDictionary();
void checkFileDict();

void checkException(EngRusDict& dictionary);

void checkInsert(EngRusDict& dictionary);
void insertManyWords(EngRusDict& dictionary);
void insertOneWord(EngRusDict& dictionary);
void insertOneTranslate(EngRusDict& dictionary);
void insertManyTranslate(EngRusDict& dictionary);

void checkDelete(EngRusDict& dictionary);
void checkOneWordDelete(EngRusDict& dictionary);
void checkOneTranslDelete(EngRusDict& dictionary);
void checkAllTranslDelete(EngRusDict& dictionary);

void checkSearch(EngRusDict& dictionary);

void checkAsRBTree(EngRusDict& dictionary);

void checkOneWord(EngRusDict& dictionary);


int main() {
    try {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        setlocale(LC_ALL, "Russian");
        mainMenu();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what();
        exit(-1);
    }
    return 0;
}

void openFile(std::fstream& in, std::string& fileName) {
    std::cout << "Enter name of file: ";
    std::cin >> fileName;
    in.open(fileName);
    if (!in.is_open()) {
        throw std::exception("Incorrrect name of file.");
    }
    if (in.peek() == EOF) {
        throw std::exception("file is empty.");
    }
}

void readDictFromFail(std::fstream& in, EngRusDict& dictionary) {
    while (!in.eof()) {
        std::string newWord, newTransl;
        int countTransl = 0;
        std::getline(in, newWord);
        if (!checkWord(newWord)) {
            throw std::exception("wrong word in file.");
        }
        in >> countTransl;
        if (in.peek() == ',') {
            throw std::exception("wrong number of translation in file.");
        }
        in.ignore(1000, '\n');
        for (int i = 0; i < countTransl; ++i) {
            std::getline(in, newTransl);
            if (!checkWord(newTransl)) {
                throw std::exception("wrong translation in file.");
            }
            dictionary.insertTranslate(newWord, newTransl);
        }
        in.ignore(1000, '\n');
    }
    in.close();
}

bool checkWord(std::string word) {
    for (unsigned char c : word) {
        if (!static_cast<bool>(std::isalpha(c)) && c != ' ' && c != '-') {
            return false;
        }
    }
    return true;
}


std::string enterWord(std::istream& in) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    std::string word;
    std::getline(in, word, '\n');
    if (word == "x") {
        return word;
    }
    if (!checkWord(word)) {
        throw std::exception("wrong word");
    }
    return word;

}

void mainMenu() {
    int com = 0;
    while (com != 3) {
        std::cout << "\nEnter the number of which English-Russian Dictionary you need:\n1. Make empty dictionary.\n2. Make dictionary from file.\n3. Exit.\n";
        std::cin >> com;
        switch (com) {
        case 1: checkEmptyDictionary(); continue;
        case 2: checkFileDict(); continue;
        case 3: exit(0);
        default: std::cout << "\nChoose the number from list.\n "; continue;
        }
    }
}

void actWithDict(EngRusDict& dictionary) {
    int com = 0;
    while (com != 7) {
        std::cout << "\nEnter the number of action with English-Russian Dictionary:\n1. Check insert\n2. Check Delete.\n3. Check search.\n4. Info about one word.\n5. Print as RBTree.\n6. Check Exception. (WARRNING!!!)\n7. Return in main menu.\n";
        std::cin >> com;
        switch (com) {
        case 1: checkInsert(dictionary); continue;
        case 2: checkDelete(dictionary); continue;
        case 3: checkSearch(dictionary); continue;
        case 4: checkOneWord(dictionary); continue;
        case 5: checkAsRBTree(dictionary); continue;
        case 6: checkException(dictionary); continue;
        case 7: return;
        default: std::cout << "\nChoose the number from list.\n "; continue;
        }
    }
}

void checkEmptyDictionary() {
    EngRusDict dictionary;
    std::cout << dictionary;
    actWithDict(dictionary);
}
void checkFileDict() {
    EngRusDict dictionary;
    std::fstream in;
    std::string fileName;
    openFile(in, fileName);
    readDictFromFail(in, dictionary);
    std::cout << dictionary;
    actWithDict(dictionary);
}

void checkException(EngRusDict& dictionary) {
    std::cout << "Now you can give me incorrect words, but after this program will be stop work.\n";
    actWithDict(dictionary);
}

void checkInsert(EngRusDict& dictionary) {
    int com = 0;
    while (com != 5) {
        std::cout << "\nChoose what you want to insert:\n1. New word (whithout translation)\n2. Many new word.\n3. New translate (just one)\n4. Many new translate.\n5. Return to action menu.\n";
        std::cin >> com;
        switch (com) {
        case 1: insertOneWord(dictionary); continue;
        case 2: insertManyWords(dictionary); continue;
        case 3: insertOneTranslate(dictionary); continue;
        case 4: insertManyTranslate(dictionary); continue;
        case 5: return;
        default: std::cout << "\nChoose the number from list.\n "; continue;
        }
    }
}
void insertOneWord(EngRusDict& dictionary) {
    std::cout << "\nEnter one english word: ";
    dictionary.insertWord(enterWord(std::cin));
    std::cout << dictionary;
    return;
}
void insertManyWords(EngRusDict& dictionary) {
    std::cout << "Enter english words. When you want to stop - enter 'x'\n";
    std::string newWord;
    while (newWord != "x") {
        newWord = enterWord(std::cin);
        if (newWord == "x") {
            break;
        }
        dictionary.insertWord(newWord);
    }
    std::cout << dictionary;
    return;
}
void insertOneTranslate(EngRusDict& dictionary) {
    std::cout << "\nEnter word, which translate you want to insert: ";
    std::string newWord = enterWord(std::cin);
    std::cout << "Enter russian translate for it : ";
    std::string newTransl = enterWord(std::cin);
    dictionary.insertTranslate(newWord, newTransl);
    std::cout << dictionary;
    return;
}
void insertManyTranslate(EngRusDict& dictionary) {
    std::cout << "\nEnter word, which translate you want to insert: ";
    std::string newWord = enterWord(std::cin);
    std::cout << "Enter russian translates for it. When you want to stop - enter 'x':\n";
    std::string newTransl;
    while (newTransl != "x") {
        newTransl = enterWord(std::cin);
        if (newTransl == "x") {
            break;
        }
        dictionary.insertTranslate(newWord, newTransl);
    }
    std::cout << dictionary;
    return;
}

void checkDelete(EngRusDict& dictionary) {
    int com = 0;
    while (com != 4) {
        std::cout << "\nChoose what you want to delete:\n1.One word\n2.One translate.\n3.All translate\n4. Return to action menu\n";
        std::cin >> com;
        switch (com) {
        case 1: checkOneWordDelete(dictionary); continue;
        case 2: checkOneTranslDelete(dictionary); continue;
        case 3: checkAllTranslDelete(dictionary); continue;
        case 4: return;
        default: std::cout << "\nChoose the number from list.\n "; continue;
        }
    }
    
}
void checkOneWordDelete(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::cout << "\nEnter one english word in dict, which you want to delete: ";
    dictionary.deleteWord(enterWord(std::cin));
    std::cout << dictionary;
    return;
}
void checkOneTranslDelete(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::cout << "\nEnter one english word in dict, where you want to delete: ";
    std::string word = enterWord(std::cin);
    std::cout << "Enter one translate, which you whant to delete: ";
    std::string delTransl = enterWord(std::cin);
    dictionary.deleteTranslate(word, delTransl);
    std::cout << dictionary;
    return;
}
void checkAllTranslDelete(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::cout << "\nEnter one english word in dict, which translate you want to delete: ";
    dictionary.deleteAllTransl(enterWord(std::cin));
    std::cout << dictionary;
    return;
}

void checkSearch(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::cout << "\nEnter one english word in dict, which you want to find: ";
    std::string word = enterWord(std::cin);
    std::cout << (dictionary.searchWord(word) ? 
        "\nThis word is in dictionary\n" : 
        "\nThis word isn't in dictionary\n");
    return;
}

void checkAsRBTree(EngRusDict& dictionary) {
    dictionary.printRBTree();
    return;
}

void checkOneWord(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::cout << "\nEnter word, which info you want to learn: ";
    std::string word = enterWord(std::cin);
    std::cout << "\nInfo about word '" << word << "' :";
    std:: cout << "\n\tTranslations: " << dictionary.getTranslate(word);
    std:: cout << "\n\tCount of translations: " << dictionary.getTranslCount(word);
    std::cout << "\n\tNode color: " << (dictionary.getNodeColor(word) ? "RED" : "BLACK");
    std::cout << "\n\tCount of words on dictionary: " << dictionary.getCountOfWord();
    return;
}