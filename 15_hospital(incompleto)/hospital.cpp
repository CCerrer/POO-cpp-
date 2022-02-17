#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <vector>
#include <iomanip>


class IMedic;

class IPatient
{
public:
    virtual void addMedic(IMedic* medic) = 0;

    virtual std::string getDiagnostic() = 0;

    virtual std::string getId() = 0;

    
}