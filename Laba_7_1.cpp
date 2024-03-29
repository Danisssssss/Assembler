#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    float x1, x2, y1, x3, x4, y2, s, y3, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    if (x3 >= x2 || x4 <= x1)
        cout << 0;
    else {
        if (y1 >= y3) {
            if (x3 >= x1 && x4 <= x2) s = (x4 - x3) * y3;
            else if (x3 >= x1 && x4 >= x2) s = abs((x2 - x3)) * y3;
            else if (x3 <= x1 && x4 >= x2) s = abs((x2 - x1)) * y3;
            else if (x3 <= x1 && x4 <= x2) s = abs((x4 - x1)) * y3;
        }
        else {
            if (x3 >= x1 && x4 <= x2)
                s = abs((x4 - x3)) * y1;
            else if (x3 >= x1 && x4 >= x2)
                s = abs((x2 - x3)) * y1;
            else if (x3 <= x1 && x4 >= x2)
                s = abs((x2 - x1)) * y1;
            else if (x3 <= x1 && x4 <= x2)
                s = abs((x4 - x1)) * y1;
        }
        cout << fixed << setprecision(4) << s;
    }
    return 0;
}