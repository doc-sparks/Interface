#ifndef DATAVALUE_H
#define DATAVALUE_H

class QString;

class DataValue
{
public:
    DataValue();    
    DataValue( const double val );
    DataValue(const DataValue &src);

    void setValue( const double val );
    void setValue( const DataValue *val );
    double getDouble() const;
    QString getString() const;

    DataValue& operator= (const DataValue &src);
    bool operator== (const DataValue &src) const;
    bool operator!=(const DataValue &other) const;

private:
    double dValue_;
};

#endif // DATAVALUE_H
