#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class DFA {
public:
    DFA() {
        // Инициализируем таблицу переходов
        string alf = "ABEKMHOPCTXY";
        transitionTable = {
            {0, createTransitionMap(alf, 1)},
            {1, createTransitionMap(alf, 2)},
            {2, createTransitionMap("[0-9]", 3)},
            {3, createTransitionMap("[0-9]", 4)},
            {4, createTransitionMap("[0-9]", 5)},
            {5, createTransitionMap(alf, 6)},
            {6, {}}
        };
        // Начальное состояние
        currentState = 0;
        // Задаем конечное состояние
        acceptingStates = { 6 };
    }

    // Функция для обработки символов
    void transition(char input) {
        if (transitionTable[currentState].count(input)) {
            currentState = transitionTable[currentState][input];
        }
        else {
            cerr << "Ошибка: недопустимый символ '" << input << "' для текущего состояния" << endl;
        }
    }

    // Функция для проверки, является ли текущее состояние конечным
    bool isAccepting() const {
        return acceptingStates.count(currentState) > 0;
    }

private:
    int currentState;
    unordered_map<int, unordered_map<char, int>> transitionTable;
    unordered_set<int> acceptingStates;

    // Функция для создания карты переходов для заданного диапазона символов
    unordered_map<char, int> createTransitionMap(const string& range, int nextState) {
        unordered_map<char, int> map;
        if (range[1] == '0') {
            for (char c = range[1]; c <= range[3]; ++c) {
                map[c] = nextState;
            }
        } else {
            for (char c = 0; c <= range.size(); ++c) {
                map[range[c]] = nextState;
            }
        }
        return map;
    }
};

int main() {
    setlocale(LC_ALL, "");
    DFA dfa;
    string input;

    cout << "Введите номерной знак автомобиля (буквы английские заглавные - AA000A): ";
    cin >> input;

    // Обрабатываем каждый символ входной строки
    for (char c : input) {
        dfa.transition(c);
    }

    // Проверяем, является ли строка принимаемой
    if (dfa.isAccepting()) cout << "Строка принимается - это российский номерной знак!" << endl;
    else cout << "Строка не принимается - возможно, вы видели карету." << endl;

    return 0;
}
