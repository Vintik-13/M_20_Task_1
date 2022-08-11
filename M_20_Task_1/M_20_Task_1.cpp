/*Задание 1. Реализация записи в ведомость учёта

Что нужно сделать
В одном из прошлых заданий мы уже создавали программу чтения и анализа
ведомости выплат. Теперь требуется создать простую программу записи в
эту ведомость.
Формат ведомости прежний. Сначала идёт имя и фамилия получателя денежных
средств, далее располагается дата выдачи в формате ДД.ММ.ГГГГ. Завершает
запись сумма выплаты в рублях. Данные разделяются между собой пробелами.
В конце каждой записи должен быть расположен перевод строки.
При старте программы пользователь последовательно вводит данные для новой
записи, которые записываются затем в файл в текстовом режиме. Программа
должна добавлять новые записи в конец файла, не удаляя его текущее содержимое.*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

std::string inName(void) {

    std::string tmp;
    std::cout << "Input Name: ";    
    std::getline(std::cin, tmp);
    return tmp;
}

std::string inSurname(void) {

    std::string tmp;
    std::cout << "Input Surname: ";    
    std::getline(std::cin, tmp);
    return tmp;
}

bool validDate(const std::string& date) {      

    int count = 0;
    int date_len = date.length();
    for (int i = 0; i < date_len; i++) {

        bool a1 = date[i] >= '0';
        bool a2 = date[i] <= '9';
        if (std::isdigit(date[i]))
            count++;
    }
    if (date.substr(2, 1) != "." || date.substr(5, 1) != "." || count != 8)
        return false;
    else {

        int d = std::stoi(date.substr(0, 2));
        int m = std::stoi(date.substr(3, 2));
        int y = std::stoi(date.substr(6, 4));

        int days_in_month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

        if (y % 4 == 0)
            days_in_month[2] = 29;

        if ((m < 1) || (m > 12))
            return false;

        if ((d < 1) || (d > days_in_month[m]))
            return false;

        return true;
    }
}

bool validSalary(const std::string& salary) {

    bool tmp_b =  salary.find_first_not_of("0123456789-+.") == std::string::npos;
    
    if (tmp_b) {

        if (std::stod(salary) > 0)
            return true;
    }        
    else
        return false;
}

std::string inString(void) {

    std::string name = inName();
    std::string surname = inSurname();

    std::string date;
    std::cout << "Input Date: ";
    std::getline(std::cin, date);
    while (!validDate(date)) {
        std::cout << "Incorrect date!" << std::endl;
        std::getline(std::cin, date);
    }

    std::string salary;
    std::cout << "Input Salary: ";
    std::getline(std::cin, salary);
    while (!validSalary(salary)) {
        std::cout << "Incorrect salary!" << std::endl;
        std::getline(std::cin, salary);
    }

    return name + " " + surname + " " + salary + " " + date + "\n";
}

void puhsBackInFile(std::string str) {

    std::ofstream ofs("D:..\\Statement.txt", std::ios::app);

    bool aaa = ofs.is_open();

    if (!ofs.is_open()) {

        std::cout << "Incorrect file opening!";
        return;
    }
    else {

        ofs << str;
    }
    ofs.close();
}

int main()
{
    puhsBackInFile(inString());   
}

