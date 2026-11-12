_Pragma("once");
#include <type_traits>
#include <vector>
#include <print>
#include "MeasureKitsPrivate.h"

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
    MeasureKitsPrivate* m_measureKitsPrivate{nullptr};
};

template <typename T, typename... Args>
inline auto MeasureKits::measure(T&& _measureType, Args&&... args) noexcept -> double
{
    double result{};
    try
    {
        result = this->m_measureKitsPrivate->measurePrivate(std::forward<T>(_measureType), std::vector<double>{static_cast<double>(std::forward<Args>(args))...});
    }
    catch (const std::exception& _e)
    {
        std::println("measure error:{}", _e.what());
    }
    catch (...)
    {
        std::println("measure error: unknown");
    }
    return result;
}
