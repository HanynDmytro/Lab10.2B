#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };  // �������������� ��� ��� �������������� ��������

// ����� ����� ��� ����������� ���� ��������������
string strSpec[] = { "����'�����i �����", "I����������", "���������� �� ������i��", "�i���� �� i����������", "������� ��������" };

// ��������� ��� ��������� ���������� ��� ��������
struct Student {
    string lname;   // �������
    int kurs;       // ����
    Spec spec;      // ������������
    int physics;    // ������ � ������
    int math;       // ������ � ����������
    union {         // ��'������� ��� ������ ������ � ��������� �� ������������
        int programming;    // ������ � ������������� (��� CS)
        int numMethods;     // ������ � ��������� ������ (��� IT)
        int pedagogy;       // ������ � ��������� (��� ����� ��������������)
    };
};

// ������� ��� �������� ����� ��� ��������
void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "��i�����: ";
        cin >> s[i].lname;
        cout << "����: ";
        cin >> s[i].kurs;
        cout << "����i����i��� (0 - ����'�����i �����, 1 - I����������, 2 - ���������� �� ������i��, "
            << "3 - �i���� �� i����������, 4 - ������� ��������): ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "��i��� � �i����: ";
        cin >> s[i].physics;
        cout << "��i��� � ����������: ";
        cin >> s[i].math;

        // �������� ������ ������ ������� �� ������������
        if (s[i].spec == CS) {
            cout << "��i��� � �������������: ";
            cin >> s[i].programming;
        }
        else if (s[i].spec == IT) {
            cout << "��i��� � ��������� ������: ";
            cin >> s[i].numMethods;
        }
        else {
            cout << "��i��� � ���������: ";
            cin >> s[i].pedagogy;
        }
        cout << endl;
    }
}

// ������� ��� ��������� ����� ��� �������� � ���������� ������
void Print(Student* s, int amSt) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| � | ��i�����      | ���� | ����i����i���           | �i���� | �����. | ����. | ���.���. | �������. |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < amSt; i++) {
        cout << "| " << setw(2) << right << i + 1 << ""
            << " | " << setw(13) << left << s[i].lname
            << " | " << setw(4) << right << s[i].kurs
            << " | " << setw(22) << left << strSpec[s[i].spec]
            << " | " << setw(6) << right << s[i].physics
            << " | " << setw(6) << right << s[i].math
            << " | ";

        // ��������� ������ ������ � �������� �������
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

// ������� ��� ��������� ���������� ������ �������� �� ������������, ������� � ���������� �� ��������
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

// ������� ��� ���������� ���������� ������ ��������
int* indexSort(Student* s, const int N) {
    int* P = new int[N];  // ����� �������
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

// ������� ��� ��������� �������� ������������� ������ ��������
void PrintIndexSorted(Student* s, int* P, const int N) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| � | ��i�����      | ���� | ����i����i���           | �i���� | �����. | ����. | ���.���. | �������. |\n";
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

// ������� ��� �������� ������ �������� �� ��������, ������������ �� ������� � ������
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
    SetConsoleCP(1251);    // ��� ���������� �������� ���������� ������� � ������
    SetConsoleOutputCP(1251); // ��� ���������� ����������� ���������� ������� � ������

    int N; // ʳ������ ��������
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* s = new Student[N]; // ��������� ����� ��������

    Create(s, N);   // ������ ������� ��� ���������� ����� ��������
    cout << "\n��������� ������ ��������:\n";
    Print(s, N);    // ��������� �������� � ����������� �������

    Sort(s, N);     // Գ����� ���������� ������ ��������
    cout << "\n������ �������� ���� ��������� ����������:\n";
    Print(s, N);    // ��������� �������� ���� ��������� ����������

    int* indexArray = indexSort(s, N);   // �������� ����������
    cout << "\n������ �������� ���� ���������� ����������:\n";
    PrintIndexSorted(s, indexArray, N);  // ��������� �������� � ������� ���������� ����������

    string prizv;
    int kurs, avrGrade;
    cout << "������ �������: "; cin >> prizv;
    cout << "������ ����: "; cin >> kurs;
    cout << "������ ������� ������: "; cin >> avrGrade;

    int found = binSearch(s, N, prizv, kurs, avrGrade);

    if (found != -1)
        cout << "�������� �������� � ������� " << found + 1 << endl;
    else
        cout << "�������� �������� �� ��������" << endl;

    delete[] s;          // ��������� ���'��
    delete[] indexArray; // ��������� ���'�� ��� ���������� ������

    return 0;
}
