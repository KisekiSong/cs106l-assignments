#include "class.h"

bool socialCredit::isValidCredit(int credit)
{
    return (credit >= 0);
}

socialCredit::socialCredit()
    : credit{0}{};
socialCredit::socialCredit(int credit)
    : credit{credit >= 0 ? credit : 0}{}

int socialCredit::getCredit() const
{
    return credit;
}
void socialCredit::setCredit(int credit)
{
    if(isValidCredit(credit))
        this->credit = credit;
}

void socialCredit::AddCredit(int add)
{
    if(isValidCredit(add))
        this->credit += add;
}
void socialCredit::MinusCredit(int minus)
{
    if(isValidCredit(minus) && this->credit > minus)
        this->credit -= minus;
    else
        this->credit = 0;
}

void socialCredit::clearCredit()
{
    this->credit = 0;
}