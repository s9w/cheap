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
   SUBCASE("inja compatibility") {
      CHECK_EQ(get_element_str(div("{{ content }}")), "<div>{{ content }}</div>\n");
      CHECK_EQ(get_element_str(div("{{key}}={{value}}"_att)), "<div {{key}}=\"{{value}}\"></div>\n");
      CHECK_EQ(get_element_str(create_element("{{name}}")), "<{{name}}></{{name}}>\n");
   }
   SUBCASE("initial_level param") {
      CHECK_EQ(get_element_str(div()), "<div></div>\n");
      CHECK_EQ(get_element_str(div(), options{.initial_level = 1}), "    <div></div>\n");
      CHECK_EQ(get_element_str(a(a()), options{ .initial_level = 1 }), "    <a>\n        <a></a>\n    </a>\n");
   }
}

TEST_CASE("escaping")
{
   SUBCASE("attributes"){
      const auto attribute_helper = [](const attribute& attrib, const bool escape)
      {
         std::string result;
         detail::write_attribute_string(attrib, result, options{ .escaping = escape });
         return result;
      };
      CHECK_EQ(attribute_helper("a<b"_att, false), " a<b");
      CHECK_EQ(attribute_helper("a<b"_att, true), " a&lt;b");
   }
   SUBCASE("trivial content") {
      CHECK_EQ(get_element_str(div("a<b"), options{.escaping = false}), "<div>a<b</div>\n");
      CHECK_EQ(get_element_str(div("a<b"), options{.escaping = true}), "<div>a&lt;b</div>\n");
   }
   SUBCASE("nontrivial content"){
      CHECK_EQ(get_element_str(div(i(),"a<b", i()), options{.escaping = false}), "<div>\n    <i></i>\n    a<b\n    <i></i>\n</div>\n");
      CHECK_EQ(get_element_str(div(i(),"a<b", i()), options{.escaping = true}),  "<div>\n    <i></i>\n    a&lt;b\n    <i></i>\n</div>\n");
   }
}

TEST_CASE("trailing newline") {
   SUBCASE("self-closing elements") {
      CHECK_EQ(get_element_str(br(), options{ .end_with_newline = true }), "<br />\n");
      CHECK_EQ(get_element_str(br(), options{ .end_with_newline = false }), "<br />");
   }
   SUBCASE("trivial elements") {
      CHECK_EQ(get_element_str(div("abc"), options{ .end_with_newline = true }), "<div>abc</div>\n");
      CHECK_EQ(get_element_str(div("abc"), options{ .end_with_newline = false }), "<div>abc</div>");
   }
   SUBCASE("nontrivial element") {
      CHECK_EQ(get_element_str(div(i(), "abc", i()), options{ .end_with_newline = true }), "<div>\n    <i></i>\n    abc\n    <i></i>\n</div>\n");
      CHECK_EQ(get_element_str(div(i(), "abc", i()), options{ .end_with_newline = false }), "<div>\n    <i></i>\n    abc\n    <i></i>\n</div>");
   }
}

TEST_CASE("tab indentation") {
   CHECK_EQ(get_element_str(div("abc"), options{ .indent_with_tab = false, .initial_level=1 }), "    <div>abc</div>\n");
   CHECK_EQ(get_element_str(div("abc"), options{ .indent_with_tab = true, .initial_level=2 }), "\t\t<div>abc</div>\n");
}

TEST_CASE("vector interface + trailing newlines") {
   CHECK_EQ(get_element_str({ img(), img() }, options{ .end_with_newline = false }), "<img />\n<img />");
   CHECK_EQ(get_element_str({ img(), img() }, options{ .end_with_newline = true }), "<img />\n<img />\n");
}



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