#include <fstream>

#include "cheap.h"


auto test(const bool value) -> void
{
   if (value == false)
      std::terminate();
}

auto test(const std::string& a, const std::string& b) -> void
{
   if (a != b)
   {
      int i = 0;
      while(true)
      {
         if (std::string{ a[i] } != std::string{ b[i] })
            std::terminate();
      }
      std::terminate();
   }
}


int main()
{
   using namespace cheap;

   const auto att0 = "x=y"_att;
   const auto att1 = "x"_batt;
   
   arbitrary_element sub{ .m_type = "span", .m_inner_html = {"content0"} };
   span s0{ .m_inner_html = {""}};
   cheap::div main{
      .m_attributes= {"hidden=b"_att, "doit"_batt},
      .m_inner_html = {"content0", sub, s0}
   };
   const auto str = get_element_str(main);

   std::ofstream file_out("test.html");
   file_out << str;

   return 0;
}
