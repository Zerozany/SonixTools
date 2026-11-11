_Pragma("once");
#include <type_traits>
#include <vector>
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
    auto measureFurther(const Department::Obstetrics& _measureType, const std::vector<double>& _params) noexcept -> double;

    auto measureFurther(const Department::FetalWeight& _measureType, const std::vector<double>& _params) noexcept -> double;
};

template <typename T, typename... Args>
inline auto MeasureKits::measure(T&& _measureType, Args&&... args) noexcept -> double
{
    return this->measureFurther(std::forward<T>(_measureType), std::vector<double>{static_cast<double>(std::forward<Args>(args))...});
}
