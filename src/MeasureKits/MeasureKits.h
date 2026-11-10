_Pragma("once");
#include <type_traits>
#include <toml++/toml.hpp>

#include "MeasureConfig.hpp"

#if defined(_WIN32) && defined(_MSC_VER)
    #ifdef SonixTools
        #define Sonix_API __declspec(dllexport)
    #else
        #define Sonix_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define Sonix_API __attribute__((visibility("default")))
#else
    #define Sonix_API
#endif

class Sonix_API MeasureKits
{
public:
    static auto instance() noexcept -> MeasureKits*;

    ~MeasureKits() noexcept = default;

public:
    template <typename T, typename... Args>
    auto measure(T&& _measureType, Args&&... args) noexcept -> double;

private:
    explicit(true) MeasureKits();

    auto init() noexcept -> void;

private:
    auto measureObstetrics(const Department::Obstetrics& _measureType, double _param) noexcept -> double;

private:
    toml::v3::ex::parse_result m_measureTable{};
};

template <typename T, typename... Args>
inline auto MeasureKits::measure(T&& _measureType, Args&&... args) noexcept -> double
{
    if constexpr (std::is_same_v<T, Department::Obstetrics>)
    {
        return this->measureObstetrics(std::forward<T>(_measureType), std::forward<Args>(args)...);
    }
    return double{};
}
