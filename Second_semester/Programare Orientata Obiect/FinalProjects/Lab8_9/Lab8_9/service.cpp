#include "service.h"


unsigned int service::addElem(string name, string price, string manufacturer, string substance){
    try{
        valid.validateAll(name, price, manufacturer, substance);
    }catch(ValidationError& e){
        throw e;}
    entity to_add(name, stof(price), manufacturer, substance);

    rapoarte.addItem(manufacturer);
    unsigned int code = repo.addElem(to_add);
    undoList.push_back(std::make_unique<undoAdd>(repo, code));
    return code;
}

void service::deleteElem(int code){
    if(repo.test_code(code)){
        entity toDel = repo.getElem(code);
        repo.removeElem(code);
        undoList.push_back(std::make_unique<undoRemove>(repo, toDel));

        rapoarte.removeItem(toDel.getManufacturer());
    }
    else{
        throw RangeError("Invalid code.");
    }

}

void service::changeElem(int code, string name, string price, string manufacturer, string substance){
    entity modif("", 0, "", "");

    if(!repo.test_code(code))
        throw RangeError("Invalid code.");


    entity actual = repo.getElem(code);

    try{
        valid.validateName(name);
        modif.setName(name);
    }catch(ValidationError& e){
        if(e.getMessage() == "invalid"){
            modif.setName(actual.getName());
            throw e;}}

    try{
        valid.validatePrice(price);
        modif.setPrice(stof(price));
    }catch(ValidationError& e){
        if(e.getMessage() == "invalid"){
            modif.setPrice(actual.getPrice());
            throw e;}}

    try{
        valid.validateManufacturer(manufacturer);
        modif.setManufacturer(manufacturer);
    }catch(ValidationError& e){
        if(e.getMessage() == "invalid"){
            modif.setManufacturer(actual.getManufacturer());
            throw e;}}

    try{
        valid.validateSubstance(substance);
        modif.setSubstance(substance);
    }catch(ValidationError& e){
        if(e.getMessage() == "invalid"){
            modif.setSubstance(actual.getSubstance());
            throw e;}}

        undoList.push_back(std::make_unique<undoChange>(repo, actual));
        repo.changeElement(code, modif);

}


iter_pair service::getAll(){
    return repo.getAll();
}

int service::getNrElems(){
    return repo.getNrElems();
}

void service::UNDO(){
    if(undoList.size() == 0)
        throw RangeError("No more undo's to perform.");
    else{
        undoList.back()->doUndo();
        undoList.pop_back();
    }
}

entity service::searchElem(string name, string manufacturer){
    iter_pair meds = repo.getAll();

    physical result = find_if(meds.first, meds.second, [name, manufacturer](entity c){
        if(manufacturer=="-1")
            return name == c.getName();
        else if(name == "-1")
            return manufacturer == c.getManufacturer();
        else
            return name == c.getName() && manufacturer == c.getManufacturer();
    } );

    if(result != meds.second)
        return *result;
    
    throw RangeError("No element found");}

iter_pair service::filterElems_afterPrice(string price){
    
    try{
        valid.validatePrice(price);
        filter.DESTROY();
    }catch(ValidationError& e){
        throw e;}

    float p = stof(price);


    iter_pair res = repo.getAll();
    physical start = res.first;
    physical end = res.second;
    
    vector<entity> output;
    copy_if(start, end, back_inserter(output), [p](entity a){ return a.getPrice() == p;} );

    for(auto i : output)
        filter.addElem(i);

    return filter.getAll();
}


iter_pair service::filterElems_afterSubstance(string substance){
    
    try{
        valid.validateSubstance(substance);
        filter.DESTROY();
    }catch(ValidationError& e){
        throw e;}

    iter_pair res = repo.getAll();
    physical start = res.first;
    physical end = res.second;

    vector<entity> output;
    copy_if(start, end, back_inserter(output), [substance](entity a){ return a.getSubstance() == substance; });

    for(auto i : output)
        filter.addElem(i);


    return filter.getAll();
}

iter_pair service::filterElems_afterName(string name){
    
    try{
        valid.validateName(name);
        filter.DESTROY();
    }catch(ValidationError& e){
        throw e;}

    iter_pair res = repo.getAll();
    physical start = res.first;
    physical end = res.second;
    
    vector<entity> output;
    copy_if(start, end, std::back_inserter(output), [name](entity a){ return a.getName() == name; });

    for(auto i:output)
        filter.addElem(i);

    return filter.getAll();
}

iter_pair service::filterElems(string attr, int clause){
    switch (clause)
    {
    case 1:
        try{
            return filterElems_afterName(attr);
        }catch(ValidationError& e){
            throw e;}break;
    
    case 2:
        try{
            return filterElems_afterPrice(attr);
        }catch(ValidationError& e){
            throw e;}break;
    case 3:
        try{
            return filterElems_afterSubstance(attr);
        }catch(ValidationError& e){
            throw e;}
        break;
    }

    throw RangeError("Invalid crit.");}

void service::sortElems(int clause){
    repo.sortElems(clause);
}

entity service::getElem(int pos){
    return repo.getElem(pos);
}




void service_reteta::adaugaPeReteta(string name){
    entity med = serv.searchElem(name, "-1");

    lista.addElem(med);
}

void service_reteta::golesteReteta(){
    lista.DESTROY();
}

void service_reteta::genereazaReteta(int nrTotal){

    for(int i=0; i<nrTotal;++i){
        
        int pos = rand() % serv.getNrElems();
        entity med = serv.getElem(pos);

        lista.addElem(med);
    }
}


void service_reteta::exportReteta(string numeFisier){
    std::ofstream O_FILE;


    O_FILE.open(numeFisier);
    iter_pair elements = lista.getAll();

    for_each(elements.first, elements.second, [&O_FILE](entity a){
        O_FILE<<a.getCSVFormat();
    });

    O_FILE.close();
}

pair<unordered_map<string, int>::iterator,unordered_map<string, int>::iterator> service::getReports(){
    return rapoarte.getAll();
}