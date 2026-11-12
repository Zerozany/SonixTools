_Pragma("once");
#include <type_traits>
#include <vector>
#include <print>
#include <any>
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

class MeasureKitsPrivate;

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
    auto measure(T&& _measureType, Args&&... args) noexcept -> double;

private:
    auto measurePrivate(const std::any& _measureType, const std::vector<double>& _args) noexcept -> double;

private:
    MeasureKitsPrivate* m_measureKitsPrivate{nullptr};
};

template <typename T, typename... Args>
inline auto MeasureKits::measure(T&& _measureType, Args&&... args) noexcept -> double
{
    static_assert(std::is_same_v<T, Department::Obstetrics> || std::is_same_v<T, Department::FetalWeight>, "Unsupported _measureType");
    return this->measurePrivate(std::any{std::forward<T>(_measureType)}, std::vector<double>{static_cast<double>(std::forward<Args>(args))...});
}
