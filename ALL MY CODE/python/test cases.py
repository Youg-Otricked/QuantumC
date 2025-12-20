#test cases for parser/lexer
from compiler import parse

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

main()
