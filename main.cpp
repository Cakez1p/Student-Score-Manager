#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>  // 添加algorithm头文件以使用std::sort
void deleteStudent(std::vector<Student>& students);
// 学生信息结构体
struct Student {
    int id;
    std::string name;
    double score;
};

// 函数声明
void displayMenu();
void loadData(std::vector<Student>& students);
void saveData(const std::vector<Student>& students);
void displayAllStudents(const std::vector<Student>& students);
void searchStudent(const std::vector<Student>& students);
void modifyScore(std::vector<Student>& students);
void sortStudents(std::vector<Student>& students);
void deleteStudent(std::vector<Student>& students);
void searchStudentByName(const std::vector<Student>& students);
// 主函数
int main() {
    std::vector<Student> students;
    loadData(students);
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        std::cout << "请输入您的选择: ";
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
                saveData(students);
                running = false;
                break;
            
            default:
                std::cout << "无效的选择，请重试！" << std::endl;
        }
    }
    
    return 0;
}

// 显示菜单
void displayMenu() {
    std::cout << "\n========== 学生成绩管理系统 ==========" << std::endl;
    std::cout << "1. 显示所有学生信息" << std::endl;
    std::cout << "2. 查询学生信息" << std::endl;
    std::cout << "3. 修改学生成绩" << std::endl;
    std::cout << "4. 排序学生信息" << std::endl;
    std::cout << "5. 删除学生信息" << std::endl;
    std::cout << "6. 按姓名查询学生信息" << std::endl;
    std::cout << "7. 退出系统" << std::endl;
    std::cout << "=====================================" << std::endl;
}

// 从文件加载数据
void loadData(std::vector<Student>& students) {
    std::ifstream inFile("students.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "无法打开文件或文件不存在，将创建新文件。" << std::endl;
        return;
    }
    
    Student temp;
    // 读取学生数量
    int count;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    for (int i = 0; i < count; i++) {
        // 读取学生ID
        inFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id));
        
        // 读取姓名长度
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        
        // 读取姓名
        char* name = new char[nameLength + 1];
        inFile.read(name, nameLength);
        name[nameLength] = '\0';
        temp.name = name;
        delete[] name;
        
        // 读取成绩
        inFile.read(reinterpret_cast<char*>(&temp.score), sizeof(temp.score));
        
        students.push_back(temp);
    }
    
    inFile.close();
}

// 保存数据到文件
void saveData(const std::vector<Student>& students) {
    std::ofstream outFile("students.dat", std::ios::binary);
    if (!outFile) {
        std::cout << "无法创建文件！" << std::endl;
        return;
    }
    
    // 写入学生数量
    int count = students.size();
    outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& student : students) {
        // 写入学生ID
        outFile.write(reinterpret_cast<const char*>(&student.id), sizeof(student.id));
        
        // 写入姓名长度
        int nameLength = student.name.length();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        
        // 写入姓名
        outFile.write(student.name.c_str(), nameLength);
        
        // 写入成绩
        outFile.write(reinterpret_cast<const char*>(&student.score), sizeof(student.score));
    }
    
    outFile.close();
    std::cout << "数据已成功保存！" << std::endl;
}

// 显示所有学生信息
void displayAllStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "没有学生记录！" << std::endl;
        return;
    }
    
    std::cout << "\n所有学生信息：" << std::endl;
    std::cout << std::left << std::setw(10) << "学号" 
              << std::setw(20) << "姓名" 
              << std::setw(10) << "成绩" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& student : students) {
        std::cout << std::left << std::setw(10) << student.id 
                  << std::setw(20) << student.name 
                  << std::setw(10) << student.score << std::endl;
    }
}

// 查询学生信息
void searchStudent(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "没有学生记录！" << std::endl;
        return;
    }
    
    int searchId;
    std::cout << "请输入要查询的学生学号: ";
    std::cin >> searchId;
    
    bool found = false;
    for (const auto& student : students) {
        if (student.id == searchId) {
            std::cout << "\n找到学生信息：" << std::endl;
            std::cout << "学号: " << student.id << std::endl;
            std::cout << "姓名: " << student.name << std::endl;
            std::cout << "成绩: " << student.score << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "未找到学号为 " << searchId << " 的学生！" << std::endl;
    }
}

// 修改学生成绩
void modifyScore(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "没有学生记录！" << std::endl;
        return;
    }
    
    int modifyId;
    std::cout << "请输入要修改成绩的学生学号: ";
    std::cin >> modifyId;
    
    bool found = false;
    for (auto& student : students) {
        if (student.id == modifyId) {
            std::cout << "学生：" << student.name << "，当前成绩：" << student.score << std::endl;
            std::cout << "请输入新的成绩: ";
            std::cin >> student.score;
            std::cout << "成绩修改成功！" << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "未找到学号为 " << modifyId << " 的学生！" << std::endl;
    }
}

// 排序学生信息
void sortStudents(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "没有学生记录！" << std::endl;
        return;
    }
    
    int sortType;
    std::cout << "请选择排序方式：" << std::endl;
    std::cout << "1. 按学号排序" << std::endl;
    std::cout << "2. 按成绩从高到低排序" << std::endl;
    std::cout << "3. 按成绩从低到高排序" << std::endl;
    std::cout << "请输入您的选择: ";
    std::cin >> sortType;
    
    switch (sortType) {
        case 1:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.id < b.id;
            });
            std::cout << "已按学号排序！" << std::endl;
            break;
        case 2:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.score > b.score;
            });
            std::cout << "已按成绩从高到低排序！" << std::endl;
            break;
        case 3:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.score < b.score;
            });
            std::cout << "已按成绩从低到高排序！" << std::endl;
            break;
        default:
            std::cout << "无效的选择！" << std::endl;
            return;
    }
    
    displayAllStudents(students);
}

// 删除学生信息
void deleteStudent(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "没有学生记录！" << std::endl;
        return;
    }

    int deleteId;
    std::cout << "请输入要删除的学生学号: ";
    std::cin >> deleteId;

    auto it = std::remove_if(students.begin(), students.end(), [deleteId](const Student& student) {
        return student.id == deleteId;
    });

    if (it != students.end()) {
        students.erase(it, students.end());
        std::cout << "学生信息已删除！" << std::endl;
        saveData(students); // 删除后保存数据
    } else {
        std::cout << "未找到学号为 " << deleteId << " 的学生！" << std::endl;
    }
}

// 按姓名查询学生信息
void searchStudentByName(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "没有学生记录！" << std::endl;
        return;
    }

    std::string searchName;
    std::cout << "请输入要查询的学生姓名: ";
    std::cin >> searchName;

    bool found = false;
    for (const auto& student : students) {
        if (student.name == searchName) {
            std::cout << "\n找到学生信息：" << std::endl;
            std::cout << "学号: " << student.id << std::endl;
            std::cout << "姓名: " << student.name << std::endl;
            std::cout << "成绩: " << student.score << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "未找到姓名为 " << searchName << " 的学生！" << std::endl;
    }
}
