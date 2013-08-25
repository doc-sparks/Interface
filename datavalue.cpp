#include "datavalue.h"
#include <QString>

////////////////////////////////////////////////////////
// Constructors
DataValue::DataValue() : dValue_(0)
{

}

DataValue::DataValue( const double val )
{
    setValue(val);
}

DataValue::DataValue(const DataValue &src)
{
    setValue(&src);
}

////////////////////////////////////////////////////////
// operator overloads
DataValue& DataValue::operator= (const DataValue &src)
{
    setValue(&src);
    return *this;
}

bool DataValue::operator== (const DataValue &src) const
{
    // are these equivalent?
    if (dValue_ == src.dValue_)
        return true;

    return false;
}

bool DataValue::operator!=(const DataValue &other) const
{
  return !(*this == other);
}


////////////////////////////////////////////////////////
// get/set functions
void DataValue::setValue(double val)
{
    dValue_ = val;
}

void DataValue::setValue(const DataValue *val)
{
    dValue_ = val->getDouble();
}

double DataValue::getDouble() const
{
    return dValue_;
}

QString DataValue::getString() const
{
    return QString::number(dValue_);
}
