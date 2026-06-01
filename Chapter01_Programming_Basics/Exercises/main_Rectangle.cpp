#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Define a Rectangle class that provides getLength and getWidth.UsingthefindMax
routines in Figure 1.25, write a main that creates an array of Rectangle and finds the
largest Rectangle first on the basis of area and then on the basis of perimeter.
*/

class Rectangle {
public:
    Rectangle(double l, double w) : length{ l }, width{ w } {}

    double getLength() const { return length; }
    double getWidth() const { return width; }

    // Helper funcs
    double getArea() const { return length * width; }
    double getPerimeter() const { return (length + width) * 2; }

    void printDetails() const {
        cout << "[Length: " << length << ", Width: " << width
            << " | Area: " << getArea()
            << ", Perimeter: " << getPerimeter() << "]";
    }

private:
    double width;
    double length;
};

template <typename Comparator>
const Rectangle& findMax(const vector<Rectangle>& arr, Comparator isLessThan) {
    int maxIndex = 0;

    for (size_t i = 0; i < arr.size(); i++)
    {
        if (isLessThan(arr[maxIndex], arr[i])) {
            maxIndex = i;
        }
    }
    return arr[maxIndex];
}

// Comparator Functors
class CompareByArea {
public:
    bool operator()(const Rectangle& lhs, const Rectangle& rhs) const {
        return lhs.getArea() < rhs.getArea();
    }
};

class CompareByPerimeter {
public:
    bool operator()(const Rectangle& lhs, const Rectangle& rhs) const {
        return lhs.getPerimeter() < rhs.getPerimeter();
    }
};

int main() {
    cout << "--- Solving the Rectangle findMax Exercise ---\n\n";

    // "write a main that creates an array of Rectangle..."
    vector<Rectangle> arr = {
        Rectangle(10.0, 2.0), // Area: 20, Perimeter: 24
        Rectangle(5.0, 5.0),  // Area: 25, Perimeter: 20
        Rectangle(4.0, 3.0)   // Area: 12, Perimeter: 14
    };

    // "...and finds the largest Rectangle first on the basis of area"
    cout << "1. Largest Rectangle on the basis of AREA:\n";
    const Rectangle& maxAreaRect = findMax(arr, CompareByArea{});
    maxAreaRect.printDetails();
    cout << "\n\n";

    // "...and then on the basis of perimeter."
    cout << "2. Largest Rectangle on the basis of PERIMETER:\n";
    const Rectangle& maxPerimeterRect = findMax(arr, CompareByPerimeter{});
    maxPerimeterRect.printDetails();
    cout << "\n";

    return 0;
}