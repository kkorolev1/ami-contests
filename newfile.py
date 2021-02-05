import sys
import os

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("usage: python newfile.py FILE")
        exit(0)
    file = sys.argv[1]
    content = """#include <iostream>

using namespace std;

int main() {
    return 0;
}
    """

    with open(file + ".cpp", "w") as f:
        f.write(content)

    content = """
add_executable({0} {0}.cpp)""".format(file)

    with open("CMakeLists.txt", "a") as f:
        f.write(content)

