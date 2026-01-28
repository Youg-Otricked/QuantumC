namespace Exported {
    #include <UnitTest, ./stdlib.qc>
    #include <Collections, ./stdlib.qc>
}

int main() {
    UnitTest::Test t = UnitTest::Test(8);
    string[] l = ["a", "b", "c"];
    t.AssertTrue(Collections::has(l, "b"), "has should return true for existing element", "has(l, \"b\")");
    t.AssertFalse(Collections::has(l, "x"), "contains should return false for missing element", "has(l, \"x\")");
    string[] l = ["a", "b", "c", "b"];
    t.AssertEqual(1, Collections::index_of(l, "b"), "index_of should return first index", "index_of(l, \"b\")");
    t.AssertEqual(-1, Collections::index_of(l, "x"), "index_of should return -1 if not found", "index_of(l, \"x\")");
    int[] l = [3, 1, 4, 2];
    int[] sorted = Collections::sort(l);

    int[] expected = [1, 2, 3, 4];
    t.AssertEqual(expected, sorted, "sort should sort list ascending", "sort(l)");
    list<int> l = [1, 2, 3, 4, 5];
    l = Collections::remove(l, 3);
    t.AssertEqual(l, [1, 2, 4, 5], "", "remove(l, 3)");
    list<int> r = [1, 2, 3, 4];
    list<int> reversed = Collections::reverse(r);
    t.AssertEqual(reversed, [4, 3, 2, 1], "", "reverse([1,2,3,4])");
    list<int> odd = [1, 2, 3];
    t.AssertEqual(Collections::reverse(odd), [3, 2, 1], "", "reverse([1,2,3])");
}
