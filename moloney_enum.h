#include <iostream>
#include <array>
#include <string_view>
#include <type_traits>
#include <concepts>

template <typename T>
concept EnumType = std::is_enum_v<T>;

template <EnumType T>
std::string_view get_enum_as_string(T value);

#define DECLARE_ENUM(NAME, ...)                                               \
    enum NAME                                                                 \
    {                                                                         \
        __VA_ARGS__,                                                          \
        NAME##_COUNT                                                          \
    };                                                                        \
                                                                              \
    namespace                                                                 \
    {                                                                         \
        constexpr std::array<std::string_view, NAME##_COUNT> NAME##_strings = \
            []() {                                                                                      \
    std::string_view values = #__VA_ARGS__;                                                             \
    std::array<std::string_view, NAME##_COUNT> NAME##_strings = {};                                     \
    size_t start = 0, end = 0;                                                                          \
    bool new_word = false;                                                                              \
    size_t value_count = 0;                                                                             \
    for (size_t i = 0; i < values.size(); ++i) {                                                        \
        if (values[i] == ',') {                                                                         \
            end = i;                                                                                    \
            new_word = true;                                                                            \
            std::string_view prefix = start > 0 ? values.substr(0, start) : "";                         \
            std::string_view suffix = end < values.size() ? values.substr(end, values.size()) : "";     \
            std::string_view to_add = values;                                                           \
            to_add.remove_prefix(start);                                                                \
            to_add.remove_suffix(to_add.size() - to_add.find(suffix));                                  \
            NAME##_strings[value_count] = to_add;                                                       \
            ++value_count;                                                                              \
            continue;                                                                                   \
        }                                                                                               \
        if (values[i] == ' ') continue;                                                                 \
        if (new_word) {                                                                                 \
            start = i;                                                                                  \
            new_word = false;                                                                           \
        }                                                                                               \
    }                                                                                                   \
    std::string_view prefix = values.substr(0, start);                                                  \
    std::string_view to_add = values;                                                                   \
    to_add.remove_prefix(to_add.find(prefix) + prefix.size());                                          \
    NAME##_strings[value_count] = to_add;                                                               \
    return NAME##_strings; }();                                                       \
    }; /* namespace */                                                        \
    template <>                                                               \
    std::string_view get_enum_as_string<NAME>(NAME value)                     \
    {                                                                         \
        return NAME##_strings[static_cast<int>(value)];                       \
    }
