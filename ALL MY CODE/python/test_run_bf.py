# (python)
import pytest
from main.py import run_bf
# assumes run_bf(code, input_str) is defined above

CASES = [
    (",+.", "A", "B"),
    (",[.,]", "Hi", "Hi"),
    ("", "anything", ""),
    (".", "", "\x00"),
    ("+" * 256 + ".", "", "\x00"),
    ("-" + ".", "", "\xff"),
    (">+<.", "", "\x00"),
    (">+.", "", "\x00"),
    ("<.<.", "", "\x00\x00"),
    ("+" * 65 + ">" + "+" * 66 + "<." + ">.", "", "AB"),
    (",.,.,.,.", "Hi", "Hi\x00"),
    ("this is not brainfuck,+. but it has + and . inside", "", "\x01"),
    ("+++[.-]", "", "\x03\x02\x01"),
    ("[]+.", "", "\x01"),
    ("++[>+++<-]>.", "", "\x06"),
    (",[.,]", "Where?", "Where?"),
    (",[.,]", "A" + "\x00", "A"),
    ("+++++++++[>+++++++++<-]>.+.>+++.", "", "Hi!"),
    (">" * 1000 + "+" + "<" * 1000 + "." + ">" * 1000 + ".", "", "\x00\x01"),
    ("abc[def]+]ghi.[,]jkl", "Z", "\x01"),
    (",[.,]", "Yo", "Yo"),
    (">" * 35000 + "+" + ".", "", "\x01"),
]

@pytest.mark.parametrize("code,inp,expected", CASES)
def test_run_bf(code, inp, expected):
    out = run_bf(code, inp)
    assert out == expected, (
        f"\nCode: {code}\nInput: {repr(inp)}\nExpected: {repr(expected)}\nActual:   {repr(out)}"
    )
