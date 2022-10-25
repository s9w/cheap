# **cheap** (C++ HTML Element Apparator) :heavy_dollar_sign::heavy_dollar_sign::heavy_dollar_sign:

**cheap** creates html string from C++. TL;DR:
```c++
const std::string elem_str = get_element_str(div(span("first"), img("src=test.jpg"_att)));
```

:arrow_double_down: :arrow_double_down:

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

Attributes can be created with the `_att` literal operator. For boolean attributes, just enter the name (`"hidden"_att`). For string attributes, write with equation sign (`"id=container"_att`). You can also just create a `bool_attribute` or `string_attribute` type. They're trivial aggregates:
```c++
struct bool_attribute {
   bool m_value = true;
   std::string m_name;
};
struct string_attribute {
   std::string m_name;
   std::string m_data;
};
```

There are two interfaces of creating the elements:

## First interface: Convenient template interface
This involves heavily templated functions. That's convenient, just be aware that this might impact compile times depending on use.

There's `create_element(<element name>, [<attributes>], [<conents>])` which accepts the element name as the first parameter. The function is variadic, you can shovel attributes and contents into it at will.

The content (children) of an element can be other elements, or a plain `std::string`.

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
   std::string m_type;
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
Note that there's also an overload that accepts multiple elements. It gets rendered just as you would expect.
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

To alleviate memory allocation worries at least to some degree, there's an alternative set of stringification functions that wrote into a `std::string&`. That target string can be preallocated by the user, or re-used between changes to avoid most string allocations.

```c++
auto write_element_str(const element& elem,                  std::string& output, const int indentation = 4) -> void;
auto write_element_str(const std::vector<element>& elements, std::string& output, const int indentation = 4) -> void;
```

## Error handling
The HTML spec constraints certain attributes
- There are enum attributes which have a set of allowed values. For example, `dir` must be one of `ltr`, `rtl` or `auto`
- There are bollean attributes which can't have a value (`autofocus`, `hidden` and `itemscope`)
- There are string attributes which must have a value (For example `id`)

Also there's self-closing tags (`<area>`, `<base>`, `<br>`, `<col>`, `<embed>`, `<hr>`, `<img>`, `<input>`, `<link>`, `<meta>`, `<source>`, `<track>` and `<wbr>`). Those can't have sub-elements.

If any of that is violated, a `cheap_exception` is thrown with a meaningful error message.

## Configuration
By default, **cheap** uses `std::format()`. To use [`fmt`](https://github.com/fmtlib/fmt) instead, make sure it's included before `cheap.h` and `#define CHEAP_USE_FMT`.
