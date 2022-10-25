#include <fstream>

// #define FMT_HEADER_ONLY
// #include <fmt/format.h>

// #define CHEAP_USE_FMT
#define CHEAP_IMPL
#include "../cheap.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"



using namespace cheap;

TEST_CASE("attributes basics"){
   CHECK(std::holds_alternative<bool_attribute>("xxx"_att));
   CHECK(std::holds_alternative<string_attribute>("xxx=yyy"_att));
}

TEST_CASE("attributes error checks") {
   CHECK_THROWS_AS("hidden=xxx"_att, cheap_exception);
   CHECK_THROWS_AS("autocapitalize=xxx"_att, cheap_exception);
   CHECK_THROWS_AS("id"_att, cheap_exception);
}

TEST_CASE("get_element_str()") {
   CHECK_EQ(get_element_str(div()), "<div></div>\n");
   CHECK_EQ(get_element_str(div("bool"_att)), "<div bool></div>\n");
   CHECK_EQ(get_element_str(div("key=val"_att)), "<div key=\"val\"></div>\n");
   CHECK_EQ(get_element_str(div("abc")), "<div>abc</div>\n");
   CHECK_EQ(get_element_str(div(span("abc"))), "<div>\n    <span>abc</span>\n</div>\n");
   CHECK_EQ(get_element_str({div(), div()}), "<div></div>\n<div></div>\n");
   CHECK_EQ(get_element_str(img()), "<img />\n");
   SUBCASE("false boolean attribute"){
      CHECK_EQ(get_element_str(img(bool_attribute{.m_name="test", .m_value = false })), "<img />\n");
   }
}

// TEST_CASE("playground"){
//    const std::string elem_str = get_element_str(
//       { img("src=a.jpg"_att), img("src=b.jpg"_att) }
//    );
//    std::ofstream file_out("test.html");
//    file_out << elem_str;
// }



// int main()
// {
//    using namespace cheap;
//    std::vector<element> elements;
//    elements.reserve(1'000'000);
//    for(int i=0; i<1'000'000; ++i)
//    {
//       auto& ref = elements.emplace_back("div");
//
//       ref.m_attributes.reserve(3);
//       ref.m_attributes.push_back(bool_attribute{ "xxx" });
//       ref.m_attributes.push_back(bool_attribute{ "yyy" });
//       ref.m_attributes.push_back(bool_attribute{ "zzz" });
//       ref.m_inner_html.push_back(element{ "div", {"inner"} });
//    }
// }