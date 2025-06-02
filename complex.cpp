#include <stdio.h>
#include <stdexcept>

class complex {
    double real; // Real part of the complex number
    double image; // Imaginary part of the complex number

    public:
        complex(double r = 0.0, double i = 0.0) : real(r), image(i) {} // Constructor to initialize complex number
        complex(const complex &c) : real(c.real), image(c.image) {} // Copy constructor
        ~complex() {} // Destructor

        double re() const { return real; } // Returns the real part
        double im() const { return image; } // Returns the imaginary part

        const complex &operator=(const complex &c) {
            real = c.real;
            image = c.image;
            return *this;
        } // Assignment operator

        const complex &operator+=(const complex &c) {
            real += c.real;
            image += c.image;
            return *this;
        } // Addition assignment operator

        const complex &operator-=(const complex &c) {
            real -= c.real;
            image -= c.image;
            return *this;
        } // Subtraction assignment operator

        const complex &operator*=(const complex &c) {
            double r = real * c.real - image * c.image; // Real part of the product
            double i = real * c.image + image * c.real; // Imaginary part of the product
            real = r;
            image = i;
            return *this;
        } // Multiplication assignment operator

        const complex &operator/=(double d) {
            if (d == 0) {
                throw std::runtime_error("Division by zero"); // Handle division by zero
            }
            real /= d; // Divide real part
            image /= d; // Divide imaginary part
            return *this;
        } // Division assignment operator

        friend complex operator!(const complex &c) {
            return complex(c.real, -c.image); // Returns the conjugate of the complex number
        } // Conjugate operator

        friend double abs2(const complex &c) {
            return c.re() * c.re() + c.im() * c.im(); // Returns the squared magnitude of the complex number
        } // Squared magnitude function

        const complex &operator/=(const complex &c) {
            return *this *= !c /= abs2(c); // Division by a complex number using conjugate and squared magnitude
        } // Division assignment operator for complex numbers

        const complex operator-(const complex &c) {
            return complex(-c.re(), -c.im()); // Returns the negation of a complex number
        } // Negation operator

        friend const complex operator-(const complex &c, const complex &d) {
            return complex(c.re() - d.re(), c.im() - d.im()); // Returns the difference of two complex numbers
        }

        friend const complex operator+(const complex &c, const complex &d) {
            return complex(c.re() + d.re(), c.im() + d.im()); // Returns the sum of two complex numbers
        } // Addition operator

        friend const complex operator*(const complex &c, const complex &d) {
            return complex(c.re() * d.re() - c.im() * d.im(), c.re() * d.im() + c.im() * d.re()); // Returns the product of two complex numbers
        } // Multiplication operator

        friend const complex operator/(const complex &c, const complex &d) {
            return complex(c) /= d; // Returns the division of a complex number by another complex number
        } // Division operator
};

void print(const complex &c) {
    printf("(%f, %f)\n", c.re(), c.im()); // Prints the complex number in the format (real, imaginary)
}

int main(){ 
    complex c=1., d(3.,4.); 
    print(c-d); 
    print(c+d);
    print(c*d);
    print(c/d); 
    return 0;
}
