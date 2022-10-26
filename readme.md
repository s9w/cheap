# **cheap** (C++ HTML Element Apparator) :heavy_dollar_sign::heavy_dollar_sign::heavy_dollar_sign:

**cheap** is a C++ library to create html strings. TL;DR:
```c++
const std::string elem_str = get_element_str(div(span("first"), img("src=test.jpg"_att)));
```
:arrow_double_down: output: :arrow_double_down:

```html
<div>
    <span>first</span>
    <img src="test.jpg" />
</div>
```

I needed this for a project, maybe others have use for some server-side rendering or god knows what.

- It requires C++20, runs on MSVC, clang and gcc ([godbolt](https://godbolt.org/z/bcPjxG1Te))
- It's a single header with no external includes. The implementation hidden behind the `CHEAP_IMPL` macro. Define that in **one** translation unit before you include it, so
```c++
#define CHEAP_IMPL
#include <cheap.h>
```
- The indentation can be adjusted as the last parameter of `get_element_str(element, int indentation=4)`
- By default, **cheap** uses `std::format()`. To use [`fmt`](https://github.com/fmtlib/fmt) instead, make sure it's included before `cheap.h` and `#define CHEAP_USE_FMT`
- *to apparate*: originates from latin and means “to appear”

Attributes can be created with the `_att` literal operator. For boolean attributes, just enter the name (`"hidden"_att`). For string attributes, write with equation sign (`"id=container"_att`). You can also just create `bool_attribute` or `string_attribute` objects. They're straightforward aggregates:
```c++
struct bool_attribute {
   std::string m_name;
   bool        m_value = true;
};
struct string_attribute {
   std::string m_name;
   std::string m_value;
};
```

There are two interfaces of creating the elements:

## First interface: Convenient template interface
This involves heavily templated functions. That's convenient, just be aware that this might impact compile times depending on use.

`create_element(<element name>, [<attributes>], [<conents>])` accepts the element name as the first parameter. The function is variadic, you can shovel attributes and sub-elements into it at will. The sub-elements can be other elements, or a plain `std::string`.

For all HTML spec elements (from [here](https://developer.mozilla.org/en-US/docs/Web/HTML/Element)), there is an equally named function. So `div(...)` is just a shortcut to `create_element("div, ...)`. Note that due to C++ limitations, the function for the `template` element is called `template_`.

```c++
auto elem = div("Hello world");
// <div>Hello world</div>

auto elem = div("data-cool=true"_att, "awesome"_att, "Attributes!");
// <div data-cool="true" awesome>Attributes!</div>

auto elem = div("class=flex"_att, span("nested"), span("content"));
// <div class="flex">
//    <span>nested</span>
//    <span>content</span>
// </div>

// Since you can nowerdays write your own elements
auto elem = create_element("my_elem", "oof"); // <my_elem>oof</my_elem>
```

## Second interface:  `element` type
An `element` is basically:
```c++
struct element
{
   std::string m_name;
   std::vector<attribute> m_attributes;
   std::vector<content> m_inner_html;

   element(const std::string_view name, std::vector<attribute> attributes, std::vector<content> inner_html)
   element(const std::string_view name,                                    std::vector<content> inner_html)
   element(const std::string_view name)
}
```

With `using content = std::variant<element, std::string>`. This interface is a little less magic and easier to use of you use code to generate your hierarchy.

Usage:
```c++
element elem{ "div", {"cool=true"_att},
   {
      element{"span", {"first"}},
      element{"span", {"second"}}
   }
};
```

Also feel free to just set the members yourself (everything is public).

## Parallel elements
There's also an overload that accepts a vector of elements. It gets rendered just as you would expect.
```c++
auto get_element_str(const element& elem,                  const int indentation = 4) -> std::string;
auto get_element_str(const std::vector<element>& elements, const int indentation = 4) -> std::string;
```

```c++
const std::string elem_str = get_element_str(
   { img("src=a.jpg"_att), img("src=b.jpg"_att) }
);

// <img src="a.jpg" />
// <img src="b.jpg" />
```

## Performance; string ref output
I did some rudimentary profiling and things are still fast with a million elements. The first pain points are allocations of the vectors etc.

To alleviate memory allocation worries at least to some degree, there's an alternative set of stringification functions that write into a `std::string&`. That target string can be preallocated by the user, or re-used between changes to avoid most string allocations.

```c++
auto write_element_str(const element& elem,                  std::string& output, const int indentation = 4) -> void;
auto write_element_str(const std::vector<element>& elements, std::string& output, const int indentation = 4) -> void;
```

## Error handling
The HTML spec constraints certain attributes
- There are enum attributes which have a set of allowed values. For example, `dir` must be one of `ltr`, `rtl` or `auto`
- There are boolean attributes which can't have a value (`autofocus`, `hidden` and `itemscope`)
- There are string attributes which must have a value (For example `id`)

Other checks:
- Self-closing tags (`<area>`, `<base>`, `<br>`, `<col>`, `<embed>`, `<hr>`, `<img>`, `<input>`, `<link>`, `<meta>`, `<source>`, `<track>` and `<wbr>`) can't have sub-elements
- `create_element()` must get a name as the first parameter

If any of that is violated, a `cheap_exception` is thrown with a meaningful error message.

## Configuration
By default, **cheap** uses [`std::format()`](https://en.cppreference.com/w/cpp/utility/format/format). To use [`fmt`](https://github.com/fmtlib/fmt) instead, make sure it's included before `cheap.h` and `#define CHEAP_USE_FMT`.

## Compatibility with inja, mustache, Handlebars etc
There's a range of popular libraries ([inja](https://github.com/pantor/inja), [mustache](https://mustache.github.io/), [handlebars](https://handlebarsjs.com/)) that fill strings that contain placeholders like `{{ this }}` with structured content - often from json or other sources. Depending on your pipeline, **cheap** might replace the need for this.

But maybe it doesn't. I'm just here to tell you that such strings "survives" **cheap**. So you can use them for attributes, element names and string contents and they come out on the other side just fine - ready to be used by such libraries.
