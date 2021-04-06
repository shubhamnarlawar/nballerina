// RUN: "%testRunScript" %s %nballerinacc "%java_path" "%skip_bir_gen" | filecheck %s

public function print_string(string val) = external;

public function print_i64(int val) = external;

public function main() {
    int a = 0;
    int b = 1;
    int c = a ^ b;
    print_string("RESULT=");
    print_i64(c);
}
// CHECK: RESULT=1
