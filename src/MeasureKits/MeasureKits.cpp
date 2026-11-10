#include "MeasureKits.h"
#include <magic_enum/magic_enum.hpp>
#include <cmrc/cmrc.hpp>
#include "exprtk.hpp"
#include <print>

CMRC_DECLARE(SonixToolsR);

auto MeasureKits::instance() noexcept -> MeasureKits*
{
    static MeasureKits* measureKits{new MeasureKits{}};
    return measureKits;
}

MeasureKits::MeasureKits()
{
    std::invoke(&MeasureKits::init, this);
}

auto MeasureKits::init() noexcept -> void
{
    auto measureFile{cmrc::SonixToolsR::get_filesystem().open("config/measure.toml")};
    this->m_measureTable = toml::parse(std::string_view{measureFile.begin(), measureFile.end()});
}

auto MeasureKits::measureObstetrics(const Department::Obstetrics& _measureType, double _param) noexcept -> double
{
    auto table{this->m_measureTable[magic_enum::enum_type_name<Department::Obstetrics>()].as_table()};
    if (!table)
    {
        std::println("table read error!");
        return double{};
    }
    exprtk::symbol_table<double> formula{};
    formula.add_variable("param", _param, true);
    exprtk::expression<double> expression{};
    expression.register_symbol_table(formula);
    exprtk::parser<double> parser{};
    if (!parser.compile(std::string{(*table)[magic_enum::enum_name(_measureType)].value_or<std::string_view>(std::string_view{})}, expression))
    {
        std::println("parser error:", parser.error());
        return double{};
    }
    return expression.value();
}
