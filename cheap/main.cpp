#include <string>
#include <vector>
#include <variant>
#include <format>
#include <fstream>


namespace cheap
{
   struct boolean_attribute
   {
      bool m_value = true;
   };

   struct string_attribute
   {
      std::string m_value;
   };



   template<typename T>
   struct enumerated_attribute
   {
      using enum_type = T;
      T m_value;
      explicit enumerated_attribute(const T initial) : m_value(initial) {}
   };

   template<typename T>
   concept boolean_attribute_c = std::derived_from<T, boolean_attribute>;
   template<typename T>
   concept string_attribute_c = std::derived_from<T, string_attribute>;
   template<typename T, typename state = typename T::enum_type>
   concept enumeration_attribute_c = std::derived_from<T, enumerated_attribute<state>>;



   struct autofocus : boolean_attribute { };
   struct accesskey : string_attribute { };
   enum class autocapitalize_state{off, on, sentences, words, characters};
   struct autocapitalize : enumerated_attribute<autocapitalize_state>{ using enumerated_attribute::enumerated_attribute; };

   using attribute = std::variant<autofocus, accesskey, autocapitalize>;

   struct string_element
   {
      std::string m_value;
   };

   struct element;
   using content = std::variant<element, string_element>;


   struct element
   {
      std::string m_type;
      std::vector<attribute> m_attributes;
      std::vector<content> m_inner_html;
   };

   static_assert(std::is_aggregate_v<accesskey>);
   // static_assert(std::is_aggregate_v<element>);

   template<typename T>
   struct attribute_name { };
   template<> struct attribute_name<autofocus>{ constexpr static inline std::string_view value = "autofocus"; };
   template<> struct attribute_name<accesskey>{ constexpr static inline std::string_view value = "accesskey"; };
   template<> struct attribute_name<autocapitalize>{ constexpr static inline std::string_view value = "autocapitalize"; };
   template<typename T> constexpr inline static std::string_view attribute_name_v = attribute_name<T>::value;

   [[nodiscard]] auto to_string(const autocapitalize_state& state) -> std::string
   {
      switch(state)
      {
      case autocapitalize_state::off: return "off";
      case autocapitalize_state::on: return "on";
      case autocapitalize_state::sentences: return "sentences";
      case autocapitalize_state::words: return "words";
      case autocapitalize_state::characters: return "characters";
      }
      std::terminate();
   }

   template<boolean_attribute_c bool_attrib_type>
   [[nodiscard]] auto to_string(const bool_attrib_type& attrib) -> std::string
   {
      // The presence of a boolean attribute on an element represents the true
      // value, and the absence of the attribute represents the false value.
      // [...]]
      // The values "true" and "false" are not allowed on boolean attributes.
      // To represent a false value, the attribute has to be omitted altogether.
      // [https://html.spec.whatwg.org/dev/common-microsyntaxes.html#boolean-attributes]
      return attrib.m_value ? std::string{ attribute_name_v<bool_attrib_type> } : "";
   }
   

   template<string_attribute_c string_attribute_type>
   [[nodiscard]] auto to_string(const string_attribute_type& attrib) -> std::string
   {
      return std::format("{}=\"{}\"", attribute_name_v<string_attribute_type>, attrib.m_value);
   }


   template<enumeration_attribute_c enum_attrib_type>
   [[nodiscard]] auto to_string(const enum_attrib_type& attrib) -> std::string
   {
      return std::format("{}=\"{}\"", attribute_name_v<enum_attrib_type>, to_string(attrib.m_value));
   }



   [[nodiscard]] auto to_string(const std::vector<attribute>& attributes) -> std::string
   {
      std::string result;
   
      const auto visitor = [](const auto& alternative) { return to_string(alternative); };
      for (const auto& attribute : attributes)
      {
         result += std::format(" {}", std::visit(visitor, attribute));
      }
      return result;
   }

   constexpr int indent = 3;

   auto get_spaces(const int count) -> std::string
   {
      std::string result;
      for (int i = 0; i < count; ++i)
         result += ' ';
      return result;
   }

   [[nodiscard]] auto to_string(const string_element& elem, const int level)->std::string
   {
      return std::format("{}{}", get_spaces(level * indent), elem.m_value);
   }

   [[nodiscard]] auto to_string(const element& elem, const int level=0) -> std::string
   {
      std::string inner_html_str;
      if (elem.m_inner_html.empty() == false)
         inner_html_str = "\n";
      const auto content_visitor = [&]<typename T>(const T& alternative) -> std::string
      {
         return to_string(alternative, level + 1);
      };
      for(const auto& inner_element : elem.m_inner_html)
      {
         inner_html_str += std::visit(content_visitor, inner_element);
         inner_html_str += "\n";
      }

      const std::string opening_indent_str = get_spaces(level * indent);
      const std::string closing_indent_str = (elem.m_inner_html.empty() == false) ? opening_indent_str : "";
      return std::format(
         "{}<{}{}>{}{}</{}>",
         opening_indent_str,
         elem.m_type,
         to_string(elem.m_attributes),
         inner_html_str,
         closing_indent_str,
         elem.m_type
      );
   }
}


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

   // const std::string x = std::format("{: >{}}", "", 5);

   test(to_string(autofocus{ false }), "");
   test(to_string(autofocus{ true }), "autofocus");
   test(to_string(autofocus{}), "autofocus");

   test(to_string(accesskey{ "A" }), "accesskey=\"A\"");
   test(to_string(accesskey{}), "accesskey=\"\"");

   test(to_string(std::vector<attribute>{}), "");
   test(to_string(std::vector<attribute>{autofocus{}, autocapitalize{autocapitalize_state::off}}), " autofocus autocapitalize=\"off\"");
   
   element sub{ .m_type = "span", .m_inner_html = {string_element{"content0"}} };
   element main{ "div", {accesskey{"test"}, autocapitalize{autocapitalize_state::off}}, {string_element{"content0"}, sub} };
   const auto str = to_string(main);
   // const auto str = to_string(sub);

   std::ofstream file_out("test.html");
   file_out << str;

   return 0;
}
