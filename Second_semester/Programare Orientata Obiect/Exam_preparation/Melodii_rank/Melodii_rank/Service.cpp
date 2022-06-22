#include "Service.h"

vector<int> Service::sameRank()
{
    vector<int> res;
    vector<Melodie> tot = getAll();
    vector<int> rankuri;
    for (auto& el : tot) {
        rankuri.push_back(el.getRank());
    }
    for (auto& el : rankuri) {
        int num = count(rankuri.begin(), rankuri.end(), el);
        res.push_back(num);
    }
    return res;
}

void Service::updateRank(int id, int newRank, string titlu)
{
    rep.updateRank(id, newRank, titlu);
}

void Service::deletePos(int id)
{
    if (rep.deletePos(id) == 0)
        throw(std::exception("Nu se poate sterge"));
    else;
}
