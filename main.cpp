#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>  // ???algorithm?????????std::sort

// ??????????
struct Student {
    int id;
    std::string name;
    double score;
};

// ????????
void displayMenu();
void loadData(std::vector<Student>& students);
void saveData(const std::vector<Student>& students);
void displayAllStudents(const std::vector<Student>& students);
void searchStudent(const std::vector<Student>& students);
void modifyScore(std::vector<Student>& students);
void sortStudents(std::vector<Student>& students);
void addStudent(std::vector<Student>& students);
void deleteStudent(std::vector<Student>& students);
void searchStudentByName(const std::vector<Student>& students);

// ??????
int main() {
    std::vector<Student> students;
    loadData(students);
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        std::cout << "?????????????: ";
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
                deleteStudent(students);
                break;
            case 6:
                searchStudentByName(students);
                break;
            case 7:
                addStudent(students);
                saveData(students);
                break;
            case 8:
                saveData(students);
                running = false;
                break;

            default:
                std::cout << "??Ч????????????" << std::endl;
        }
    }
    
    return 0;
}
//1141414141
// ??????
void displayMenu() {
    std::cout << "\n========== ???????????? ==========" << std::endl;
    std::cout << "1. ?????????????" << std::endl;
    std::cout << "2. ?????????" << std::endl;
    std::cout << "3. ?????????" << std::endl;
    std::cout << "4. ??????????" << std::endl;
    std::cout << "5. ?????????" << std::endl;
    std::cout << "6. ???????????????" << std::endl;
    std::cout << "7. ???????????" << std::endl;
    std::cout << "8. ?????" << std::endl;
    std::cout << "=====================================" << std::endl;
}

// ?????????????
void loadData(std::vector<Student>& students) {
    std::ifstream inFile("students.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "?????????????????????????????????" << std::endl;
        return;
    }
    
    Student temp;
    // ??????????
    int count;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    for (int i = 0; i < count; i++) {
        // ??????ID
        inFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id));
        
        // ???????????
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        
        // ???????
        char* name = new char[nameLength + 1];
        inFile.read(name, nameLength);
        name[nameLength] = '\0';
        temp.name = name;
        delete[] name;
        
        // ??????
        inFile.read(reinterpret_cast<char*>(&temp.score), sizeof(temp.score));
        
        students.push_back(temp);
    }
    
    inFile.close();
}

// ????????????
void saveData(const std::vector<Student>& students) {
    std::ofstream outFile("students.dat", std::ios::binary);
    if (!outFile) {
        std::cout << "????????????" << std::endl;
        return;
    }
    
    // д?????????
    int count = students.size();
    outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& student : students) {
        // д?????ID
        outFile.write(reinterpret_cast<const char*>(&student.id), sizeof(student.id));
        
        // д??????????
        int nameLength = student.name.length();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        
        // д??????
        outFile.write(student.name.c_str(), nameLength);
        
        // д????
        outFile.write(reinterpret_cast<const char*>(&student.score), sizeof(student.score));
    }
    
    outFile.close();
    std::cout << "???????????棡" << std::endl;
}

// ?????????????
void displayAllStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "???????????" << std::endl;
        return;
    }
    
    std::cout << "\n????????????" << std::endl;
    std::cout << std::left << std::setw(10) << "???" 
              << std::setw(20) << "????" 
              << std::setw(10) << "???" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& student : students) {
        std::cout << std::left << std::setw(10) << student.id 
                  << std::setw(20) << student.name 
                  << std::setw(10) << student.score << std::endl;
    }
}

// ?????????
void searchStudent(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "???????????" << std::endl;
        return;
    }
    
    int searchId;
    std::cout << "??????????????????: ";
    std::cin >> searchId;
    
    bool found = false;
    for (const auto& student : students) {
        if (student.id == searchId) {
            std::cout << "\n???????????" << std::endl;
            std::cout << "???: " << student.id << std::endl;
            std::cout << "????: " << student.name << std::endl;
            std::cout << "???: " << student.score << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "δ??????? " << searchId << " ???????" << std::endl;
    }
}

void addStudent(std::vector<Student>& students) {
    Student newStudent;
    std::cout << "????????????????: ";
    std::cin >> newStudent.id;

    // ????????????
    for (const auto& student : students) {
        if (student.id == newStudent.id) {
            std::cout << "??????????????????" << std::endl;
            return;
        }
    }

    std::cout << "?????????????????: ";
    std::cin.ignore(); // ????????????????з?
    std::getline(std::cin, newStudent.name);

    std::cout << "???????????????: ";
    std::cin >> newStudent.score;

    students.push_back(newStudent);
    std::cout << "?????????????????" << std::endl;
}

// ?????????
void modifyScore(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "???????????" << std::endl;
        return;
    }
    
    int modifyId;
    std::cout << "????????????????????: ";
    std::cin >> modifyId;
    
    bool found = false;
    for (auto& student : students) {
        if (student.id == modifyId) {
            std::cout << "?????" << student.name << "??????????" << student.score << std::endl;
            std::cout << "???????????: ";
            std::cin >> student.score;
            std::cout << "??????????" << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "δ??????? " << modifyId << " ???????" << std::endl;
    }
}

// ??????????
void sortStudents(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "???????????" << std::endl;
        return;
    }
    
    int sortType;
    std::cout << "????????????" << std::endl;
    std::cout << "1. ?????????" << std::endl;
    std::cout << "2. ???????????????" << std::endl;
    std::cout << "3. ???????????????" << std::endl;
    std::cout << "?????????????: ";
    std::cin >> sortType;
    
    switch (sortType) {
        case 1:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.id < b.id;
            });
            std::cout << "??????????" << std::endl;
            break;
        case 2:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.score > b.score;
            });
            std::cout << "????????????????" << std::endl;
            break;
        case 3:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.score < b.score;
            });
            std::cout << "????????????????" << std::endl;
            break;
        default:
            std::cout << "??Ч?????" << std::endl;
            return;
    }
    
    displayAllStudents(students);
}

// ?????????
void deleteStudent(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "???????????" << std::endl;
        return;
    }

    int deleteId;
    std::cout << "??????????????????: ";
    std::cin >> deleteId;

    auto it = std::remove_if(students.begin(), students.end(), [deleteId](const Student& student) {
        return student.id == deleteId;
    });

    if (it != students.end()) {
        students.erase(it, students.end());
        std::cout << "?????????????" << std::endl;
        saveData(students); // ??????????
    } else {
        std::cout << "δ??????? " << deleteId << " ???????" << std::endl;
    }
}

// ???????????????
void searchStudentByName(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "???????????" << std::endl;
        return;
    }

    std::string searchName;
    std::cout << "???????????????????: ";
    std::cin >> searchName;

    bool found = false;
    for (const auto& student : students) {
        if (student.name == searchName) {
            std::cout << "\n???????????" << std::endl;
            std::cout << "???: " << student.id << std::endl;
            std::cout << "????: " << student.name << std::endl;
            std::cout << "???: " << student.score << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "δ???????? " << searchName << " ???????" << std::endl;
    }
}
