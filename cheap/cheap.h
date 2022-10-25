// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
#pragma once

#include <exception>
#include <span>
#include <string>
#include <variant>
#include <vector>

#ifndef CHEAP_USE_FMT
#include <format>
#endif


namespace cheap
{
   struct cheap_exception final : std::runtime_error { using runtime_error::runtime_error; };

   struct bool_attribute {
      bool m_value = true; // TODO: setting this to false
      std::string m_name;
   };
   struct string_attribute {
      std::string m_name;
      std::string m_data;
   };
   using attribute = std::variant<bool_attribute, string_attribute>;

   auto operator "" _att(const char* c_str, const std::size_t size) -> attribute;

   struct element;
   using content = std::variant<element, std::string>;

   struct element
   {
      std::string m_type;
      std::vector<attribute> m_attributes;
      std::vector<content> m_inner_html;
      
      explicit element(const std::string_view name, const std::vector<attribute>& attributes, const std::vector<content>& inner_html);
      explicit element(const std::string_view name, const std::vector<content>& inner_html);
      explicit element(const std::string_view name);
      [[nodiscard]] auto is_trivial() const -> bool;
      [[nodiscard]] auto get_trivial() const -> std::string;

   private:
      explicit element() = default;
      template<typename ... Ts>
      friend auto create_element(Ts&&... args) -> element;
   };


   template<typename ... Ts>
   [[nodiscard]] auto create_element(Ts&&... args) -> element;

   template<typename ... Ts> auto html(Ts&&... args) -> element { return create_element("html", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto base(Ts&&... args) -> element { return create_element("base", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto head(Ts&&... args) -> element { return create_element("head", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto link(Ts&&... args) -> element { return create_element("link", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto meta(Ts&&... args) -> element { return create_element("meta", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto style(Ts&&... args) -> element { return create_element("style", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto title(Ts&&... args) -> element { return create_element("title", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto body(Ts&&... args) -> element { return create_element("body", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto address(Ts&&... args) -> element { return create_element("address", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto article(Ts&&... args) -> element { return create_element("article", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto aside(Ts&&... args) -> element { return create_element("aside", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto footer(Ts&&... args) -> element { return create_element("footer", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto header(Ts&&... args) -> element { return create_element("header", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto h1(Ts&&... args) -> element { return create_element("h1", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto h2(Ts&&... args) -> element { return create_element("h2", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto h3(Ts&&... args) -> element { return create_element("h3", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto h4(Ts&&... args) -> element { return create_element("h4", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto h5(Ts&&... args) -> element { return create_element("h5", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto h6(Ts&&... args) -> element { return create_element("h6", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto main(Ts&&... args) -> element { return create_element("main", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto nav(Ts&&... args) -> element { return create_element("nav", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto section(Ts&&... args) -> element { return create_element("section", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto blockquote(Ts&&... args) -> element { return create_element("blockquote", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto dd(Ts&&... args) -> element { return create_element("dd", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto div(Ts&&... args) -> element { return create_element("div", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto dl(Ts&&... args) -> element { return create_element("dl", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto dt(Ts&&... args) -> element { return create_element("dt", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto figcaption(Ts&&... args) -> element { return create_element("figcaption", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto figure(Ts&&... args) -> element { return create_element("figure", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto hr(Ts&&... args) -> element { return create_element("hr", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto menu(Ts&&... args) -> element { return create_element("menu", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto ol(Ts&&... args) -> element { return create_element("ol", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto p(Ts&&... args) -> element { return create_element("p", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto pre(Ts&&... args) -> element { return create_element("pre", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto ul(Ts&&... args) -> element { return create_element("ul", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto a(Ts&&... args) -> element { return create_element("a", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto abbr(Ts&&... args) -> element { return create_element("abbr", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto b(Ts&&... args) -> element { return create_element("b", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto bdi(Ts&&... args) -> element { return create_element("bdi", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto bdo(Ts&&... args) -> element { return create_element("bdo", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto cite(Ts&&... args) -> element { return create_element("cite", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto code(Ts&&... args) -> element { return create_element("code", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto data(Ts&&... args) -> element { return create_element("data", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto dfn(Ts&&... args) -> element { return create_element("dfn", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto em(Ts&&... args) -> element { return create_element("em", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto i(Ts&&... args) -> element { return create_element("i", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto kdb(Ts&&... args) -> element { return create_element("kdb", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto mark(Ts&&... args) -> element { return create_element("mark", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto q(Ts&&... args) -> element { return create_element("q", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto rp(Ts&&... args) -> element { return create_element("rp", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto rt(Ts&&... args) -> element { return create_element("rt", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto ruby(Ts&&... args) -> element { return create_element("ruby", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto s(Ts&&... args) -> element { return create_element("s", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto samp(Ts&&... args) -> element { return create_element("samp", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto small(Ts&&... args) -> element { return create_element("small", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto span(Ts&&... args) -> element { return create_element("span", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto strong(Ts&&... args) -> element { return create_element("strong", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto sub(Ts&&... args) -> element { return create_element("sub", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto sup(Ts&&... args) -> element { return create_element("sup", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto time(Ts&&... args) -> element { return create_element("time", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto u(Ts&&... args) -> element { return create_element("u", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto var(Ts&&... args) -> element { return create_element("var", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto wbr(Ts&&... args) -> element { return create_element("wbr", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto area(Ts&&... args) -> element { return create_element("area", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto audio(Ts&&... args) -> element { return create_element("audio", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto img(Ts&&... args) -> element { return create_element("img", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto map(Ts&&... args) -> element { return create_element("map", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto track(Ts&&... args) -> element { return create_element("track", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto video(Ts&&... args) -> element { return create_element("video", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto embed(Ts&&... args) -> element { return create_element("embed", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto iframe(Ts&&... args) -> element { return create_element("iframe", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto object(Ts&&... args) -> element { return create_element("object", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto picture(Ts&&... args) -> element { return create_element("picture", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto portal(Ts&&... args) -> element { return create_element("portal", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto source(Ts&&... args) -> element { return create_element("source", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto svg(Ts&&... args) -> element { return create_element("svg", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto math(Ts&&... args) -> element { return create_element("math", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto canvas(Ts&&... args) -> element { return create_element("canvas", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto noscript(Ts&&... args) -> element { return create_element("noscript", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto script(Ts&&... args) -> element { return create_element("script", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto del(Ts&&... args) -> element { return create_element("del", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto ins(Ts&&... args) -> element { return create_element("ins", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto caption(Ts&&... args) -> element { return create_element("caption", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto col(Ts&&... args) -> element { return create_element("col", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto colgroup(Ts&&... args) -> element { return create_element("colgroup", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto stable(Ts&&... args) -> element { return create_element("stable", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto tbody(Ts&&... args) -> element { return create_element("tbody", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto td(Ts&&... args) -> element { return create_element("td", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto tfoot(Ts&&... args) -> element { return create_element("tfoot", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto th(Ts&&... args) -> element { return create_element("th", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto thead(Ts&&... args) -> element { return create_element("thead", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto tr(Ts&&... args) -> element { return create_element("tr", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto button(Ts&&... args) -> element { return create_element("button", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto datalist(Ts&&... args) -> element { return create_element("datalist", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto fieldset(Ts&&... args) -> element { return create_element("fieldset", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto form(Ts&&... args) -> element { return create_element("form", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto input(Ts&&... args) -> element { return create_element("input", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto label(Ts&&... args) -> element { return create_element("label", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto legend(Ts&&... args) -> element { return create_element("legend", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto meter(Ts&&... args) -> element { return create_element("meter", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto optgroup(Ts&&... args) -> element { return create_element("optgroup", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto option(Ts&&... args) -> element { return create_element("option", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto progress(Ts&&... args) -> element { return create_element("progress", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto select(Ts&&... args) -> element { return create_element("select", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto textarea(Ts&&... args) -> element { return create_element("textarea", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto details(Ts&&... args) -> element { return create_element("details", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto dialog(Ts&&... args) -> element { return create_element("dialog", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto summary(Ts&&... args) -> element { return create_element("summary", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto slot(Ts&&... args) -> element { return create_element("slot", std::forward<Ts>(args)...); }
   template<typename ... Ts> auto template_(Ts&&... args) -> element { return create_element("template", std::forward<Ts>(args)...); }

   [[nodiscard]] auto get_element_str(const element& elem, const int indentation = 4) -> std::string;
} // namespace cheap

namespace cheap::detail
{
   template<typename T, typename ... types>
   constexpr bool is_any_of = (std::same_as<T, types> || ...);

   template<typename T>
   struct always_false : std::false_type {};
   template<typename alternative_type, typename variant_type>
   struct is_alternative {
      static_assert(always_false<alternative_type>::value, "Can't use is_alternative<> with a non-variant");
   };
   template<typename alternative_type, typename... variant_alternatives>
   struct is_alternative<alternative_type, std::variant<variant_alternatives...>>
      : std::disjunction<std::is_same<alternative_type, variant_alternatives>...>
   {};
   template<typename alternative_type, typename variant_type>
   concept is_alternative_c = is_alternative<alternative_type, variant_type>::value;

   template<typename T>
   auto process(element& result, T&& arg) -> void;

   [[nodiscard]] auto to_string(const attribute& attrib) -> std::string;
   [[nodiscard]] auto get_attribute_str(const element& elem) -> std::string;
   [[nodiscard]] auto get_spaces(const int count) -> std::string;
   [[nodiscard]] auto get_element_str_impl(const std::string& elem, const int indentation, const int current_level) -> std::string;

   template<typename variant_type, typename visitor_type>
   [[nodiscard]] auto get_joined_visits(
      const std::vector<variant_type>& variants,
      const visitor_type& visitor,
      const std::string_view delim
   ) -> std::string;

   [[nodiscard]] auto get_inner_html_str(const element& elem, const int indentation, const int current_level) -> std::string;
   [[nodiscard]] auto get_element_str_impl(const element& elem, const int indentation, const int current_level) -> std::string;
   [[nodiscard]] auto get_attribute_name(const attribute& attrib) -> std::string;
   [[nodiscard]] auto is_in(const std::span<const std::string_view> choices, const std::string& value) -> bool;
   auto assert_attrib_valid(const attribute& attrib) -> void;
   auto assert_string_enum_choice(const attribute& attrib, const std::span<const std::string_view> choices) -> void;

} // namespace cheap::detail

#ifdef CHEAP_USE_FMT
#define CHEAP_FORMAT(...) fmt::format( __VA_ARGS__ )
#else
#define CHEAP_FORMAT(...) std::format( __VA_ARGS__ )
#endif













// template function definitions

template<typename ... Ts>
auto cheap::create_element(Ts&&... args) -> element
{
   static_assert(sizeof...(args) > 0, "At least set a name");

   element result{};
   (detail::process(result, std::forward<Ts>(args)), ...);

   if (result.m_type.empty())
   {
      throw cheap_exception{ "No name set" };
   }
   return result;
}

template<typename variant_type, typename visitor_type>
auto cheap::detail::get_joined_visits(
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


template<typename T>
auto cheap::detail::process(element& result, T&& arg) -> void
{
   if constexpr (is_any_of<T, element, attribute, std::string> == false)
   {
      process(result, std::string{ arg });
   }
   else if constexpr (std::same_as<T, std::string>)
   {
      // string as first parameter -> element name
      if (result.m_type.empty())
      {
         result.m_type = arg;
      }

      // otherwise -> singular content
      else
      {
         if (result.m_inner_html.empty() == false)
         {
            // TODO: error
         }
         result.m_inner_html = { arg };
      }
   }
   else if constexpr (std::same_as<T, attribute>)
   {
      result.m_attributes.push_back(arg);
   }
   else if constexpr (std::same_as<T, element>)
   {
      result.m_inner_html.push_back(arg);
   }
}











#ifdef CHEAP_IMPL

auto cheap::get_element_str(
   const element& elem,
   const int indentation
) -> std::string
{
   return detail::get_element_str_impl(elem, indentation, 0);
}

cheap::element::element(
   const std::string_view name,
   const std::vector<attribute>& attributes,
   const std::vector<content>& inner_html
)
   : m_type(name)
   , m_attributes(attributes)
   , m_inner_html(inner_html)
{ }
cheap::element::element(const std::string_view name, const std::vector<content>& inner_html)
   : element(name, {}, inner_html)
{ }
cheap::element::element(const std::string_view name)
   : element(name, {}, {})
{ }

auto cheap::element::is_trivial() const -> bool
{
   if (m_inner_html.empty())
      return true;

   return m_inner_html.size() == 1 && std::holds_alternative<std::string>(m_inner_html.front());
}
auto cheap::element::get_trivial() const -> std::string
{
   if (m_inner_html.empty())
      return "";
   return std::get<std::string>(m_inner_html.front());
}

auto cheap::operator "" _att(const char* c_str, std::size_t size) -> attribute
{
   std::string str(c_str);
   const auto equal_pos = str.find('=');
   attribute result;
   if (equal_pos == std::string::npos)
   {
      result = bool_attribute{ .m_name = str };
   }
   else
   {
      result = string_attribute{
         .m_name = str.substr(0, equal_pos),
         .m_data = str.substr(equal_pos + 1)
      };
   }
   detail::assert_attrib_valid(result);
   return result;
}












auto cheap::detail::assert_attrib_valid(const attribute& attrib) -> void
{
   // Check if global boolean attributes are used correctly
   constexpr std::string_view bool_list[] = { "autofocus", "hidden", "itemscope" };
   const auto attrib_name = get_attribute_name(attrib);
   if (is_in(bool_list, attrib_name) && std::holds_alternative<bool_attribute>(attrib) == false)
   {
      throw cheap_exception{ CHEAP_FORMAT("attribute \"{}\" must be boolean. It is not!\n", attrib_name) };
   }

   // Check if global string attributes are used correctly
   constexpr std::string_view string_attrib_list[] = { "accesskey", "class", "id", "is", "itemid", "itemref", "itemscope", "itemtype", "lang", "nonce", "part", "role", "slot", "style", "tabindex", "title" };
   if(is_in(string_attrib_list, attrib_name) && std::holds_alternative<string_attribute>(attrib) == false)
   {
      throw cheap_exception{ CHEAP_FORMAT("attribute \"{}\" must be a string. It is not!\n", attrib_name) };
   }

   // Check if global enumerated attributes are used correctly
   if (attrib_name == "autocapitalize")
   {
      constexpr std::string_view valid_list[] = { "off", "on", "sentences", "words", "characters" };
      assert_string_enum_choice(attrib, valid_list);
   }
   else if (attrib_name == "contenteditable")
   {
      constexpr std::string_view valid_list[] = { "true", "false" };
      assert_string_enum_choice(attrib, valid_list);
   }
   else if (attrib_name == "dir")
   {
      constexpr std::string_view valid_list[] = { "ltr", "rtl", "auto" };
      assert_string_enum_choice(attrib, valid_list);
   }
   else if (attrib_name == "draggable")
   {
      constexpr std::string_view valid_list[] = { "true", "false" };
      assert_string_enum_choice(attrib, valid_list);
   }
   else if (attrib_name == "enterkeyhint")
   {
      constexpr std::string_view valid_list[] = { "enter", "done", "go", "next", "previous", "search", "send" };
      assert_string_enum_choice(attrib, valid_list);
   }
   else if (attrib_name == "inputmode")
   {
      constexpr std::string_view valid_list[] = { "none", "text", "decimal", "numeric", "tel", "search", "email", "url" };
      assert_string_enum_choice(attrib, valid_list);
   }
   else if (attrib_name == "spellcheck")
   {
      constexpr std::string_view valid_list[] = { "true", "false" };
      assert_string_enum_choice(attrib, valid_list);
   }
   else if (attrib_name == "translate")
   {
      constexpr std::string_view valid_list[] = { "yes", "no" };
      assert_string_enum_choice(attrib, valid_list);
   }
}


auto cheap::detail::assert_string_enum_choice(
   const attribute& attrib,
   const std::span<const std::string_view> choices
) -> void
{
   if (std::holds_alternative<string_attribute>(attrib) == false)
   {
      throw cheap_exception{ CHEAP_FORMAT("Attribute \"{}\" must be a string attribute. It's not!\n", get_attribute_name(attrib)) };
   }

   const auto attrib_name = get_attribute_name(attrib);
   if (is_in(choices, attrib_name) == false)
   {
      std::string choices_str;
      for (int i = 0; i < std::ssize(choices); ++i)
      {
         if (i > 0)
            choices_str += ", ";
         choices_str += choices[i];
      }
      throw cheap_exception{
         CHEAP_FORMAT(
            "Attribute is an enum. It must be one of [{}]. But it's \"{}\"!\n",
            choices_str,
            attrib_name
         )
      };
   }
}


auto cheap::detail::get_attribute_name(const attribute& attrib) -> std::string
{
   return std::visit(
      [](const auto& alternative) {return alternative.m_name; },
      attrib
   );
}


auto cheap::detail::is_in(const std::span<const std::string_view> choices, const std::string& value) -> bool
{
   for (const auto& test : choices)
   {
      if (test == value)
         return true;
   }
   return false;
}


auto cheap::detail::get_element_str_impl(
   const element& elem,
   const int indentation,
   const int current_level
) -> std::string
{
   if(elem.is_trivial())
   {
      return CHEAP_FORMAT(
         "{}<{}{}>{}</{}>",
         detail::get_spaces(current_level * indentation),
         elem.m_type,
         detail::get_attribute_str(elem),
         elem.get_trivial(),
         elem.m_type
      );
   }
   else
   {
      std::string result;
      result += CHEAP_FORMAT("<{}{}>", elem.m_type, detail::get_attribute_str(elem));
      result += '\n';
      result += detail::get_inner_html_str(elem, indentation, current_level);
      result += '\n';
      result += CHEAP_FORMAT("</{}>", elem.m_type);
      return result;
   }
}


auto cheap::detail::to_string(const attribute& attrib) -> std::string
{
   const auto visitor = []<is_alternative_c<attribute> T>(const T& alternative) -> std::string
   {
      if constexpr (std::same_as<T, bool_attribute>)
      {
         // The presence of a boolean string_attribute on an element represents the true
         // value, and the absence of the string_attribute represents the false value.
         // [...]]
         // The values "true" and "false" are not allowed on boolean attributes.
         // To represent a false value, the string_attribute has to be omitted altogether.
         // [https://html.spec.whatwg.org/dev/common-microsyntaxes.html#boolean-attributes]
         if (alternative.m_value == false)
            return {};
         return alternative.m_name;
      }
      else if constexpr (std::same_as<T, string_attribute>)
      {
         return CHEAP_FORMAT("{}=\"{}\"", alternative.m_name, alternative.m_data);
      }
   };
   return std::visit(visitor, attrib);
}


auto cheap::detail::get_attribute_str(const element& elem) -> std::string
{
   const auto visitor = []<typename T>(const T & alternative)
   {
      return to_string(alternative);
   };

   std::string result;
   for (const auto& x : elem.m_attributes)
   {
      result += ' ';
      result += std::visit(visitor, x);
   }
   return result;
}


auto cheap::detail::get_spaces(const int count) -> std::string
{
   std::string result;
   result.reserve(count);
   for (int i = 0; i < count; ++i)
      result += ' ';
   return result;
}


auto cheap::detail::get_element_str_impl(
   const std::string& elem,
   const int indentation,
   const int current_level
) -> std::string
{
   return CHEAP_FORMAT("{}{}", get_spaces(current_level * indentation), elem);
}


auto cheap::detail::get_inner_html_str(
   const element& elem,
   const int indentation,
   const int current_level
) -> std::string
{
   const auto content_visitor = [&]<typename T>(const T & alternative) -> std::string
   {
      return get_element_str_impl(alternative, indentation, current_level + 1);
   };

   return get_joined_visits(elem.m_inner_html, content_visitor, "\n");
}
#endif
