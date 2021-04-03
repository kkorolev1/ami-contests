#include <map>
#include <string>

struct StudentResults {
    std::string login;
    std::string group;
    std::map<std::string, int> scores;  // номер задачи -> баллы

    // ...

    StudentResults(const std::string& l, const std::string& gr): login(l), group(gr) {
    }

    StudentResults(const StudentResults&) = delete;
    StudentResults& operator=(const StudentResults&) = delete;
};

#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

class Monitor {
private:
    // удобные псевдонимы типов для краткости:
    using Ptr = std::shared_ptr<StudentResults>;
    using ConstPtr = std::shared_ptr<const StudentResults>;

    std::map<std::string, Ptr> by_student;
    std::map<std::string, std::vector<ConstPtr>> by_group;
    std::vector<ConstPtr> all_results;

public:
    Monitor() = default;
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    Ptr RegisterStudent(const std::string& login, const std::string& group) {
        if (by_student.find(login) != by_student.end()) {
            throw std::invalid_argument("Student is already registered");
        }
        // Добавить новую запись о студенте и вернуть ее
        auto results = std::make_shared<StudentResults>(login, group);
        by_student.emplace(login, results);
        by_group[group].push_back(results);
        all_results.push_back(results);
        return results;
    }

    Ptr GetStudentResults(const std::string& login) {
        return by_student.at(login);
    }

    ConstPtr GetStudentResults(const std::string& login) const {
        return by_student.at(login);
    }

    std::vector<ConstPtr> GetGroupResults(const std::string& group) const {
        return by_group.at(group);
    }

    std::vector<ConstPtr> GetAllResults() const {
        return all_results;
    }
};

#include <iostream>

int main() {
    Monitor monitor;

    {
        auto ptr = monitor.RegisterStudent("Ivanov Ivan", "201-1");
        ptr->scores["A"] = 10;
        ptr->scores["B"] = 8;
    }

    {
        auto ptr = monitor.RegisterStudent("Petrov Petr", "201-2");
        ptr->scores["A"] = 5;
        ptr->scores["C"] = 10;
    }

    auto ptr = monitor.GetStudentResults("Ivanov Ivan");
    ptr->scores["Z"] = 100;

    // тут может быть аналогичный вызов monitor.GetGroupResults(group)
    for (const auto& result : monitor.GetAllResults()) {
        std::cout << result->login << "\t" << result->group << "\t";
        for (const auto& [problemId, score] : result->scores) {
            std::cout << problemId << ": " << score << "\t";
        }
        std::cout << "\n";
    }
}
