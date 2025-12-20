# i made a mini c++ like lexel and parser
class Token:
    def __init__(self, kind, value):
        self.kind = kind
        self.value = value

KEYWORDS = {
    "int": "INT",#it can handle int declerations, + - * / = (, ) , and all statments end in ;. it can also handle all ints and negitive ints
}

SINGLE = {
    "+": "PLUS",
    "-": "MINUS",
    "*": "STAR",
    "/": "SLASH",
    "=": "EQUAL",
    "(": "LPAREN",
    ")": "RPAREN",
    ";": "SEMICOLON",
}

def tokenize(source):
    tokens = []
    # python
    i = 0
    s = source
    while i < len(s):
        ch = s[i]
        if ch.isspace():
            i += 1
            continue
        if ch.isdigit():
            start = i
            while i < len(s) and s[i].isdigit():
                i += 1
            num_text = s[start:i]  # "123"
            tokens.append(Token("NUMBER", int(num_text)))
            continue
        if ch.isalpha() or ch == "_":
            start = i
            while i < len(s) and (s[i].isalnum() or s[i] == "_"):
                i += 1
            ident = s[start:i]  # "int" or "x"
            if ident in KEYWORDS:
                tokens.append(Token(KEYWORDS[ident], ident))
            else:
                tokens.append(Token("IDENT", ident))
            continue
        if s[i] in SINGLE:
            tokens.append(Token(SINGLE[s[i]], s[i]))
            i += 1
        else:
            raise ValueError("Unexpected char: " + s[i])
        
    tokens.append(Token("EOF", None))
    return tokens

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0

    def current(self):
        return self.tokens[self.pos]

    def advance(self):
        self.pos += 1
        return self.tokens[self.pos - 1]

    def match(self, kind):
        if self.current().kind == kind:
            return self.advance()
        return None

    def expect(self, kind, msg):
        if self.current().kind != kind:
            raise ValueError(msg)
        return self.advance()

    def parse_statement(self):
        if self.current().kind == "INT":
            self.advance()
            
            # Step 2: Get the identifier name
            name_token = self.expect("IDENT", "Expected identifier after 'int'")
            name = name_token.value  # Extract the actual name string
            
            # Step 3: Check for '='
            if self.match("EQUAL") is not None:
                # There's an '=', so parse the expression
                initializer = self.parse_expression()  # What method should you call here?
            else:
                # No '=', so no initializer
                initializer = None
            
            # Step 4: Expect semicolon
            self.expect("SEMICOLON", "Expected ';'")
            
            # Step 5: Return the declaration tuple
            return ("decl", "int", name, initializer)
        expr = self.parse_expression()
        self.expect("SEMICOLON", "Expected ';'")
        return ("expr", expr)
            
        
    def parse_expression(self):
        left = self.parse_term()
        while self.current().kind == "PLUS" or self.current().kind == "MINUS":
            op = self.advance().value
            right = self.parse_term()
            left = ("binop", op, left, right)
        return left
    def parse_term(self):
        left = self.parse_factor()
        while self.current().kind == "STAR" or self.current().kind == "SLASH":
            op = self.advance().value
            right = self.parse_factor()
            left = ("binop", op, left, right)
        return left
    def parse_factor(self):
        if self.current().kind == "MINUS":
            self.advance()
            return ("unary", "-", self.parse_factor())
        if self.current().kind == "NUMBER":
            return ("num", self.advance().value)
        if self.current().kind == "IDENT":
            return ("ident", self.advance().value)
        if self.current().kind == "LPAREN":
            self.advance()
            inner = self.parse_expression()
            self.expect("RPAREN", "Expected ')'")
            return inner
        raise ValueError("Expected a number, identifier, or '('")
def parse(source):
    tokens = tokenize(source)
    parser = Parser(tokens)
    ast = parser.parse_statement()
    return ast
    



valid_cases = [
    # Simple numbers and identifiers
    ("0;", ("expr", ("num", 0))),
    ("12345;", ("expr", ("num", 12345))),
    ("x;", ("expr", ("ident", "x"))),
    ("_foo123;", ("expr", ("ident", "_foo123"))),

    # Spacing/whitespace
    ("   42   ;", ("expr", ("num", 42))),
    ("x   +    1   ;", ("expr", ("binop", "+", ("ident", "x"), ("num", 1)))),
    ("(   1+2 ) *   3   ;", ("expr", ("binop", "*", ("binop", "+", ("num", 1), ("num", 2)), ("num", 3)))),

    # Unary minus
    ("-5;", ("expr", ("unary", "-", ("num", 5)))),
    ("-x;", ("expr", ("unary", "-", ("ident", "x")))),
    ("-(-5);", ("expr", ("unary", "-", ("unary", "-", ("num", 5))))),
    ("x + -5;", ("expr", ("binop", "+", ("ident", "x"), ("unary", "-", ("num", 5))))),
    ("-(-(-3));", ("expr", ("unary", "-", ("unary", "-", ("unary", "-", ("num", 3)))))),
    ("(-x) * 2;", ("expr", ("binop", "*", ("unary", "-", ("ident", "x")), ("num", 2)))),

    # Binary ops and precedence
    ("1 + 2 * 3;", ("expr", ("binop", "+", ("num", 1), ("binop", "*", ("num", 2), ("num", 3))))),
    ("(1 + 2) * 3;", ("expr", ("binop", "*", ("binop", "+", ("num", 1), ("num", 2)), ("num", 3)))),
    ("8 / 4 + 2;", ("expr", ("binop", "+", ("binop", "/", ("num", 8), ("num", 4)), ("num", 2)))),
    ("8 / (4 + 2);", ("expr", ("binop", "/", ("num", 8), ("binop", "+", ("num", 4), ("num", 2))))),
    ("7 - 3 - 2;", ("expr", ("binop", "-", ("binop", "-", ("num", 7), ("num", 3)), ("num", 2)))),
    ("20 / 5 / 2;", ("expr", ("binop", "/", ("binop", "/", ("num", 20), ("num", 5)), ("num", 2)))),
    ("1 + 2 + 3 + 4;", ("expr", ("binop", "+", ("binop", "+", ("binop", "+", ("num", 1), ("num", 2)), ("num", 3)), ("num", 4)))),
    ("2 * 3 * 4;", ("expr", ("binop", "*", ("binop", "*", ("num", 2), ("num", 3)), ("num", 4)))),
    ("10 - 2 * 3 + 1;", ("expr", ("binop", "+", ("binop", "-", ("num", 10), ("binop", "*", ("num", 2), ("num", 3))), ("num", 1)))),
    ("10 / 2 * 3;", ("expr", ("binop", "*", ("binop", "/", ("num", 10), ("num", 2)), ("num", 3)))),
    ("2 * (3 + 4) / 7;", ("expr", ("binop", "/", ("binop", "*", ("num", 2), ("binop", "+", ("num", 3), ("num", 4))), ("num", 7)))),

    # Parentheses and nesting
    ("((1));", ("expr", ("num", 1))),
    ("(((1 + 2)));", ("expr", ("binop", "+", ("num", 1), ("num", 2)))),
    ("(1 + (2 * (3 + 4)));", ("expr", ("binop", "+", ("num", 1), ("binop", "*", ("num", 2), ("binop", "+", ("num", 3), ("num", 4)))))),
    ("((1 + 2) * (3 + 4));", ("expr", ("binop", "*", ("binop", "+", ("num", 1), ("num", 2)), ("binop", "+", ("num", 3), ("num", 4))))),
    ("(x + (y * (z + 1)));", ("expr", ("binop", "+", ("ident", "x"), ("binop", "*", ("ident", "y"), ("binop", "+", ("ident", "z"), ("num", 1)))))),

    # Mixed unary with parentheses
    ("-(1 + 2);", ("expr", ("unary", "-", ("binop", "+", ("num", 1), ("num", 2))))),
    ("-1 * 5;", ("expr", ("binop", "*", ("num", 1), ("num", 5)))),  # Note: (-1) lexes as NUMBER 1 with unary outside? Here it's parenthesized 1 only; toy grammar doesn't support negative literals directly, so adjust:
    # To fit the grammar, use: -1 * 5;
    ("-1 * 5;", ("expr", ("binop", "*", ("unary", "-", ("num", 1)), ("num", 5)))),
    ("-((1 + 2) * 3);", ("expr", ("unary", "-", ("binop", "*", ("binop", "+", ("num", 1), ("num", 2)), ("num", 3))))),
    ("(-x) + (-y);", ("expr", ("binop", "+", ("unary", "-", ("ident", "x")), ("unary", "-", ("ident", "y"))))),

    # Identifiers in expressions
    ("a + b * c;", ("expr", ("binop", "+", ("ident", "a"), ("binop", "*", ("ident", "b"), ("ident", "c"))))),
    ("(a + b) * c;", ("expr", ("binop", "*", ("binop", "+", ("ident", "a"), ("ident", "b")), ("ident", "c")))),
    ("a * -b + c;", ("expr", ("binop", "+", ("binop", "*", ("ident", "a"), ("unary", "-", ("ident", "b"))), ("ident", "c")))),
    ("hp + (armor / 2);", ("expr", ("binop", "+", ("ident", "hp"), ("binop", "/", ("ident", "armor"), ("num", 2))))),

    # Declarations without initializer
    ("int a;", ("decl", "int", "a", None)),
    ("int _abc123;", ("decl", "int", "_abc123", None)),
    ("int score;", ("decl", "int", "score", None)),
    ("int X;", ("decl", "int", "X", None)),

    # Declarations with initializer
    ("int a = 0;", ("decl", "int", "a", ("num", 0))),
    ("int a = 1 + 2 * 3;", ("decl", "int", "a", ("binop", "+", ("num", 1), ("binop", "*", ("num", 2), ("num", 3))))),
    ("int a = (1 + 2) * 3;", ("decl", "int", "a", ("binop", "*", ("binop", "+", ("num", 1), ("num", 2)), ("num", 3)))),
    ("int a = -5;", ("decl", "int", "a", ("unary", "-", ("num", 5)))),
    ("int a = -(-5);", ("decl", "int", "a", ("unary", "-", ("unary", "-", ("num", 5))))),
    ("int a = x + -y;", ("decl", "int", "a", ("binop", "+", ("ident", "x"), ("unary", "-", ("ident", "y"))))),
    ("int a = (x + 1) * (y + 2);", ("decl", "int", "a", ("binop", "*", ("binop", "+", ("ident", "x"), ("num", 1)), ("binop", "+", ("ident", "y"), ("num", 2))))),
    ("int hp = (10 - 3) * 2;", ("decl", "int",))
    ]
def runbc():
    passed = 0
    failed = 0
    for src, expected in valid_cases:
        try:
            result = parse(src)
            ok = (result == expected)
        except Exception as e:
            result = f"Error: {e}"
            ok = False
        print("---------------------------------")
        print("Input:   ", src)
        print("Expected:", expected)
        print("Actual:  ", result)
        if ok:
            print("Pass")
            passed += 1
        else:
            print("Fail")
            failed += 1
    print("============ RESULTS ============")
    print(f"{passed} passed, {failed} failed")



run_cases = [
    ("int x = 1 + 2 * 3;", ("decl", "int", "x", ("binop", "+", ("num", 1), ("binop", "*", ("num", 2), ("num", 3))))),
    ("7 + 5;", ("expr", ("binop", "+", ("num", 7), ("num", 5)))),
    ("int y;", ("decl", "int", "y", None)),
]

submit_cases = run_cases + [
    ("(1 + 2) * 3;", ("expr", ("binop", "*", ("binop", "+", ("num", 1), ("num", 2)), ("num", 3)))),
    ("int hp = (10 - 3) * 2;", ("decl", "int", "hp", ("binop", "*", ("binop", "-", ("num", 10), ("num", 3)), ("num", 2)))) ,
    ("score + -5;", ("expr", ("binop", "+", ("ident", "score"), ("unary", "-", ("num", 5))))),
]


def test(input_src, expected_output):
    print("---------------------------------")
    print("Input:")
    print(input_src)
    print("")
    try:
        result = parse(input_src)
    except Exception as e:
        print("Error while parsing:")
        print(str(e))
        print("Fail")
        return False
    print("Expected:")
    print(expected_output)
    print("Actual:")
    print(result)
    if result == expected_output:
        print("Pass")
        return True
    print("Fail")
    return False


def main():
    passed = 0
    failed = 0
    skipped = len(submit_cases) - len(test_cases)
    for case in test_cases:
        ok = test(*case)
        if ok:
            passed += 1
        else:
            failed += 1
    if failed == 0:
        print("============= PASS ==============")
    else:
        print("============= FAIL ==============")
    if skipped > 0:
        print(f"{passed} passed, {failed} failed, {skipped} skipped")
    else:
        print(f"{passed} passed, {failed} failed")


test_cases = submit_cases
if "__RUN__" in globals():
    test_cases = run_cases


        
        
# python
cases = [
    ("0;", ("expr", ("num", 0))),
    ("12345;", ("expr", ("num", 12345))),
    ("x;", ("expr", ("ident", "x"))),
    ("-5;", ("expr", ("unary", "-", ("num", 5)))),
    ("1 + 2 * 3;", ("expr", ("binop", "+", ("num", 1), ("binop", "*", ("num", 2), ("num", 3))))),
    ("(1 + 2) * 3;", ("expr", ("binop", "*", ("binop", "+", ("num", 1), ("num", 2)), ("num", 3)))),
    ("7 - 3 - 2;", ("expr", ("binop", "-", ("binop", "-", ("num", 7), ("num", 3)), ("num", 2)))),
    ("10 / 2 * 3;", ("expr", ("binop", "*", ("binop", "/", ("num", 10), ("num", 2)), ("num", 3)))),
    ("x + -5;", ("expr", ("binop", "+", ("ident", "x"), ("unary", "-", ("num", 5))))),
    ("int a;", ("decl", "int", "a", None)),
    ("int a = -(-5);", ("decl", "int", "a", ("unary", "-", ("unary", "-", ("num", 5))))),
    ("int hp = (10 - 3) * 2;", ("decl", "int", "hp", ("binop", "*", ("binop", "-", ("num", 10), ("num", 3)), ("num", 2)))),
]

def run():
    passed = 0
    failed = 0
    for src, expected in cases:
        try:
            result = parse(src)
            ok = (result == expected)
        except Exception as e:
            result = f"Error: {e}"
            ok = False
        print("---------------------------------")
        print("Input:   ", src)
        print("Expected:", expected)
        print("Actual:  ", result)
        if ok:
            print("Pass")
            passed += 1
        else:
            print("Fail")
            failed += 1
    print("============ RESULTS ============")
    print(f"{passed} passed, {failed} failed")
tests = input("which test suite.(1/2/3)")
if tests == 1:
    run()
elif tests == 2:
    runbc()
else:
    main()