class socialCredit
{
public:
    socialCredit();
    socialCredit(int credit);
    int getCredit() const;
    void setCredit(int credit);
    void AddCredit(int add);
    void MinusCredit(int mminus);
    void clearCredit();
private:
    int credit;
    bool isValidCredit(int credit);
};