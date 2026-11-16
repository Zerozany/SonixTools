_Pragma("once");
#include <type_traits>
#include <vector>
#include "MeasureConfig.hpp"

#if defined(_WIN32) && defined(_MSC_VER)
    #ifdef SONIXTOOLS_BUILDING
        #define SONIX_DLL __declspec(dllexport)
    #else
        #define SONIX_DLL __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define SONIX_DLL __attribute__((visibility("default")))
#else
    #define SONIX_DLL
#endif

#define MeasureMethod(_Namespace, _MeasureType) auto measure##_MeasureType(const _Namespace::_MeasureType& _measureType, const std::vector<double>& _args) noexcept -> double

class SONIX_DLL MeasureKits
{
public:
    explicit MeasureKits(/*Object* = _parent*/);

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
    if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, Department::Obstetrics>)
    {
        return this->measureObstetrics(std::forward<T>(_measureType), std::vector<double>{static_cast<double>(std::forward<Args>(_args))...});
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, Department::FetalWeight>)
    {
        return this->measureFetalWeight(std::forward<T>(_measureType), std::vector<double>{static_cast<double>(std::forward<Args>(_args))...});
    }
    return double{};
}
