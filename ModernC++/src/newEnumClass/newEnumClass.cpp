// An enhanced version of C's enumeration
// Declared with "enum class" as start.
// 以类名::成员使用，即enumClassName::member
// 1. 强烈性检查
// 2. 防止隐形转换为int
// 3. 有效防止名字冲突

enum class Number {One, Two, Three, Four, Five};

int main(void)
{
    Number num = Number::Three;
    // int num1 = Number::One;  // With strong type check error

    return 0;
}