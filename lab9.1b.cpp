#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>  // ������������ ����������� ��������

using namespace std;

enum Spesialnist { KN, INF, ME, FI, TN };

string spesialnistStr[] = { "��������� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student {
    string prizv;
    int kurs;
    Spesialnist spesialnist;
    int mark_phys;
    int mark_math;
    union {
        int mark_prog;
        int mark_ch_meth;
        int mark_ped;
    };
};

struct Marks {
    int phys;
    int math;
    int prog;
    int ch_meth;
    int ped;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N, Marks& marks, double proc_55);
void Count_4(Student* p, const int N, Marks& marks);
double Proc_55(Student* p, const int N);

int main() {
    // ������������ ����������� ��������:
    SetConsoleCP(1251);       // ������������ ������� win-cp1251 � ���� �����
    SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

    int N;
    cout << "������ ������� ��������: ";
    cin >> N;
    Student* p = new Student[N];
    Marks marks = { 0, 0, 0, 0, 0 };

    Create(p, N);
    double proc_55 = Proc_55(p, N);
    Count_4(p, N, marks);
    Print(p, N, marks, proc_55);

    delete[] p;

    return 0;
}

void Create(Student* p, const int N) {
    int spes_number;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();  // ������� ����� ���������, �� ����������� �������
        cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
        cout << "    �������: ";
        getline(cin, p[i].prizv);
        cout << "    ����: ";
        cin >> p[i].kurs;
        cout << "   ������������: (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������,";
        cout << " 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> spes_number;
        p[i].spesialnist = (Spesialnist)spes_number;
        cout << "    ������ � ������: ";
        cin >> p[i].mark_phys;
        cout << "    ������ � ����������: ";
        cin >> p[i].mark_math;
        switch (p[i].spesialnist) {
            case KN:
                cout << "    ������ � �������������: ";
                cin >> p[i].mark_prog;
                break;
            case INF:
                cout << "    ������ � ��������� ������: ";
                cin >> p[i].mark_ch_meth;
                break;
            default:
                cout << "    ������ � ���������: ";
                cin >> p[i].mark_ped;
                break;
        }
        cout << endl;
    }
}

void Print(Student* p, const int N, Marks& marks, double proc_55) {
    cout << "============================================================================================================================" << endl;
    cout << "| � |   �������   |  ����  |      ������������      | Գ���� | ���������� | ������������� | ������� ������ | ��������� |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << i + 1 << " ";
        cout << "| " << setw(12) << left << p[i].prizv << " ";
        cout << "|    " << p[i].kurs << "   ";
        cout << "| " << setw(23) << left << spesialnistStr[p[i].spesialnist] << " ";
        cout << "| " << setw(6) << right << p[i].mark_phys << " ";
        cout << "| " << setw(10) << right << p[i].mark_math << " ";
        switch (p[i].spesialnist) {
        case KN:
            cout << "| " << setw(13) << right << p[i].mark_prog << " ";
            cout << "|                 ";
            cout << "|            ";
            break;
        case INF:
            cout << "|               ";
            cout << "| " << setw(15) << right << p[i].mark_ch_meth << " ";
            cout << "|            ";
            break;
        default:
            cout << "|               ";
            cout << "|                 ";
            cout << "| " << setw(10) << right << p[i].mark_ped << " ";
            break;
        }
        cout << "|" << endl;
    }
    cout << "============================================================================================================================" << endl;
    cout << endl;

    cout << "ʳ������ ������ ""�����"" � ������: " << marks.phys << endl;
    cout << "ʳ������ ������ ""�����"" � ����������: " << marks.math << endl;
    cout << "ʳ������ ������ ""�����"" � �������������: " << marks.prog << endl;
    cout << "ʳ������ ������ ""�����"" � ��������� ������: " << marks.ch_meth << endl;
    cout << "ʳ������ ������ ""�����"" � ���������: " << marks.ped << endl;

    cout << "������� ��������, �� �������� � � ������, � � ���������� ������ ""5"": " << proc_55 << "%" << endl;
}

void Count_4(Student* p, const int N, Marks& marks) {
    for (int i = 0; i < N; i++) {
        if (p[i].mark_phys == 4) marks.phys++;
        if (p[i].mark_math == 4) marks.math++;
        switch (p[i].spesialnist) {
        case KN:
            if (p[i].mark_prog == 4) marks.prog++;
            break;
        case INF:
            if (p[i].mark_ch_meth == 4) marks.ch_meth++;
            break;
        default:
            if (p[i].mark_ped == 4) marks.ped++;
            break;
        }
    }
}

double Proc_55(Student* p, const int N) {
    int count_55 = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].mark_phys == 5 && p[i].mark_math == 5) count_55++;
    }
    return 100.0 * count_55 / N;
}
