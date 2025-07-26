/*
    Simple calculator
    
    Revision history:
        Revised by Albert Queraltó July 2025
        Revised by Bjarne Stroustrup November 2013
        Revised by Bjarne Stroustrup May 2007
        Revised by Bjarne Stroustrup August 2006
        Revised by Bjarne Stroustrup August 2004
        Originally written by Bjarne Stroustrup
                    (bs@cs.tamu.edu) Spring 2004.
    
    This code implements a simple calculator that can handle basic arithmetic 
    operations, parentheses, and factorials.
    To run this code, you need to download the std_lib_facilities.h file
    from https://www.stroustrup.com/Programming/std_lib_facilities.h
    The calculator is an exercise from "Programming: Principles and Practice 
    Using C++" by Bjarne Stroustrup.

    
    Input from cin; output to cout.
    The grammar for input is:
    
    Statement:
        Expression
        Print
        Quit
    Print:
        ;
    Quit:
        q
    Expression:
        Term
        Expression + Term
        Expression – Term
    Term:
        Factorial
        Term * Factorial
        Term / Factorial
        Term % Factorial
    Factorial:
        Power
        Factorial!  // factorial operator
    Power:
        Primary
        pow ( Expression, Integer )
    Primary:
        Number
        ( Expression )
        { Expression }
        sqrt( Expression )
        – Primary
        + Primary
    Number:
        floating-point-literal
    
    Input comes from cin through the Token_stream called ts.
*/

#include "std_lib_facilities.h"

const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
const char name   = 'a';    // t.kind==name means that t is a name Token
const char let = 'L';    // t.kind==let means that t is a let Token
const char sqrtfunc = 'S';   // t.kind==sqrt means that t is a sqrt Token
const char powfunc = 'P';   // t.kind==pow means that t is a pow Token
const string declkey = "let"; // declaration keyword
const string sqrtkey = "sqrt"; // square root keyword
const string powkey = "pow"; // power keyword
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

struct Token {
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    string name;      // for names: a name
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
    Token(char ch, string n)       // make a Token from a char and a name
        :kind(ch), name(n) { }
};


class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c);      // ignore tokens until we find a print
    void unget(Token t) { buffer = t; full = true; }
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
    case '(': 
    case ')': 
    case '+': 
    case '-': 
    case '*': 
    case '/':
    case '{': 
    case '}': 
    case '!':
    case '%':
    case '=': // for '=' in variable assignment
    case ',': // for ',' in pow function
        return Token(ch);        // let each character represent itself
    case '.':   // a floating-point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': // numeric literals
    {
        cin.unget();         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token(number, val);
    }
    default:
        if (isalpha(ch)) {
            string s;
            s += ch;             // we have found a letter: start a name
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) {
                s += ch;         // add to the name
            }
            cin.unget();
            if (s == sqrtkey) return Token(sqrtfunc); // sqrt keyword
            if (s == powkey) return Token(powfunc); // pow keyword
            if (s == declkey) return Token(let); // let keyword
            return Token(name, s);
        }
        error("Bad token");
        return Token(0);
    }
}

void Token_stream::ignore(char c)
{
    // first look in the buffer:
    if (full && buffer.kind == c) {
        full = false;  // we found the token we were looking for
        return;
    }
    full = false;      // no Token in buffer
    // now search the input:
    char ch;
    while (cin >> ch) {
        if (ch == c) return;  // found the token we were looking for
    }
}

Token_stream ts;        // provides get() and putback() 


struct Variable {
    string name;
    double value;
    Variable(string n, double v) : name(n), value(v) {}
};

class Symbol_table {
    public:
        double get_value(string s);
        void set_value(string s, double d);
        bool is_declared(string var);
        double define_name(string var, double val);
    private:
        vector<Variable> var_table; // holds variables
};

double Symbol_table::get_value(string s)
// return the value of the Variable names s
{
    for (const Variable& v : var_table) {
        if (v.name == s) return v.value;
    }
    error("Variable not found");
    return 0; // unreachable, but avoids compiler warning
}

void Symbol_table::set_value(string s, double d)
// set the Variable named s to d
{
    for (Variable& v : var_table) {
        if (v.name == s) {
            v.value = d;
            return;
        }
    }
    error("Variable not found");
}

bool Symbol_table::is_declared(string var)
// check if a variable is already declared
{
    for (const Variable& v : var_table) {
        if (v.name == var) return true;
    }
    return false;
}

double Symbol_table::define_name(string var, double val)
// define a new variable named var with value val
{
    if (is_declared(var)) error(var, " declared twice");
    var_table.push_back(Variable(var, val));
    return val;
}

Symbol_table sym_table; // global symbol table

double expression(Token_stream& ts);    // declaration so that primary() can call expression()
double primary(Token_stream& ts);

// Add pow() support in power()
double power(Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind == powfunc) {
        t = ts.get();
        if (t.kind != '(') error("'(' expected after 'pow'");
        double base = expression(ts);
        t = ts.get();
        if (t.kind != ',') error("',' expected after base in 'pow'");
        double exponent = expression(ts);
        t = ts.get();
        if (t.kind != ')') error("')' expected after exponent in 'pow'");
        int iexponent = int(exponent);
        if (exponent != iexponent) error("Exponent must be an integer");
        return pow(base, exponent);
    } else {
        ts.putback(t); // put back the token if it's not a pow function
        return primary(ts); // just return the primary value
    }
}

int calc_factorial(int n) {
    if (n < 0) error("Factorial of a negative number is undefined");
    if (n == 0 || n == 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

double factorial(Token_stream& ts)
{
    double val = power(ts);
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

// deal with numbers and parentheses
double primary(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')') error("')' expected");
            return d;
    }
    case '{':    // handle '{' expression '}'
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != '}') error("'}' expected");
            return d;
    }
    case sqrtfunc: // handle sqrt( expression )
    {
        t = ts.get(); // get the next token
        if (t.kind != '(') error("'(' expected after 'sqrt'");
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')') error("')' expected after expression in sqrt");
        if (d < 0) error("Square root of negative number is undefined");
        return sqrt(d); // return the square root of d
    }
    case number:            // we use '8' to represent a number
        return t.value;  // return the number's value
    case name:             // handle variable names
        return sym_table.get_value(t.name);
    case '-':            // handle unary minus
        return -primary(ts); // return the negation of the primary
    case '+':            // handle unary plus
        return primary(ts);  // return the primary as is
    default:
        error("primary expected");
        return 0;
    }
}

// deal with *, /, and %
double term(Token_stream& ts)
{
    double left = factorial(ts);
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= factorial(ts);
            t = ts.get();
            break;
        case '/':
        {
            double d = factorial(ts);
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = factorial(ts);
            if (d == 0) error("divide by zero");
            left = fmod(left, d); // use fmod for modulus operation
            t = ts.get();
            break;
        }
        default:
            ts.unget(t);     // put t back into the token stream
            return left;
        }
    }
}

// deal with + and -
double expression(Token_stream& ts)
{
    double left = term(ts);      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term(ts);    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term(ts);    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.unget(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double declaration(Token_stream& ts)
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
{
    Token t = ts.get();
    if (t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') error("'=' expected in declaration");
    double d = expression(ts);
    sym_table.define_name(var_name, d);
    return d;
}

double statement(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration(ts);
        default:
            ts.unget(t);
            return expression(ts);
    }
}


void clean_up_mess(Token_stream& ts)
{
    ts.ignore(print);
}

void calculate(Token_stream& ts) {
    while (cin) {
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get(); // eat 'print'
            if (t.kind == quit) { // 'x' for "exit"
                return;
            }
            ts.unget(t);
            cout << result << statement(ts) << '\n';
        }
        catch (exception& e) {
            cerr << e.what() << '\n'; // report the error
            clean_up_mess(ts);
        }
    }
}

int main()
try
{
    cout << "Welcome to our simple calculator.\n"
         << "Please enter expressions using floating-point numbers.\n"
         << "Operators: +, -, *, /, and parentheses ().\n"
         << "Type 'q' to exit.\n";

    sym_table.define_name("pi", 3.1415926535897932385); // define pi
    sym_table.define_name("e", 2.7182818284590452354); // define e

    calculate(ts);
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
