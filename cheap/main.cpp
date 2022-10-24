#include <string>
#include <vector>
#include <variant>
#include <format>
#include <optional>
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

   struct element;
   using content = std::variant<element, std::string>;


   struct arbitrary_element
   {
      std::string m_type;
      std::vector<attribute> m_attributes;
      std::vector<content> m_inner_html;
   };

   template<int>
   struct generic_element
   {
      std::vector<attribute> m_attributes;
      std::vector<content> m_inner_html;
   };

   using div = generic_element<__COUNTER__>;
   using span = generic_element<__COUNTER__>;
   using svg = generic_element<__COUNTER__>;
   

   struct element : std::variant<arbitrary_element, div, span, svg>
   {
      using variant::variant;

      [[nodiscard]] auto has_content() const -> bool
      {
         const auto visitor = [](const auto& alternative)
         {
            return alternative.m_inner_html.size() != 0;
         };
         return std::visit(visitor, *this);
      }


      [[nodiscard]] auto get_trivial_content() const -> std::optional<std::string>
      {
         const auto visitor = [](const auto& alternative) -> std::optional<std::string>
         {
            if(alternative.m_inner_html.size() == 1 && std::holds_alternative<std::string>(alternative.m_inner_html.front()))
            {
               return std::get<std::string>(alternative.m_inner_html.front());
            }
            return std::nullopt;
         };
         return std::visit(visitor, *this);
      }


      [[nodiscard]] auto get_element_name() const -> std::string
      {
         const auto visitor = []<typename T>(const T& alternative)
         {
            if constexpr(std::same_as<T, arbitrary_element>)
            {
               return alternative.m_type;
            }
            else if constexpr (std::same_as<T, div>) { return std::string{ "div" }; }
            else if constexpr (std::same_as<T, span>) { return std::string{ "span" }; }
            else if constexpr (std::same_as<T, svg>) { return std::string{ "svg" }; }
         };
         return std::visit(visitor, *this);
      }
   };

   static_assert(std::is_aggregate_v<accesskey>);
   static_assert(std::is_aggregate_v<arbitrary_element>);

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


   [[nodiscard]] auto get_attribute_str(const element& elem) -> std::string
   {
      const auto visitor = []<typename T>(const T& alternative)
      {
         return to_string(alternative.m_attributes);
      };
      return std::visit(visitor, elem);
   }


   constexpr int indent = 3;

   auto get_spaces(const int count) -> std::string
   {
      std::string result;
      result.reserve(count);
      for (int i = 0; i < count; ++i)
         result += ' ';
      return result;
   }


   [[nodiscard]] auto get_element_str(const std::string& elem, const int level) -> std::string
   {
      return std::format("{}{}", get_spaces(level * indent), elem);
   }

   namespace detail
   {
      template<typename variant_type, typename visitor_type>
      [[nodiscard]] auto get_joined_visits(
         const std::vector<variant_type>& variants,
         const visitor_type& visitor,
         const std::string_view delim
      ) -> std::string
      {
         if (variants.empty())
            return std::string{};
         std::string result;
         for (int i = 0; i < std::ssize(variants); ++i)
         {
            if (i > 0)
               result += '\n';
            result += std::visit(visitor, variants[i]);
         }
         return result;
      }
   }


   [[nodiscard]] auto get_inner_html_str(const element& variant, const int level) -> std::string
   {
      const auto outer_visitor = [&](const auto& element) -> std::string
      {
         const auto content_visitor = [&]<typename T>(const T& alternative) -> std::string
         {
            return get_element_str(alternative, level + 1);
         };
   
         return detail::get_joined_visits(element.m_inner_html, content_visitor, "\n");
      };
   
      return std::visit(outer_visitor, variant);
   }


   [[nodiscard]] auto get_element_str(const element& elem, const int level = 0) -> std::string
   {
      if(const auto x = elem.get_trivial_content(); x.has_value())
      {
         return std::format(
            "{}<{}>{}</{}>",
            get_spaces(level * indent),
            elem.get_element_name(),
            x.value(),
            elem.get_element_name()
         );
      }
      else
      {
         std::string result;
         result += std::format("<{}>", elem.get_element_name());
         result += '\n';
         result += get_inner_html_str(elem, level);
         result += '\n';
         result += std::format("</{}>", elem.get_element_name());
         return result;
      }
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
   
   arbitrary_element sub{ .m_type = "span", .m_inner_html = {"content0"} };
   span s0{ .m_inner_html = {""}};
   cheap::div main{
      .m_inner_html = {"content0", sub, s0}
   };
   const auto str = get_element_str(main);

   std::ofstream file_out("test.html");
   file_out << str;

   return 0;
}
