#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

// Функция для проверки, можно ли добавить слово в кроссворд
bool canAddWord(const string& word, const string& lastWord) {
    return lastWord.empty() || word[0] == lastWord.back();
}

// Функция для поиска кроссворда
void findCrossword(const vector<string>& words, vector<string>& current, unordered_set<string>& usedWords, int& maxLength, vector<string>& maxCrossword) {
    // Если текущий кроссворд больше максимального, обновляем максимальный кроссворд
    if (current.size() > maxLength) {
        maxLength = current.size();
        maxCrossword = current;
    }

    // Пробуем добавить каждое слово в кроссворд
    for (const string& word : words) {
        if (!usedWords.count(word) && canAddWord(word, current.empty() ? "" : current.back())) {
            // Добавляем слово в кроссворд и помечаем его как использованное
            current.push_back(word);
            usedWords.insert(word);

            // Рекурсивно ищем кроссворд с новым словом
            findCrossword(words, current, usedWords, maxLength, maxCrossword);

            // Удаляем слово из кроссворда и убираем пометку о том, что оно использовалось
            current.pop_back();
            usedWords.erase(word);
        }
    }
}

// Функция для построения кроссворда из заданных слов
vector<string> buildCrossword(const vector<string>& words) {
    vector<string> current; // Текущий кроссворд
    unordered_set<string> usedWords; // Использованные слова
    int maxLength = 0; // Максимальная длина кроссворда
    vector<string> maxCrossword; // Максимальный кроссворд

    // Ищем кроссворд
    findCrossword(words, current, usedWords, maxLength, maxCrossword);

    return maxCrossword;
}

int main() {
    // Тест 1: Простой набор слов
    vector<string> words1 = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    vector<string> crossword1 = buildCrossword(words1);
    cout << "Test 1:" << endl;
    for (const string& word : crossword1) {
        cout << word << endl;
    }

    // Тест 2: Набор слов, где нет возможности построить кроссворд
    vector<string> words2 = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew"};
    vector<string> crossword2 = buildCrossword(words2);
    cout << "Test 2:" << endl;
    for (const string& word : crossword2) {
        cout << word << endl;
    }

    // Тест 3: Набор слов, где есть возможность построить кроссворд
    vector<string> words3 = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "ice", "juice"};
    vector<string> crossword3 = buildCrossword(words3);
    cout << "Test 3:" << endl;
    for (const string& word : crossword3) {
        cout << word << endl;
    }

    // Тест 4: Набор слов, содержащий повторяющиеся слова
    vector<string> words4 = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "apple", "banana"};
    vector<string> crossword4 = buildCrossword(words4);
    cout << "Test 4:" << endl;
    for (const string& word : crossword4) {
        cout << word << endl;
    }

    // Тест 5: Набор слов, содержащий пустые слова
    vector<string> words5 = {"apple", "banana", "", "date", "elderberry", "fig", "grape"};
    vector<string> crossword5 = buildCrossword(words5);
    cout << "Test 5:" << endl;
    for (const string& word : crossword5) {
        cout << word << endl;
    }

    return 0;
}


