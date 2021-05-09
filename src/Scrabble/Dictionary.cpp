//
//  Dictionary.cpp


#include "Dictionary.h"

#include <fstream>
#include <string>

using namespace std;


void Dictionary::setLanguage(Language language) {
    ifstream words;
    string auxWord = " ";
    m_words.clear();
    
    m_languagesPath[CATALAN] = "data/Dictionaries/Catalan.dic";
    m_languagesPath[SPANISH] = "data/Dictionaries/Catalan.dic";
    m_languagesPath[ENGLISH] = "data/Dictionaries/Catalan.dic";

    switch (language) 
    {
        case CATALAN:
            words.open(m_languagesPath[CATALAN]);
            if(words.is_open())
            {
                while (!words.eof())
                {
                    words >> auxWord;
                    m_words.push_back(auxWord);
                }
            }
            words.close();
            break;
        case SPANISH:
                words.open(m_languagesPath[SPANISH]);
                if (words.is_open())
                {
                    while(!words.eof())
                    {
                        words >> auxWord;
                        m_words.push_back(auxWord);
                    }
                }
                words.close();
            break;
        case ENGLISH:
            words.open(m_languagesPath[ENGLISH]);
            if (words.is_open())
            {
                while(!words.eof())
                {
                    words >> auxWord;
                    m_words.push_back(auxWord);
                }
            }
            words.close();
            break;

    }
}

bool Dictionary::check(const string &word) {

bool check = false;
int i = 0;
string auxWord;

    while (!check)
    {
        auxWord = m_words[i];
        if (word.compare(auxWord) == 0)
        {
            check = true;
        }
        else
        {
            i++;
        }
    }
    return check;
}