// #include <fstream>

#define CHEAP_IMPL
#include "cheap.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace cheap;

TEST_CASE("attributes") {
   CHECK(std::holds_alternative<bool_attribute>("xxx"_att));
   CHECK(std::holds_alternative<string_attribute>("xxx=yyy"_att));
   CHECK_THROWS_AS("hidden=xxx"_att, cheap_exception);
   CHECK_THROWS_AS("autocapitalize=xxx"_att, cheap_exception);

   // auto elem = create_element("div", "cool=true"_att, "hallo");
   auto elem = div("data-cool=true"_att,
      span("first"),
      span("second")
      );

   // auto elem = div({ "some string content" });
   std::ofstream file_out("test.html");
   file_out << get_element_str(elem);
}


// int main()
// {
//    using namespace cheap;
//
//    const auto att0 = "x=y"_att;
//    const auto att1 = "x"_batt;
//    
//    arbitrary_element sub{ .m_type = "span", .m_inner_html = {"content0"} };
//    span s0{ .m_inner_html = {""}};
//    cheap::div main{
//       .m_attributes= {"hidden=b"_att, "doit"_batt},
//       .m_inner_html = {"content0", sub, s0}
//    };
//    const auto str = get_element_str(main);
//
//    std::ofstream file_out("test.html");
//    file_out << str;
//
//    return 0;
// }
