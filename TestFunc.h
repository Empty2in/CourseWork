#ifndef TESTFUNC_H
#define TESTFUNC_H

#include "EngRusDict.h"
#include <string>
#include <fstream>

void openFile(std::fstream& in, std::string& fileName);
void writeToFile(EngRusDict& dictionary);
void readDictFromFail(std::fstream& in, EngRusDict& dictionary);
void createFileDict(EngRusDict& dictionary);

bool checkWord(std::string word);
void enterWord(std::istream& in, std::string& word);
void enterInt(std::istream& in, size_t& count);
void helpIOList(std::istream& in, DoubleList< std::string >& list);
std::string helpIO(std::string phrase, bool ignore);

void mainMenu();
void actWithDict(EngRusDict& dictionary);

void checkEmptyDictionary();
void checkFileDict();

void checkInsert(EngRusDict& dictionary);
void insertManyWords(EngRusDict& dictionary);
void insertOneWord(EngRusDict& dictionary);
void insertOneTranslate(EngRusDict& dictionary);
void insertManyTranslate(EngRusDict& dictionary);
void changeTranslate(EngRusDict& dictionary);

void checkDelete(EngRusDict& dictionary);
void checkOneWordDelete(EngRusDict& dictionary);
void checkOneTranslDelete(EngRusDict& dictionary);
void checkAllTranslDelete(EngRusDict& dictionary);

void checkSearch(EngRusDict& dictionary);

void checkAsRBTree(EngRusDict& dictionary);

void checkOneWord(EngRusDict& dictionary);

#endif
