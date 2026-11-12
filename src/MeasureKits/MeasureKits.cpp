#include "MeasureKits.h"
#include "MeasureKitsPrivate.h"

MeasureKits::MeasureKits()
{
    this->m_measureKitsPrivate = new MeasureKitsPrivate{};
}

MeasureKits::~MeasureKits() noexcept
{
    delete this->m_measureKitsPrivate;
}

auto MeasureKits::measurePrivate(const std::any& _measureType, const std::vector<double>& _args) noexcept -> double
{
    try
    {
        if (_measureType.type() == typeid(Department::Obstetrics))
        {
            return m_measureKitsPrivate->measurePrivate(std::any_cast<Department::Obstetrics>(_measureType), _args);
        }
        if (_measureType.type() == typeid(Department::FetalWeight))
        {
            return m_measureKitsPrivate->measurePrivate(std::any_cast<Department::FetalWeight>(_measureType), _args);
        }
    }
    catch (const std::exception& _e)
    {
        std::println("measure error:{}", _e.what());
    }
    catch (...)
    {
        std::println("measure error: unknown");
    }
    return double{};
}
