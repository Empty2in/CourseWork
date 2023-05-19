#include "TestFunc.h"
#include "EngRusDict.h"
#include "DoubleList.h"
#include "InputException.h"
#include "Phrases.h"
#include <iostream>
#include <fstream>
#include <Windows.h>


void openFile(std::fstream& in, std::string& fileName) {
    std::cout << "Enter name of file: ";
    std::cin >> fileName;
    in.open(fileName);
    if (!in.is_open()) {
        throw IncorrectFile();
    }
    if (in.peek() == EOF) {
        throw EmptyFile();
    }
}
void writeToFile(EngRusDict& dictionary) {
    std::ofstream out;
    std::string fileName;
    std::cout << "Enter name of file: ";
    std::cin >> fileName;
    out.open(fileName);
    out << dictionary;
    out.close();
}
void createFileDict(EngRusDict& dictionary) {
    std::fstream in;
    std::string fileName;
    openFile(in, fileName);
    readDictFromFail(in, dictionary);
}

void readDictFromFail(std::fstream& in, EngRusDict& dictionary) {
    while (!in.eof()) {
        std::string newWord, newTransl;
        DoubleList< std::string > list;
        size_t countTransl = 0;
        enterWord(in, newWord);
        enterInt(in, countTransl);
        for (int i = 0; i < countTransl; ++i) {
            enterWord(in, newTransl);
            list.insert(newTransl);
        }
        dictionary.insertManyTrans(newWord, list);
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
void enterInt(std::istream& in, size_t& count) {
    in >> count;
    if (in.peek() != '\n') {
        throw WrongInt();
    }
    in.ignore(1000, '\n');
}
std::string helpIO(std::string phrase, bool ignore) {
    std::cout << phrase;
    if (ignore) {
        std::cin.ignore(1000, '\n');
    }
    std::string word;
    enterWord(std::cin, word);
    return word;
}
void helpIOList(std::istream& in, DoubleList< std::string >& list) {
    std::cout << insertRussianword << whenStop;
    std::string newTransl;
    while (in) {
        enterWord(in, newTransl);
        if (newTransl == "x" || newTransl == "÷") {
            break;
        }
        list.insert(newTransl);
    }
}
void enterWord(std::istream& in, std::string& word) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    std::getline(in, word);
    if (!checkWord(word)) {
        throw WrongWord();
    }
}

void mainMenu() {
    char com = ' ';
    while (com) {
        std::cout << mainMenuPhrase;
        std::cin >> com;
        switch (com) {
        case '1': checkEmptyDictionary(); break;
        case '2': checkFileDict(); break;
        case '3': exit(0);
        default: 
            std::cout << defaultPhrase; break;
        }
    }
}
void actWithDict(EngRusDict& dictionary) {
    char com = ' ';
    while (com) {
        std::cout << actWithDictPhrase;
        std::cin >> com;
        switch (com) {
        case '1': checkInsert(dictionary); break;
        case '2': checkDelete(dictionary); break;
        case '3': checkSearch(dictionary); break;
        case '4': checkOneWord(dictionary); break;
        case '5': checkAsRBTree(dictionary); break;
        case '6': writeToFile(dictionary); break;
        case '7': return;
        default: std::cout << defaultPhrase; break;
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
    createFileDict(dictionary);
    std::cout << dictionary;
    actWithDict(dictionary);
}

void checkInsert(EngRusDict& dictionary) {
    char com = ' ';;
    while (com) {
        std::cout << checkInsertPhrase;
        std::cin >> com;
        switch (com) {
        case '1': insertOneWord(dictionary); break;
        case '2': insertManyWords(dictionary); break;
        case '3': insertOneTranslate(dictionary); break;
        case '4': insertManyTranslate(dictionary); break;
        case '5': changeTranslate(dictionary); break;
        case '6': return;
        default: std::cout << defaultPhrase; break;
        }
    }
}
void insertOneWord(EngRusDict& dictionary) {
    dictionary.insertWord(helpIO(insertEngWord, true));
    std::cout << dictionary;
    return;
}
void insertManyWords(EngRusDict& dictionary) {
    std::cout << insertEngWord << whenStop;
    std::cin.ignore(1000, '\n');
    std::string newWord;
    while (std::cin) {
        enterWord(std::cin, newWord);
        if (newWord == "x" || newWord == "÷") {
            break;
        }
        dictionary.insertWord(newWord);
    }
    std::cout << dictionary;
    return;
}
void insertOneTranslate(EngRusDict& dictionary) {
    std::string word = helpIO(engWordForTransl, true);
    std::string transl = helpIO(insertRussianword, false);
    dictionary.insertTranslate(word, transl);
    std::cout << dictionary;
    return;
}
void insertManyTranslate(EngRusDict& dictionary) {
    std::string word = helpIO(engWordForTransl, true);
    DoubleList< std::string > list;
    helpIOList(std::cin, list);
    dictionary.insertManyTrans(word, list);
    std::cout << dictionary;
    return;
}
void changeTranslate(EngRusDict& dictionary) {
    std::string word = helpIO(engWordForTransl, true);
    DoubleList< std::string > list;
    helpIOList(std::cin, list);
    dictionary.changeAllTransl(word, list);
    std::cout << dictionary;
    return;
}

void checkDelete(EngRusDict& dictionary) {
    char com = ' ';;
    while (com) {
        std::cout << checkDeletePhrase;
        std::cin >> com;
        switch (com) {
        case '1': checkOneWordDelete(dictionary); break;
        case '2': checkOneTranslDelete(dictionary); break;
        case '3': checkAllTranslDelete(dictionary); break;
        case '4': return;
        default: std::cout << defaultPhrase; break;
        }
    }
}
void checkOneWordDelete(EngRusDict& dictionary) {
    std::cout << dictionary;
    dictionary.deleteWord(helpIO(deleteEngWord, true));
    std::cout << dictionary;
    return;
}
void checkOneTranslDelete(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::string word = helpIO(deleteWordAllTransl, true);
    std::string transl = helpIO(deleteTransl, false);
    dictionary.deleteTranslate(word, transl);
    std::cout << dictionary;
    return;
}
void checkAllTranslDelete(EngRusDict& dictionary) {
    std::cout << dictionary;
    dictionary.deleteAllTransl(helpIO(deleteWordAllTransl, true));
    std::cout << dictionary;
    return;
}

void checkSearch(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::cout << (dictionary.searchWord(helpIO(searchWord, true)) ?
        "\nThis word is in dictionary\n" :
        "\nThis word isn't in dictionary\n");
    return;
}

void checkAsRBTree(EngRusDict& dictionary) {
    dictionary.printRBTree(std::cout);
    return;
}

void checkOneWord(EngRusDict& dictionary) {
    std::cout << dictionary;
    std::string word = helpIO(infoWord, true);

    std::cout << "\nInfo about word '" << word << "' :";
    if (!dictionary.searchWord(word)) {
        std::cout << "\n\tThere is no such word in dictionary!";
        return;
    }
    std::cout << "\n\tTranslations: " << dictionary.getTranslate(word);
    std::cout << "\n\tCount of translations: " << dictionary.getTranslCount(word);
    std::cout << "\n\tNode color: " << (dictionary.getNodeColor(word) ? "RED" : "BLACK");
    std::cout << "\n\tCount of words on dictionary: " << dictionary.getCountOfWord();
    return;
}