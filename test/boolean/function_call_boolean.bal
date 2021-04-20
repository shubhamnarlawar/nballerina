// RUN: "%testRunScript" %s %nballerinacc "%java_path" "%skip_bir_gen" | filecheck %s

public function print_string(string val) = external;

public function print_boolean(boolean val) = external;

public function bar(boolean z) returns boolean {
    return z && false;
}

public function main() {
    boolean a = true;
    print_string("RESULT=");
    print_boolean(bar(a));
}
// CHECK: RESULT=false
