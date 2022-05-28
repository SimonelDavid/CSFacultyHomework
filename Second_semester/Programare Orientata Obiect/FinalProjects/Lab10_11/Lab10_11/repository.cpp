#include "repository.h"

physical repository::find(unsigned int code) {
    return find_if(list.begin(),list.end(),[code](entity a){return a.getCode() == code;});
}

repository::repository():nrElems{0}{}

int repository::addElem(entity to_add){
    to_add.setCode( (nrElems + 1) * 1000 + (rand() % 1000) );
    list.push_back(to_add);
    ++nrElems;
    
    return to_add.getCode();
}

bool repository::test_code(int code) {
    return find(code) != list.end();
}

void repository::removeElem(int code){

    physical location = find(code);
    list.erase(location);
    --nrElems;
}


void repository::changeElement(int code, entity updated){
    physical location = find(code);
    
    if(updated.getName() != "")
        location->setName(updated.getName());
        
    if(updated.getPrice() != -1)
        location->setPrice(updated.getPrice());
    
    if(updated.getManufacturer() != "")
        location->setManufacturer(updated.getManufacturer());
    
    if(updated.getSubstance() != "")
        location->setSubstance(updated.getSubstance());

}

iter_pair repository::getAll(){
    return iter_pair(list.begin(),list.end());
}

int repository::getNrElems(){
    return nrElems;
}

entity repository::getElem(int code){
    return *(find(code));
}
void repository::DESTROY(){
    list.clear();
    nrElems = 0;
}

bool comparator_nume(entity a, entity b){
    if(a.getName() == b.getName())
        return a.getPrice() < b.getPrice();
    
    return a.getName() < b.getName();
}

bool comparator_manufacturer(entity a, entity b){
    if(a.getManufacturer() == b.getManufacturer())
        return a.getPrice() < b.getPrice();
    
    return a.getManufacturer() < b.getManufacturer();
}

bool comparator_substance(entity a, entity b){
    if(a.getSubstance() == b.getSubstance())
        return a.getPrice() < b.getPrice();
    
    return a.getSubstance() < b.getSubstance();
}


void repository::sortElems(int clause){
    switch(clause){
        case 0:
            sort(list.begin(),list.end(), comparator_nume);
            break;
        case 1:
            sort(list.begin(),list.end(), comparator_manufacturer);
            break;
        
        case 2:
            sort(list.begin(),list.end(), comparator_substance);
            break;            
    }
}


void repository_report::addItem(string manufacturer){

    auto search = reports.find(manufacturer); 

    if(search == reports.end() ){
        reports.insert(pair<string, int>(manufacturer, 1));
    }else{
        reports[manufacturer]++;
    }

}

int repository_report::getItem(string manufacturer) const{
    
    auto search = reports.find(manufacturer);

    if( search == reports.end())
        return -1;
    else
        return search->second;

}

void repository_report::removeItem(string manufacturer){
    auto search = reports.find(manufacturer);

    if(search == reports.end())
        throw RangeError("Elementul nu exista in rapoarte.");
    else{
        --reports[manufacturer];

        if(reports[manufacturer] == 0)
            reports.erase(manufacturer);
    }
}

pair<unordered_map<string, int>::iterator,unordered_map<string, int>::iterator>
repository_report::getAll(){
    return pair<unordered_map<string, int>::iterator,unordered_map<string, int>::iterator>(reports.begin(), reports.end());
}
