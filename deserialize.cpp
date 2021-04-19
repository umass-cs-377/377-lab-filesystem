#include <fstream>

#include "student.h"

void deserialize(std::istream& istream, Student& student){
    istream.read(reinterpret_cast<char*>(&student), sizeof(Student));
}

void print_student(const Student& student){
    std::cout << "Name:\t" << student.name << std::endl
              << "Gender:\t" << student.gender << std::endl
              << "Age:\t" << student.age << std::endl;
}

int main(){
    Student student1, student2;
    std::ifstream fin("file.bin", std::ios::binary);
    deserialize(fin, student1);
    deserialize(fin, student2);

    print_student(student1);
    print_student(student2);
    fin.close();
}
