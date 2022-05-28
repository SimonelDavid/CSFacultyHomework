#include "undo.h"

void undoAdd::doUndo(){
    repo.removeElem(code);
}

void undoRemove::doUndo(){
    repo.addElem(subject);
}

void undoChange::doUndo(){
    repo.changeElement(subject.getCode(), subject);
}