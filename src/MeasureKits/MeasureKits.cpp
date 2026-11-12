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
