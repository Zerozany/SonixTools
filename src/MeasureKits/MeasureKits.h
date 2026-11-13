_Pragma("once");
#include <type_traits>
#include <vector>
#include "MeasureConfig.hpp"

#if defined(__ANDROID__)
    #include <android/log.h>
#endif

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

#define MeasureMethod(_Namespace, _MeasureType) auto measure##_MeasureType(const _Namespace::_MeasureType& _measureType, const std::vector<double>& _args) noexcept -> double

class Sonix_API MeasureKits
{
public:
    explicit(true) MeasureKits(/*Object* = _parent*/);

    ~MeasureKits() noexcept;

    MeasureKits(const MeasureKits&)                = delete;
    MeasureKits& operator=(const MeasureKits&)     = delete;
    MeasureKits(MeasureKits&&) noexcept            = delete;
    MeasureKits& operator=(MeasureKits&&) noexcept = delete;

public:
    template <typename T, typename... Args>
    auto measure(T&& _measureType, Args&&... _args) noexcept -> double;

private:
    MeasureMethod(Department, Obstetrics);

    MeasureMethod(Department, FetalWeight);
};

template <typename T, typename... Args>
inline auto MeasureKits::measure(T&& _measureType, Args&&... _args) noexcept -> double
{
    if constexpr (std::is_same_v<std::remove_cvref_t<T>, Department::Obstetrics>)
    {
        return this->measureObstetrics(std::forward<T>(_measureType), std::vector<double>{static_cast<double>(std::forward<Args>(_args))...});
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<T>, Department::FetalWeight>)
    {
        return this->measureFetalWeight(std::forward<T>(_measureType), std::vector<double>{static_cast<double>(std::forward<Args>(_args))...});
    }
    return double{};
}
