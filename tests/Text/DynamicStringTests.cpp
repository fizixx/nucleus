
#include "nucleus/Testing.h"
#include "nucleus/Text/DynamicString.h"

namespace nu {

TEST_CASE("DynamicString can be copied") {
  DynamicString str1{"testing"};

  SECTION("copy construction") {
    DynamicString str3{str1};
    CHECK(str3.getData() != str1.getData());
    CHECK(str3.compare(str1) == 0);
  }

  SECTION("copy assignment") {
    DynamicString str2;
    str2 = str1;

    CHECK(str2.getData() != str1.getData());
    CHECK(str1.compare(str2) == 0);
  }
}

TEST_CASE("DynamicString does not allocate a buffer when default constructed") {
  DynamicString str;
  CHECK(str.getAllocated() == 0);
}

TEST_CASE("DynamicString increases size correctly") {
  SECTION("with c-string") {
    DynamicString str{"Do this test!"};
    CHECK(str.getLength() == 13);
    CHECK(str.getAllocated() == 16);  // Minimum allocation size.
  }

  SECTION("with StringView") {
    DynamicString str{StringView{"Do this test!", 10}};
    CHECK(str.getLength() == 10);
    CHECK(str.getAllocated() == 16);  // Minimum allocation size.
  }
}

TEST_CASE("DynamicString grows when appending") {
  DynamicString str{"Do this test!"};

  SECTION("with c-string") {
    str.append("some more text");
    CHECK(str.getLength() == 27);
    CHECK(str.getAllocated() == 32);
  }

  SECTION("with StringView") {
    str.append(StringView{"some more text"});
    CHECK(str.getLength() == 27);
    CHECK(str.getAllocated() == 32);
  }
}

TEST_CASE("DynamicString can erase text") {
  DynamicString str{"abcd"};

  SECTION("erase from beginning") {
    str.erase(0, 2);
    CHECK(str.compare("cd") == 0);
  }

  SECTION("erase past the allocated size") {
    str.erase(2, 10);
    CHECK(str.compare("ab") == 0);
  }
}

}  // namespace nu
