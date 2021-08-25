DO NOT USE THIS.  DEPRECATED

# COMPSCI 377 LAB #7: Serialization/Deserialization

## Purpose

This lab is designed to provide a basic idea about how serialization/deserialization is done. Please
make sure that all of your answers to questions in these labs come from work done on the Edlab
environment – otherwise, they may be inconsistent results and will not receive points.

Please submit your answers to this lab on Gradescope in the assignment marked Lab #7. All answers
are due by the time specified on Gradescope. The TA present in your lab will do a brief explanation
of the various parts of this lab, but you are expected to answer all questions by yourself. Please
raise your hand if you have any questions during the lab section – TAs will be notified you are
asking a question. Questions and Parts have a number of points marked next to them to signify their
weight in this lab’s final grade. Labs are weighted equally, regardless of their total points.

## Overview

Serialization and deserialization is very common in computer science. It's used in various cases,
for instance, persisting information in memory to a file, or sending information over the network in
a REST API request or RPC call. In this lab we serialize a very simple `Student` struct to a file.
As you will see later in the quiz, it is a very naive implementation and has many flaws.

## Serialize

The `Student` struct that we are trying to serialize is defined in `student.h`:

```c++
struct Student {
    char name[32];
    uint age;
    char gender;
};
```

In `serialize.cpp` we create the information for two students and write their information to a
binary file named `file.bin`.

```c++
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
```

Notice the `serialize` function, basically what we are doing here is:
1. Take the pointer to `student` and convert it to a `const char` pointer.
2. Write the memory space that contains the student information to file as a `char` array (oy byte
   array), the length of the array is determined by `sizeof(Student)`.

## Deserialize
Similarly in `deserialize.cpp`, we can restore the student information from the binary file. We
first create two empty `Student` structs. Then we read `sizeof(Student)` bytes at a time and copy
those bytes to the memory space of the `Student` structs. The information printed out should match
what we defined in `serialize.cpp`.

```c++
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
```
