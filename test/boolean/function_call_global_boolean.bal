// RUN: "%testRunScript" %s %nballerinacc "%java_path" "%skip_bir_gen" | filecheck %s

public function print_string(string val) = external;

public function print_boolean(boolean val) = external;

public function bar(boolean z) returns boolean {
    return z && false;
}

boolean a = true;
public function main() {
    print_string("RESULT=");
    print_boolean(bar(a));
}
// CHECK: RESULT=false
