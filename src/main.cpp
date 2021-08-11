#include <iostream>
#include <limits>
#include <string>
#include <math.h>
#include <numeric>
#include <cassert>

using namespace std;

enum Colour_e {
    FIRST_COLOUR = 0,
    NONE = FIRST_COLOUR,
    RED,
    BLUE,
    GREEN,
    LAST_COLOUR = GREEN
};

string GetStringFromStream(const string &message) {
    std::string str;
    while (true) {
        cout << message << endl;
        while (str.empty()) {
            getline(cin, str);
        }
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return str;
}

static double GetDoubleFromStream(const string &message, double min, double max) {
    double num;
    bool isCorrect = false;
    while (!isCorrect) {
        cout << message << ":";
        isCorrect = (!!(cin >> num)) && num >= min && num <= max;
        if (!isCorrect) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Please enter correct number" << endl;
        }
    }
    return num;
}

static void GetShapeParameters(double & inCenterX, double & inCenterY, Colour_e & inColour) {
    bool isCorrect;
    inCenterX = GetDoubleFromStream("Enter X center", -DBL_MAX, DBL_MAX);
    inCenterX = GetDoubleFromStream("Enter Y center", -DBL_MAX, DBL_MAX);

    do {
        isCorrect = true;
        string colour = GetStringFromStream("Enter colour (none|red|blue|green):");
        if (colour == "none") {
            inColour = NONE;
        } else if (colour == "red") {
            inColour = RED;
        } else if (colour == "blue") {
            inColour = BLUE;
        } else if (colour == "green") {
            inColour = GREEN;
        } else {
            cout << "Error. Incorrect colour" << endl;
            isCorrect = false;
        }
    } while (!isCorrect);
}

class Shape {
    double centerX;
    double centerY;
    Colour_e colour;
public:
    Shape(double inCenterX, double inCenterY, Colour_e inColour) :
            centerX(inCenterX),
            centerY(inCenterY),
            colour(inColour) {
        assert(inColour >= FIRST_COLOUR && inColour < LAST_COLOUR);
    }

    virtual double CalculateSquare() {
        return 0;
    }

    virtual void CalculateDepictedRectangle(double & outWidth, double & outHeight) {

    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double inCenterX, double inCenterY, Colour_e inColour, double inRadius)
            : Shape(inCenterX, inCenterY, inColour) {
        assert(inRadius > 0);
        radius = inRadius;
    }

    double CalculateSquare() final {
        return M_PI * radius * radius;
    }

    void CalculateDepictedRectangle(double & outWidth, double & outHeight) final {
        outWidth = radius + 0.1;
        outHeight = outWidth;
    }
};

class EquilateralTriangle : public Shape {
    double edge;
public:
    EquilateralTriangle(double inCenterX, double inCenterY, Colour_e inColour, double inEdge)
            : Shape(inCenterX, inCenterY, inColour) {
        assert(inEdge > 0);
        edge = inEdge;
    }

    double CalculateSquare() final {
        return edge * edge * sqrt(3) / 4.0;
    }

    void CalculateDepictedRectangle(double & outWidth, double & outHeight) final {
        outWidth = edge + 0.1;
        outHeight = outWidth;
    }
};

class Rectangle : public Shape {
    double width;
    double height;

public:
    Rectangle(double inCenterX, double inCenterY, Colour_e inColour, double inWidth, double inHeight)
            : Shape(inCenterX, inCenterY, inColour) {
        assert(inWidth > 0);
        assert(inHeight > 0);
        width = inWidth;
        height = inHeight;
    }

    double CalculateSquare() override {
        return width * height;
    }

    void CalculateDepictedRectangle(double & outWidth, double & outHeight) override {
        outWidth = width + 0.1;
        outHeight = height + 0.1;
    }
};

class Square : public Rectangle {
public:
    Square(double inCenterX, double inCenterY, Colour_e inColour, double inEdge)
            : Rectangle(inCenterX, inCenterY, inColour, inEdge, inEdge) {
    }
};

int main() {
    while (true) {
        Shape * shape;
        double centerX;
        double centerY;
        Colour_e colour;

        string cmd = GetStringFromStream("Enter command (circle|square|triangle|rectangle|exit)");
        if (cmd == "circle") {
            double radius;
            GetShapeParameters(centerX, centerY, colour);
            radius = GetDoubleFromStream("Enter radius", 0, DBL_MAX);
            shape = new Circle(centerX, centerY, colour, radius);
        } else if (cmd == "square") {
            double edge;
            GetShapeParameters(centerX, centerY, colour);
            edge = GetDoubleFromStream("Enter edge", 0, DBL_MAX);
            shape = new Square(centerX, centerY, colour, edge);
        } else if (cmd == "triangle") {
            double edge;
            GetShapeParameters(centerX, centerY, colour);
            edge = GetDoubleFromStream("Enter edge", 0, DBL_MAX);
            shape = new EquilateralTriangle(centerX, centerY, colour, edge);
        } else if (cmd == "rectangle") {
            double width, height;
            GetShapeParameters(centerX, centerY, colour);
            width = GetDoubleFromStream("Enter width", 0, DBL_MAX);
            height = GetDoubleFromStream("Enter height", 0, DBL_MAX);
            shape = new Rectangle(centerX, centerY, colour, width, height);
        } else if (cmd == "exit") {
            break;
        } else {
            cout << "Error. Incorrect command" << endl;
            continue;
        }

        cout << "The square of the shape is: " << shape->CalculateSquare() << endl;
        double width, height;
        shape->CalculateDepictedRectangle(width, height);
        cout << "The depicted rectangle is: Width = " << width << " Height = " << height << endl;

        delete shape;
    }

    return 0;
}
