//
// Created by zhangqianyi on 2017/7/7.
//

#ifndef DESIGNPATTERN_MVC_H
#define DESIGNPATTERN_MVC_H

#include <iostream>
using namespace std;

class Student {
public:
    string GetRollNo() { return m_rollNo; }
    void SetRollNo(string rollNo) { m_rollNo = rollNo; }
    string GetName() { return m_name; }
    void SetName(string name) { m_name = name; }

private:
    string m_rollNo;
    string m_name;
};

class StudentView {
public:
    void PrintInfo(string name, string rollNo) {
        cout << "Name: " << name << ", RollNo: " << rollNo << endl;
    }

    virtual void PrintName(string name) = 0;
    virtual void PrintRollNo(string rollNo) = 0;
};

class StudentController {
public:
    StudentController(Student student, StudentView studentView) : m_student(student), m_studentView(studentView) {}

    string GetStudentRollNo() { return m_student.GetRollNo(); }
    void SetStudentRollNo(string rollNo) { m_student.SetRollNo(rollNo); }
    string GetStudentName() { return m_student.GetName(); }
    void SetStudentName(string name) { m_student.SetName(name); }

    void UpdateView() { m_studentView.PrintInfo(m_student.GetName(), m_student.GetRollNo()); }

private:
    Student m_student;
    StudentView m_studentView;
};


#endif //DESIGNPATTERN_MVC_H
