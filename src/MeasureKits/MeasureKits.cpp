#include "MeasureKits.h"
#include <magic_enum/magic_enum.hpp>
#include <cmrc/cmrc.hpp>
#include <toml++/toml.hpp>
#include "exprtk.hpp"
#include <print>

CMRC_DECLARE(SonixToolsR);

namespace Private
{
    static toml::v3::ex::parse_result measureTable{};

    static auto calculate{[](const std::string& _formula, const std::vector<double>& _params) -> double {
        exprtk::symbol_table<double> formulaTable{};
        for (std::size_t i{}; i < _params.size(); ++i)
        {
            formulaTable.add_variable("param_" + std::to_string(i), const_cast<double&>(_params[i]), true);
        }
        exprtk::expression<double> expression{};
        expression.register_symbol_table(formulaTable);
        exprtk::parser<double> parser{};
        if (!parser.compile(_formula, expression))
        {
            std::println("Parser error:{}", parser.error());
            return double{};
        }
        return expression.value();
    }};
}  // namespace Private

MeasureKits::MeasureKits()
{
    auto measureFile{cmrc::SonixToolsR::get_filesystem().open("config/measure.toml")};
    Private::measureTable = toml::parse(std::string_view{measureFile.begin(), measureFile.end()});
}

MeasureKits::~MeasureKits() noexcept
{
}

auto MeasureKits::measureObstetrics(const Department::Obstetrics& _measureType, const std::vector<double>& _args) noexcept -> double
{
    auto table{Private::measureTable[magic_enum::enum_type_name<Department::Obstetrics>()].as_table()};
    if (!table)
    {
        std::println("Formula table reading failed!");
        return double{};
    }
    return Private::calculate(std::string{(*table)[magic_enum::enum_name(_measureType)].value_or<std::string_view>(std::string_view{})}, _args);
}

auto MeasureKits::measureFetalWeight(const Department::FetalWeight& _measureType, const std::vector<double>& _args) noexcept -> double
{
    auto table{Private::measureTable[magic_enum::enum_type_name<Department::FetalWeight>()].as_table()};
    if (!table)
    {
        std::println("Formula table reading failed!");
        return double{};
    }
    return std::pow(10, Private::calculate(std::string{(*table)[magic_enum::enum_name(_measureType)].value_or<std::string_view>(std::string_view{})}, _args));
}
