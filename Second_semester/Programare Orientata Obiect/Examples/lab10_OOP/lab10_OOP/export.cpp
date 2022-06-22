#include "export.h"
#include "locatarRepo.h"
#include <fstream>

void exportToCVS(const std::string& fName, const std::vector<Locatar>& loc)
{
    std::ofstream locatarOutput(fName, std::ios::trunc);
    if (!locatarOutput.is_open())
        throw LocatarRepoException("Unable to open file" + fName);
    for (auto& l : loc) {
        locatarOutput << l.getApartment() << "," << l.getName() << "," << l.getSurface() << "," << l.getType() << "\n";
    }
    locatarOutput.close();
}

void exportToHTML(const std::string& fName, const std::vector<Locatar>& loc)
{
    std::ofstream locatarOutput(fName, std::ios::trunc);
    if (!locatarOutput.is_open())
        throw LocatarRepoException("Unable to open file" + fName);
    locatarOutput << "<html><body>" << std::endl;
    locatarOutput << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
    for (const auto& l : loc) {
        locatarOutput << "<tr>" << std::endl;
        locatarOutput << "<td>" << l.getApartment() << "</td>" << std::endl;
        locatarOutput << "<td>" << l.getName() << "</td>" << std::endl;
        locatarOutput << "<td>" << l.getSurface() << "</td>" << std::endl;
        locatarOutput << "<td>" << l.getType() << "</td>" << std::endl;
        locatarOutput << "</tr>" << std::endl;
    }
    locatarOutput << "</table>" << std::endl;
    locatarOutput << "</body></html>" << std::endl;
    locatarOutput.close();
}
