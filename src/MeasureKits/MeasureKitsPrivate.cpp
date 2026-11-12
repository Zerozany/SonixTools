#include "MeasureKitsPrivate.h"
#include <magic_enum/magic_enum.hpp>
#include <cmrc/cmrc.hpp>
#include "exprtk.hpp"
#include <print>

CMRC_DECLARE(SonixToolsR);

namespace Private
{
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

MeasureKitsPrivate::MeasureKitsPrivate()
{
    std::invoke(&MeasureKitsPrivate::init, this);
}

auto MeasureKitsPrivate::init() -> void
{
    auto measureFile{cmrc::SonixToolsR::get_filesystem().open("config/measure.toml")};
    this->m_measureTable = toml::parse(std::string_view{measureFile.begin(), measureFile.end()});
}

auto MeasureKitsPrivate::measurePrivate(const Department::Obstetrics& _measureType, const std::vector<double>& _params) noexcept -> double
{
    auto table{this->m_measureTable[magic_enum::enum_type_name<Department::Obstetrics>()].as_table()};
    if (!table)
    {
        std::println("Formula table reading failed!");
        return double{};
    }
    return Private::calculate(std::string{(*table)[magic_enum::enum_name(_measureType)].value_or<std::string_view>(std::string_view{})}, _params);
}

auto MeasureKitsPrivate::measurePrivate(const Department::FetalWeight& _measureType, const std::vector<double>& _params) noexcept -> double
{
    auto table{this->m_measureTable[magic_enum::enum_type_name<Department::FetalWeight>()].as_table()};
    if (!table)
    {
        std::println("Formula table reading failed!");
        return double{};
    }
    return std::pow(10, Private::calculate(std::string{(*table)[magic_enum::enum_name(_measureType)].value_or<std::string_view>(std::string_view{})}, _params));
}
