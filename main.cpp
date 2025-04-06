#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>  // ���algorithmͷ�ļ���ʹ��std::sort

// ѧ����Ϣ�ṹ��
struct Student {
    int id;
    std::string name;
    double score;
};

// ��������
void displayMenu();
void loadData(std::vector<Student>& students);
void saveData(const std::vector<Student>& students);
void displayAllStudents(const std::vector<Student>& students);
void searchStudent(const std::vector<Student>& students);
void modifyScore(std::vector<Student>& students);
void sortStudents(std::vector<Student>& students);
void addStudent(std::vector<Student>& students);


// ������
int main() {
    std::vector<Student> students;
    loadData(students);
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        std::cout << "����������ѡ��: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                displayAllStudents(students);
                break;
            case 2:
                searchStudent(students);
                break;
            case 3:
                modifyScore(students);
                saveData(students);
                break;
            case 4:
                sortStudents(students);
                break;
            case 5:
                saveData(students);
                running = false;
                break;
            case 6:
                addStudent(students);
                saveData(students);
                break;
            default:
                std::cout << "��Ч��ѡ�������ԣ�" << std::endl;
        }
    }
    
    return 0;
}

// ��ʾ�˵�
void displayMenu() {
    std::cout << "\n========== ѧ���ɼ�����ϵͳ ==========" << std::endl;
    std::cout << "1. ��ʾ����ѧ����Ϣ" << std::endl;
    std::cout << "2. ��ѯѧ����Ϣ" << std::endl;
    std::cout << "3. �޸�ѧ���ɼ�" << std::endl;
    std::cout << "4. ����ѧ����Ϣ" << std::endl;
    std::cout << "5. �˳�ϵͳ" << std::endl;
    std::cout << "6. ¼����ѧ���ɼ�" << std::endl;
    std::cout << "=====================================" << std::endl;
}

// ���ļ���������
void loadData(std::vector<Student>& students) {
    std::ifstream inFile("students.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "�޷����ļ����ļ������ڣ����������ļ���" << std::endl;
        return;
    }
    
    Student temp;
    // ��ȡѧ������
    int count;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    for (int i = 0; i < count; i++) {
        // ��ȡѧ��ID
        inFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id));
        
        // ��ȡ��������
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        
        // ��ȡ����
        char* name = new char[nameLength + 1];
        inFile.read(name, nameLength);
        name[nameLength] = '\0';
        temp.name = name;
        delete[] name;
        
        // ��ȡ�ɼ�
        inFile.read(reinterpret_cast<char*>(&temp.score), sizeof(temp.score));
        
        students.push_back(temp);
    }
    
    inFile.close();
}

// �������ݵ��ļ�
void saveData(const std::vector<Student>& students) {
    std::ofstream outFile("students.dat", std::ios::binary);
    if (!outFile) {
        std::cout << "�޷������ļ���" << std::endl;
        return;
    }
    
    // д��ѧ������
    int count = students.size();
    outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& student : students) {
        // д��ѧ��ID
        outFile.write(reinterpret_cast<const char*>(&student.id), sizeof(student.id));
        
        // д����������
        int nameLength = student.name.length();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        
        // д������
        outFile.write(student.name.c_str(), nameLength);
        
        // д��ɼ�
        outFile.write(reinterpret_cast<const char*>(&student.score), sizeof(student.score));
    }
    
    outFile.close();
    std::cout << "�����ѳɹ����棡" << std::endl;
}

// ��ʾ����ѧ����Ϣ
void displayAllStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "û��ѧ����¼��" << std::endl;
        return;
    }
    
    std::cout << "\n����ѧ����Ϣ��" << std::endl;
    std::cout << std::left << std::setw(10) << "ѧ��" 
              << std::setw(20) << "����" 
              << std::setw(10) << "�ɼ�" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& student : students) {
        std::cout << std::left << std::setw(10) << student.id 
                  << std::setw(20) << student.name 
                  << std::setw(10) << student.score << std::endl;
    }
}

// ��ѯѧ����Ϣ
void searchStudent(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "û��ѧ����¼��" << std::endl;
        return;
    }
    
    int searchId;
    std::cout << "������Ҫ��ѯ��ѧ��ѧ��: ";
    std::cin >> searchId;
    
    bool found = false;
    for (const auto& student : students) {
        if (student.id == searchId) {
            std::cout << "\n�ҵ�ѧ����Ϣ��" << std::endl;
            std::cout << "ѧ��: " << student.id << std::endl;
            std::cout << "����: " << student.name << std::endl;
            std::cout << "�ɼ�: " << student.score << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "δ�ҵ�ѧ��Ϊ " << searchId << " ��ѧ����" << std::endl;
    }
}

void addStudent(std::vector<Student>& students) {
    Student newStudent;
    std::cout << "��������ѧ����ѧ��: ";
    std::cin >> newStudent.id;

    // ���ѧ���Ƿ��ظ�
    for (const auto& student : students) {
        if (student.id == newStudent.id) {
            std::cout << "��ѧ���Ѵ��ڣ��޷���ӣ�" << std::endl;
            return;
        }
    }

    std::cout << "��������ѧ��������: ";
    std::cin.ignore(); // �����һ�������Ļ��з�
    std::getline(std::cin, newStudent.name);

    std::cout << "��������ѧ���ĳɼ�: ";
    std::cin >> newStudent.score;

    students.push_back(newStudent);
    std::cout << "��ѧ����Ϣ����ӳɹ���" << std::endl;
}

// �޸�ѧ���ɼ�
void modifyScore(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "û��ѧ����¼��" << std::endl;
        return;
    }
    
    int modifyId;
    std::cout << "������Ҫ�޸ĳɼ���ѧ��ѧ��: ";
    std::cin >> modifyId;
    
    bool found = false;
    for (auto& student : students) {
        if (student.id == modifyId) {
            std::cout << "ѧ����" << student.name << "����ǰ�ɼ���" << student.score << std::endl;
            std::cout << "�������µĳɼ�: ";
            std::cin >> student.score;
            std::cout << "�ɼ��޸ĳɹ���" << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "δ�ҵ�ѧ��Ϊ " << modifyId << " ��ѧ����" << std::endl;
    }
}

// ����ѧ����Ϣ
void sortStudents(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "û��ѧ����¼��" << std::endl;
        return;
    }


    int sortType;
    std::cout << "��ѡ������ʽ��" << std::endl;
    std::cout << "1. ��ѧ������" << std::endl;
    std::cout << "2. ���ɼ��Ӹߵ�������" << std::endl;
    std::cout << "3. ���ɼ��ӵ͵�������" << std::endl;
    std::cout << "����������ѡ��: ";
    std::cin >> sortType;
    
    switch (sortType) {
        case 1:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.id < b.id;
            });
            std::cout << "�Ѱ�ѧ������" << std::endl;
            break;
        case 2:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.score > b.score;
            });
            std::cout << "�Ѱ��ɼ��Ӹߵ�������" << std::endl;
            break;
        case 3:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.score < b.score;
            });
            std::cout << "�Ѱ��ɼ��ӵ͵�������" << std::endl;
            break;
        default:
            std::cout << "��Ч��ѡ��" << std::endl;
            return;
    }
    
    displayAllStudents(students);
}
