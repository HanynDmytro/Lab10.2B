#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };  // Перелічувальний тип для спеціальностей студентів

// Масив рядків для відображення назв спеціальностей
string strSpec[] = { "Комп'ютернi науки", "Iнформатика", "Математика та економiка", "Фiзика та iнформатика", "Трудове навчання" };

// Структура для зберігання інформації про студента
struct Student {
    string lname;   // Прізвище
    int kurs;       // Курс
    Spec spec;      // Спеціальність
    int physics;    // Оцінка з фізики
    int math;       // Оцінка з математики
    union {         // Об'єднання для третьої оцінки в залежності від спеціальності
        int programming;    // Оцінка з програмування (для CS)
        int numMethods;     // Оцінка з чисельних методів (для IT)
        int pedagogy;       // Оцінка з педагогіки (для решти спеціальностей)
    };
};

// Функція для введення даних про студентів
void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "Прiзвище: ";
        cin >> s[i].lname;
        cout << "Курс: ";
        cin >> s[i].kurs;
        cout << "Спецiальнiсть (0 - Комп'ютернi науки, 1 - Iнформатика, 2 - Математика та економiка, "
            << "3 - Фiзика та iнформатика, 4 - Трудове навчання): ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "Оцiнка з фiзики: ";
        cin >> s[i].physics;
        cout << "Оцiнка з математики: ";
        cin >> s[i].math;

        // Введення третьої оцінки залежно від спеціальності
        if (s[i].spec == CS) {
            cout << "Оцiнка з програмування: ";
            cin >> s[i].programming;
        }
        else if (s[i].spec == IT) {
            cout << "Оцiнка з чисельних методів: ";
            cin >> s[i].numMethods;
        }
        else {
            cout << "Оцiнка з педагогіки: ";
            cin >> s[i].pedagogy;
        }
        cout << endl;
    }
}

// Функція для виведення даних про студентів у табличному форматі
void Print(Student* s, int amSt) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| № | Прiзвище      | Курс | Спецiальнiсть           | Фiзика | Матем. | Прог. | Чис.мет. | Педагог. |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < amSt; i++) {
        cout << "| " << setw(2) << right << i + 1 << ""
            << " | " << setw(13) << left << s[i].lname
            << " | " << setw(4) << right << s[i].kurs
            << " | " << setw(22) << left << strSpec[s[i].spec]
            << " | " << setw(6) << right << s[i].physics
            << " | " << setw(6) << right << s[i].math
            << " | ";

        // Виведення третьої оцінки в відповідну колонку
        if (s[i].spec == CS)
            cout << setw(5) << right << s[i].programming << " | " << setw(8) << " " << " | " << setw(8) << " ";
        else if (s[i].spec == IT)
            cout << setw(5) << " " << " | " << setw(8) << right << s[i].numMethods << " | " << setw(8) << " ";
        else
            cout << setw(5) << " " << " | " << setw(8) << " " << " | " << setw(8) << right << s[i].pedagogy;

        cout << " |" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------\n";
}

double findMark(Student* p, const int N) {
    switch (p[N].spec) {
    case CS:
        return ((p[N].math + p[N].physics + p[N].programming) / 3.0);
        break;
    case IT:
        return ((p[N].math + p[N].physics + p[N].numMethods) / 3.0);
    default:
        return ((p[N].math + p[N].physics + p[N].pedagogy) / 3.0);
    }
}

// Функція для фізичного сортування масиву студентів за спеціальністю, оцінкою з математики та прізвищем
void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].kurs > p[i1 + 1].kurs) ||
                (p[i1].kurs == p[i1 + 1].kurs && findMark(p, i1) < findMark(p, i1 + 1)) ||
                (p[i1].kurs == p[i1 + 1].kurs && findMark(p, i1) == findMark(p, i1 + 1) &&
                    p[i1].lname < p[i1 + 1].lname))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

// Функція для індексного сортування масиву студентів
int* indexSort(Student* s, const int N) {
    int* P = new int[N];  // Масив індексів
    for (int i = 0; i < N; i++)
        P[i] = i;

    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((s[P[i1]].kurs > s[P[i1 + 1]].kurs) ||
                (s[P[i1]].kurs == s[P[i1 + 1]].kurs && findMark(s, P[i1]) < findMark(s, P[i1 + 1])) ||
                (s[P[i1]].kurs == s[P[i1 + 1]].kurs && findMark(s, P[i1]) == findMark(s, P[i1 + 1]) &&
                    s[P[i1]].lname < s[P[i1 + 1]].lname))
            {
                int tmp = P[i1];
                P[i1] = P[i1 + 1];
                P[i1 + 1] = tmp;
            }
    return P;
}

// Функція для виведення індексно відсортованого масиву студентів
void PrintIndexSorted(Student* s, int* P, const int N) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| № | Прiзвище      | Курс | Спецiальнiсть           | Фiзика | Матем. | Прог. | Чис.мет. | Педагог. |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << ""
            << " | " << setw(13) << left << s[P[i]].lname
            << " | " << setw(4) << right << s[P[i]].kurs
            << " | " << setw(22) << left << strSpec[s[P[i]].spec]
            << " | " << setw(6) << right << s[P[i]].physics
            << " | " << setw(6) << right << s[P[i]].math
            << " | ";

        if (s[P[i]].spec == CS)
            cout << setw(5) << right << s[P[i]].programming << " | " << setw(8) << " " << " | " << setw(8) << " ";
        else if (s[P[i]].spec == IT)
            cout << setw(5) << " " << " | " << setw(8) << right << s[P[i]].numMethods << " | " << setw(8) << " ";
        else
            cout << setw(5) << " " << " | " << setw(8) << " " << " | " << setw(8) << right << s[P[i]].pedagogy;

        cout << " |" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------\n";
}

// Функція для бінарного пошуку студента за прізвищем, спеціальністю та оцінкою з фізики
int binSearch(Student* p, const int N, const string prizv, int const kurs, const double avr)
{
    for (int i = 0; i < N; i++)
    {
        if (p[i].lname == prizv && p[i].kurs == kurs && findMark(p, i) == avr) {
            return i;
        }
    }
    return -1;
}
int main() {
    SetConsoleCP(1251);    // Для коректного введення українських символів у консолі
    SetConsoleOutputCP(1251); // Для коректного відображення українських символів у консолі

    int N; // Кількість студентів
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* s = new Student[N]; // Динамічний масив студентів

    Create(s, N);   // Виклик функції для заповнення даних студентів
    cout << "\nСтворений список студентів:\n";
    Print(s, N);    // Виведення студентів у початковому порядку

    Sort(s, N);     // Фізичне сортування масиву студентів
    cout << "\nСписок студентів після фізичного сортування:\n";
    Print(s, N);    // Виведення студентів після фізичного сортування

    int* indexArray = indexSort(s, N);   // Індексне сортування
    cout << "\nСписок студентів після індексного сортування:\n";
    PrintIndexSorted(s, indexArray, N);  // Виведення студентів у порядку індексного сортування

    string prizv;
    int kurs, avrGrade;
    cout << "Введіть прізвище: "; cin >> prizv;
    cout << "Введіть курс: "; cin >> kurs;
    cout << "Введіть середню оцінку: "; cin >> avrGrade;

    int found = binSearch(s, N, prizv, kurs, avrGrade);

    if (found != -1)
        cout << "Знайдено студента в позиції " << found + 1 << endl;
    else
        cout << "Шуканого студента не знайдено" << endl;

    delete[] s;          // Звільнення пам'яті
    delete[] indexArray; // Звільнення пам'яті для індексного масиву

    return 0;
}
