// c++ refreshner - trying out stuff

#include <iostream>
#include <string>
#include <vector>


class workforce {
private:
    int num_employees;
    int total_salary;
public:
    workforce() {}
    ~workforce() {}
    void add_employee(int new_salary) {
        total_salary+=new_salary;
        ++num_employees;
    };
    int get_employee_count() {return num_employees;};
    int get_total_salary() {return total_salary;};
};

class employee {
private:
    int index;
    int salary;
    std::string my_name;
public:    
    employee(std::string name, int sal, workforce& wf) {
        my_name = name;
        salary = sal;
        wf.add_employee(salary);
    }
    ~employee();
    std::string get_name() {return my_name;};
};

employee* create_new_employee(workforce& wf, int& max_total, std::string 
name, int sal) { 
    if(wf.get_total_salary()+sal<=max_total){
        std::cout << "Creating new employee..." << std::endl;
        return new employee(name, sal, wf);
    }else{
        std::cout << "Max salary mass reached!" << std::endl;
        return new employee("ERROR NOT ENOUGH MONEY", 0, wf);
    }
}

int main() {
    int max_salary = 200000;
    workforce wf = workforce();
    employee* empl1 = create_new_employee(wf, max_salary, "J.B.", 100000);
    std::cout << empl1->get_name() << std::endl;
    employee* empl2 = create_new_employee(wf, max_salary, "J.B.", 
2000000);
    std::cout << empl2->get_name() << std::endl;
    return 0;
}   

