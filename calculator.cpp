// To run this code, you need to download the std_lib_facilities.h file
// from https://www.stroustrup.com/Programming/std_lib_facilities.h
// The calculator is an exercise from "Programming: Principles and Practice Using C++" by Bjarne Stroustrup.
// This code implements a simple calculator that can handle basic arithmetic operations, parentheses, and factorials

#include "std_lib_facilities.h"

const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a resul

class Token{
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};


class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};


// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}


// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}


Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case print:    // for "print"
    case quit:    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
    case '{': case '}': case '!':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token(number, val);
    }
    default:
        error("Bad token");
        return Token(0);
    }
}

Token_stream ts;        // provides get() and putback() 

double expression();    // declaration so that primary() can call expression()

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
            return d;
    }
    case '{':    // handle '{' expression '}'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') error("'}' expected");
            return d;
    }
    case number:            // we use '8' to represent a number
        return t.value;  // return the number's value
    case '-':            // handle unary minus
        return -primary(); // return the negation of the primary
    case '+':            // handle unary plus
        return primary();  // return the primary as is
    default:
        error("primary expected");
        return 0;
    }
}


int calc_factorial(int n) {
    if (n < 0) error("Factorial of a negative number is undefined");
    if (n == 0 || n == 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

double factorial()
{
    double val = primary();
    Token t = ts.get();
    while (t.kind == '!') {
        int ival = int(val);
        if (val != ival) error("Factorial of a non-integer is undefined");
        val = calc_factorial(ival);
        t = ts.get();
    }
    ts.putback(t);
    return val;
}

// deal with *, /, and %
double term()
{
    double left = factorial();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= factorial();
            t = ts.get();
            break;
        case '/':
        {
            double d = factorial();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = factorial();
            if (d == 0) error("divide by zero");
            left = fmod(left, d); // use fmod for modulus operation
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

void calculate() {
    while (cin) {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get(); // eat 'print'
        if (t.kind == quit) { // 'x' for "exit"
            return;
        }
        ts.putback(t);
        cout << result << expression() << '\n';
    }
}

int main()
try
{
    cout << "Welcome to our simple calculator.\n"
         << "Please enter expressions using floating-point numbers.\n"
         << "Operators: +, -, *, /, and parentheses ().\n"
         << "Type 'x' to exit.\n";
    calculate();
    keep_window_open();
    return 0;
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open("~~");
    return 2;
}
