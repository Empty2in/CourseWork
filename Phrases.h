#ifndef RHRASES_H
#define RHRASES_H

#include <string>

std::string mainMenuPhrase = "\nEnter the number of which English-Russian Dictionary you need:\n1. Make empty dictionary.\n2. Make dictionary from file.\n3. Exit.\n";
std::string defaultPhrase = "\nChoose the number from list.\n ";
std::string actWithDictPhrase = "\nEnter the number of action with English-Russian Dictionary:\n1. Check insert\n2. Check Delete.\n3. Check search.\n4. Info about one word.\n5. Check as RBTree.\n6. Save the dictionary.\n7. Return in main menu.\n";
std::string checkTwoDictsPhrase = "\nEnter the number of action with English-Russian Dictionaries:\n1. Check merge dictionary.\n2.Check dictionaries is equal\n3. Return in main menu.\n";
std::string checkInsertPhrase = "\nChoose what you want to insert:\n1. New word (whithout translation)\n2. Many new word.\n3. New translate (just one)\n4. Many new translate.\n5. Change All translate.\n6. Return to action menu.\n";
std::string checkDeletePhrase = "\nChoose what you want to delete:\n1. One word\n2. One translate.\n3. All translate\n4. Return to action menu\n";
std::string insertEngWord = "Enter english word, which you whant to insert: ";
std::string engWordForTransl = "\nEnter word, which translate you want to insert: ";
std::string insertRussianword = "Enter russian translates for it: ";
std::string whenStop = "When you want to stop - enter 'x'\n";
std::string deleteEngWord = "\nEnter one english word in dict, which you want to delete: ";
std::string deleteTransl = "Enter one translate, which you whant to delete: ";
std::string deleteWordAllTransl = "\nEnter one english word in dict, which translate you want to delete: ";
std::string searchWord = "\nEnter one english word in dict, which you want to find: ";
std::string infoWord = "\nEnter word, which info you want to learn: ";

#endif

