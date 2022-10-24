#include <string>
#include <vector>
#include <variant>
#include <format>
#include <optional>
#include <fstream>


namespace cheap
{
   namespace detail
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
   }

   struct autofocus : detail::boolean_attribute { };
   struct accesskey : detail::string_attribute { };
   enum class autocapitalize_state{off, on, sentences, words, characters};
   struct autocapitalize : detail::enumerated_attribute<autocapitalize_state>{ using enumerated_attribute::enumerated_attribute; };

   using attribute = std::variant<autofocus, accesskey, autocapitalize>;

   struct element;
   using content = std::variant<element, std::string>;


   struct arbitrary_element
   {
      std::string m_type;
      std::vector<attribute> m_attributes;
      std::vector<content> m_inner_html;
   };

   namespace detail
   {
      template<int>
      struct generic_element
      {
         std::vector<attribute> m_attributes;
         std::vector<content> m_inner_html;
      };
   }

   using html = detail::generic_element<__COUNTER__>;
   using base = detail::generic_element<__COUNTER__>;
   using head = detail::generic_element<__COUNTER__>;
   using link = detail::generic_element<__COUNTER__>;
   using meta = detail::generic_element<__COUNTER__>;
   using style = detail::generic_element<__COUNTER__>;
   using title = detail::generic_element<__COUNTER__>;
   using body = detail::generic_element<__COUNTER__>;
   using address = detail::generic_element<__COUNTER__>;
   using article = detail::generic_element<__COUNTER__>;
   using aside = detail::generic_element<__COUNTER__>;
   using footer = detail::generic_element<__COUNTER__>;
   using header = detail::generic_element<__COUNTER__>;
   using h1 = detail::generic_element<__COUNTER__>;
   using h2 = detail::generic_element<__COUNTER__>;
   using h3 = detail::generic_element<__COUNTER__>;
   using h4 = detail::generic_element<__COUNTER__>;
   using h5 = detail::generic_element<__COUNTER__>;
   using h6 = detail::generic_element<__COUNTER__>;
   using main = detail::generic_element<__COUNTER__>;
   using nav = detail::generic_element<__COUNTER__>;
   using section = detail::generic_element<__COUNTER__>;
   using blockquote = detail::generic_element<__COUNTER__>;
   using dd = detail::generic_element<__COUNTER__>;
   using div = detail::generic_element<__COUNTER__>;
   using dl = detail::generic_element<__COUNTER__>;
   using dt = detail::generic_element<__COUNTER__>;
   using figcaption = detail::generic_element<__COUNTER__>;
   using figure = detail::generic_element<__COUNTER__>;
   using hr = detail::generic_element<__COUNTER__>;
   using menu = detail::generic_element<__COUNTER__>;
   using ol = detail::generic_element<__COUNTER__>;
   using p = detail::generic_element<__COUNTER__>;
   using pre = detail::generic_element<__COUNTER__>;
   using ul = detail::generic_element<__COUNTER__>;
   using a = detail::generic_element<__COUNTER__>;
   using abbr = detail::generic_element<__COUNTER__>;
   using b = detail::generic_element<__COUNTER__>;
   using bdi = detail::generic_element<__COUNTER__>;
   using bdo = detail::generic_element<__COUNTER__>;
   using cite = detail::generic_element<__COUNTER__>;
   using code = detail::generic_element<__COUNTER__>;
   using data = detail::generic_element<__COUNTER__>;
   using dfn = detail::generic_element<__COUNTER__>;
   using em = detail::generic_element<__COUNTER__>;
   using i = detail::generic_element<__COUNTER__>;
   using kdb = detail::generic_element<__COUNTER__>;
   using mark = detail::generic_element<__COUNTER__>;
   using q = detail::generic_element<__COUNTER__>;
   using rp = detail::generic_element<__COUNTER__>;
   using rt = detail::generic_element<__COUNTER__>;
   using ruby = detail::generic_element<__COUNTER__>;
   using s = detail::generic_element<__COUNTER__>;
   using samp = detail::generic_element<__COUNTER__>;
   using small = detail::generic_element<__COUNTER__>;
   using span = detail::generic_element<__COUNTER__>;
   using strong = detail::generic_element<__COUNTER__>;
   using sub = detail::generic_element<__COUNTER__>;
   using sup = detail::generic_element<__COUNTER__>;
   using time = detail::generic_element<__COUNTER__>;
   using u = detail::generic_element<__COUNTER__>;
   using var = detail::generic_element<__COUNTER__>;
   using wbr = detail::generic_element<__COUNTER__>;
   using area = detail::generic_element<__COUNTER__>;
   using audio = detail::generic_element<__COUNTER__>;
   using img = detail::generic_element<__COUNTER__>;
   using map = detail::generic_element<__COUNTER__>;
   using track = detail::generic_element<__COUNTER__>;
   using video = detail::generic_element<__COUNTER__>;
   using embed = detail::generic_element<__COUNTER__>;
   using iframe = detail::generic_element<__COUNTER__>;
   using object = detail::generic_element<__COUNTER__>;
   using picture = detail::generic_element<__COUNTER__>;
   using portal = detail::generic_element<__COUNTER__>;
   using source = detail::generic_element<__COUNTER__>;
   using svg = detail::generic_element<__COUNTER__>;
   using math = detail::generic_element<__COUNTER__>;
   using canvas = detail::generic_element<__COUNTER__>;
   using noscript = detail::generic_element<__COUNTER__>;
   using script = detail::generic_element<__COUNTER__>;
   using del = detail::generic_element<__COUNTER__>;
   using ins = detail::generic_element<__COUNTER__>;
   using caption = detail::generic_element<__COUNTER__>;
   using col = detail::generic_element<__COUNTER__>;
   using colgroup = detail::generic_element<__COUNTER__>;
   using stable = detail::generic_element<__COUNTER__>;
   using tbody = detail::generic_element<__COUNTER__>;
   using td = detail::generic_element<__COUNTER__>;
   using tfoot = detail::generic_element<__COUNTER__>;
   using th = detail::generic_element<__COUNTER__>;
   using thead = detail::generic_element<__COUNTER__>;
   using tr = detail::generic_element<__COUNTER__>;
   using button = detail::generic_element<__COUNTER__>;
   using datalist = detail::generic_element<__COUNTER__>;
   using fieldset = detail::generic_element<__COUNTER__>;
   using form = detail::generic_element<__COUNTER__>;
   using input = detail::generic_element<__COUNTER__>;
   using label = detail::generic_element<__COUNTER__>;
   using legend = detail::generic_element<__COUNTER__>;
   using meter = detail::generic_element<__COUNTER__>;
   using optgroup = detail::generic_element<__COUNTER__>;
   using option = detail::generic_element<__COUNTER__>;
   using progress = detail::generic_element<__COUNTER__>;
   using select = detail::generic_element<__COUNTER__>;
   using textarea = detail::generic_element<__COUNTER__>;
   using details = detail::generic_element<__COUNTER__>;
   using dialog = detail::generic_element<__COUNTER__>;
   using summary = detail::generic_element<__COUNTER__>;
   using slot = detail::generic_element<__COUNTER__>;
   using template_ = detail::generic_element<__COUNTER__>;


   struct element : std::variant<arbitrary_element, html, base, head, link, meta, style, title, body, address, article, aside, footer, header, h1, h2, h3, h4, h5, h6, main, nav, section, blockquote, dd, div, dl, dt, figcaption, figure, hr, menu, ol, p, pre, ul, a, abbr, b, bdi, bdo, cite, code, data, dfn, em, i, kdb, mark, q, rp, rt, ruby, s, samp, small, span, strong, sub, sup, time, u, var, wbr, area, audio, img, map, track, video, embed, iframe, object, picture, portal, source, svg, math, canvas, noscript, script, del, ins, caption, col, colgroup, stable, tbody, td, tfoot, th, thead, tr, button, datalist, fieldset, form, input, label, legend, meter, optgroup, option, progress, select, textarea, details, dialog, summary, slot, template_>
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
            if (alternative.m_inner_html.size() != 1 || !std::holds_alternative<std::string>(alternative.m_inner_html.front()))
               return std::nullopt;
            return std::get<std::string>(alternative.m_inner_html.front());
         };
         return std::visit(visitor, *this);
      }


      [[nodiscard]] auto get_element_name() const -> std::string
      {
         struct visitor {
            auto operator()(const arbitrary_element& el) -> std::string { return el.m_type; }

            auto operator()(const html&) const -> std::string { return "html"; }
            auto operator()(const base&) const -> std::string { return "base"; }
            auto operator()(const head&) const -> std::string { return "head"; }
            auto operator()(const link&) const -> std::string { return "link"; }
            auto operator()(const meta&) const -> std::string { return "meta"; }
            auto operator()(const style&) const -> std::string { return "style"; }
            auto operator()(const title&) const -> std::string { return "title"; }
            auto operator()(const body&) const -> std::string { return "body"; }
            auto operator()(const address&) const -> std::string { return "address"; }
            auto operator()(const article&) const -> std::string { return "article"; }
            auto operator()(const aside&) const -> std::string { return "aside"; }
            auto operator()(const footer&) const -> std::string { return "footer"; }
            auto operator()(const header&) const -> std::string { return "header"; }
            auto operator()(const h1&) const -> std::string { return "h1"; }
            auto operator()(const h2&) const -> std::string { return "h2"; }
            auto operator()(const h3&) const -> std::string { return "h3"; }
            auto operator()(const h4&) const -> std::string { return "h4"; }
            auto operator()(const h5&) const -> std::string { return "h5"; }
            auto operator()(const h6&) const -> std::string { return "h6"; }
            auto operator()(const main&) const -> std::string { return "main"; }
            auto operator()(const nav&) const -> std::string { return "nav"; }
            auto operator()(const section&) const -> std::string { return "section"; }
            auto operator()(const blockquote&) const -> std::string { return "blockquote"; }
            auto operator()(const dd&) const -> std::string { return "dd"; }
            auto operator()(const div&) const -> std::string { return "div"; }
            auto operator()(const dl&) const -> std::string { return "dl"; }
            auto operator()(const dt&) const -> std::string { return "dt"; }
            auto operator()(const figcaption&) const -> std::string { return "figcaption"; }
            auto operator()(const figure&) const -> std::string { return "figure"; }
            auto operator()(const hr&) const -> std::string { return "hr"; }
            auto operator()(const menu&) const -> std::string { return "menu"; }
            auto operator()(const ol&) const -> std::string { return "ol"; }
            auto operator()(const p&) const -> std::string { return "p"; }
            auto operator()(const pre&) const -> std::string { return "pre"; }
            auto operator()(const ul&) const -> std::string { return "ul"; }
            auto operator()(const a&) const -> std::string { return "a"; }
            auto operator()(const abbr&) const -> std::string { return "abbr"; }
            auto operator()(const b&) const -> std::string { return "b"; }
            auto operator()(const bdi&) const -> std::string { return "bdi"; }
            auto operator()(const bdo&) const -> std::string { return "bdo"; }
            auto operator()(const cite&) const -> std::string { return "cite"; }
            auto operator()(const code&) const -> std::string { return "code"; }
            auto operator()(const data&) const -> std::string { return "data"; }
            auto operator()(const dfn&) const -> std::string { return "dfn"; }
            auto operator()(const em&) const -> std::string { return "em"; }
            auto operator()(const i&) const -> std::string { return "i"; }
            auto operator()(const kdb&) const -> std::string { return "kdb"; }
            auto operator()(const mark&) const -> std::string { return "mark"; }
            auto operator()(const q&) const -> std::string { return "q"; }
            auto operator()(const rp&) const -> std::string { return "rp"; }
            auto operator()(const rt&) const -> std::string { return "rt"; }
            auto operator()(const ruby&) const -> std::string { return "ruby"; }
            auto operator()(const s&) const -> std::string { return "s"; }
            auto operator()(const samp&) const -> std::string { return "samp"; }
            auto operator()(const small&) const -> std::string { return "small"; }
            auto operator()(const span&) const -> std::string { return "span"; }
            auto operator()(const strong&) const -> std::string { return "strong"; }
            auto operator()(const sub&) const -> std::string { return "sub"; }
            auto operator()(const sup&) const -> std::string { return "sup"; }
            auto operator()(const time&) const -> std::string { return "time"; }
            auto operator()(const u&) const -> std::string { return "u"; }
            auto operator()(const var&) const -> std::string { return "var"; }
            auto operator()(const wbr&) const -> std::string { return "wbr"; }
            auto operator()(const area&) const -> std::string { return "area"; }
            auto operator()(const audio&) const -> std::string { return "audio"; }
            auto operator()(const img&) const -> std::string { return "img"; }
            auto operator()(const map&) const -> std::string { return "map"; }
            auto operator()(const track&) const -> std::string { return "track"; }
            auto operator()(const video&) const -> std::string { return "video"; }
            auto operator()(const embed&) const -> std::string { return "embed"; }
            auto operator()(const iframe&) const -> std::string { return "iframe"; }
            auto operator()(const object&) const -> std::string { return "object"; }
            auto operator()(const picture&) const -> std::string { return "picture"; }
            auto operator()(const portal&) const -> std::string { return "portal"; }
            auto operator()(const source&) const -> std::string { return "source"; }
            auto operator()(const svg&) const -> std::string { return "svg"; }
            auto operator()(const math&) const -> std::string { return "math"; }
            auto operator()(const canvas&) const -> std::string { return "canvas"; }
            auto operator()(const noscript&) const -> std::string { return "noscript"; }
            auto operator()(const script&) const -> std::string { return "script"; }
            auto operator()(const del&) const -> std::string { return "del"; }
            auto operator()(const ins&) const -> std::string { return "ins"; }
            auto operator()(const caption&) const -> std::string { return "caption"; }
            auto operator()(const col&) const -> std::string { return "col"; }
            auto operator()(const colgroup&) const -> std::string { return "colgroup"; }
            auto operator()(const stable&) const -> std::string { return "stable"; }
            auto operator()(const tbody&) const -> std::string { return "tbody"; }
            auto operator()(const td&) const -> std::string { return "td"; }
            auto operator()(const tfoot&) const -> std::string { return "tfoot"; }
            auto operator()(const th&) const -> std::string { return "th"; }
            auto operator()(const thead&) const -> std::string { return "thead"; }
            auto operator()(const tr&) const -> std::string { return "tr"; }
            auto operator()(const button&) const -> std::string { return "button"; }
            auto operator()(const datalist&) const -> std::string { return "datalist"; }
            auto operator()(const fieldset&) const -> std::string { return "fieldset"; }
            auto operator()(const form&) const -> std::string { return "form"; }
            auto operator()(const input&) const -> std::string { return "input"; }
            auto operator()(const label&) const -> std::string { return "label"; }
            auto operator()(const legend&) const -> std::string { return "legend"; }
            auto operator()(const meter&) const -> std::string { return "meter"; }
            auto operator()(const optgroup&) const -> std::string { return "optgroup"; }
            auto operator()(const option&) const -> std::string { return "option"; }
            auto operator()(const progress&) const -> std::string { return "progress"; }
            auto operator()(const select&) const -> std::string { return "select"; }
            auto operator()(const textarea&) const -> std::string { return "textarea"; }
            auto operator()(const details&) const -> std::string { return "details"; }
            auto operator()(const dialog&) const -> std::string { return "dialog"; }
            auto operator()(const summary&) const -> std::string { return "summary"; }
            auto operator()(const slot&) const -> std::string { return "slot"; }
            auto operator()(const template_&) const -> std::string { return "template_"; }
         };
         return std::visit(visitor{}, *this);
      }
   };


   namespace detail
   {
      template<typename T>
      struct attribute_name { };
      template<> struct attribute_name<autofocus> { constexpr static inline std::string_view value = "autofocus"; };
      template<> struct attribute_name<accesskey> { constexpr static inline std::string_view value = "accesskey"; };
      template<> struct attribute_name<autocapitalize> { constexpr static inline std::string_view value = "autocapitalize"; };
      template<typename T> constexpr inline static std::string_view attribute_name_v = attribute_name<T>::value;

      [[nodiscard]] auto to_string(const autocapitalize_state& state) -> std::string
      {
         switch (state)
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
         const auto visitor = []<typename T>(const T & alternative)
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


      [[nodiscard]] auto get_inner_html_str(const element& variant, const int level) -> std::string
      {
         const auto outer_visitor = [&](const auto& element) -> std::string
         {
            const auto content_visitor = [&]<typename T>(const T & alternative) -> std::string
            {
               return get_element_str(alternative, level + 1);
            };

            return get_joined_visits(element.m_inner_html, content_visitor, "\n");
         };

         return std::visit(outer_visitor, variant);
      }
   }


   [[nodiscard]] auto get_element_str(const element& elem, const int level = 0) -> std::string
   {
      if(const auto x = elem.get_trivial_content(); x.has_value())
      {
         return std::format(
            "{}<{}>{}</{}>",
            detail::get_spaces(level * detail::indent),
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
         result += detail::get_inner_html_str(elem, level);
         result += '\n';
         result += std::format("</{}>", elem.get_element_name());
         return result;
      }
   }

   // std::string operator "" _att(const char* str, std::size_t)
   // {
   //    int stop = 0;
   //    return "";
   // }

} // namespace cheap


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
   // cheap::

   using namespace cheap;

   // "abc"_att;

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
