_Pragma("once");
#include "MeasureConfig.hpp"
#include <vector>
#include <toml++/toml.hpp>

class MeasureKits;

class MeasureKitsPrivate
{
    friend class MeasureKits;

public:
    explicit(true) MeasureKitsPrivate(/* args */);
    ~MeasureKitsPrivate() noexcept = default;

private:
    auto measurePrivate(const Department::Obstetrics& _measureType, const std::vector<double>& _params) noexcept -> double;

    auto measurePrivate(const Department::FetalWeight& _measureType, const std::vector<double>& _params) noexcept -> double;

private:
    auto init() -> void;

private:
    toml::v3::ex::parse_result m_measureTable{};
};
