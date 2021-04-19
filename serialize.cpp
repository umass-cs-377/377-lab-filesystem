#include <fstream>

#include "student.h"

void serialize(std::ostream& ostream, const Student& student) {
    ostream.write(reinterpret_cast<const char*>(&student), sizeof(Student));
}

int main() {
    Student student1 = {"Jane Doe", 22, 'F'};
    Student student2 = {"Richard Roe", 21, 'M'};
    std::ofstream fout("file.bin", std::ios::binary);
    serialize(fout, student1);
    serialize(fout, student2);
    fout.close();
}
