#include <memory>
#include "classifiers.h"

using namespace std;

class CombinedClassifier {
public:
    CombinedClassifier(const string& fastClfData, const string& mainClfData) :
        fastClf(make_unique<FastClassifier>(fastClfData)), mainClfData(mainClfData) {}

    double classify(const string& s) {
        try {
            return fastClf->classify(s);
        } catch (const TooHardObjectException& exc) {
            return getMainClassifier(mainClfData)->classify(s);
        }
    }

    static MainClassifier* getMainClassifier(const std::string& data = "") {
        static MainClassifier mainClf(data);
        return &mainClf;
    }

private:
    unique_ptr<FastClassifier> fastClf;
    string mainClfData;
};

int main() {
    CombinedClassifier clf("fastClf", "mainClf");
    cout << clf.classify("42 hard 2021") << "\n";
    cout << clf.classify("24 hard 2020") << "\n";
    cout << clf.classify("24 easy 2020") << "\n";
    return 0;
}
