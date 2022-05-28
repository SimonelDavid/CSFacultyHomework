#pragma once
#include "repository.h"
class undoAction{
    public:
        virtual void doUndo() = 0;

        virtual ~undoAction(){};
};



class undoAdd : public undoAction{
    private:
        repository& repo;
        int code;
    public:
        undoAdd(repository& r, int c):repo{r},code{c}{};

        void doUndo() override;

};


class undoRemove : public undoAction{
    private:
        repository& repo;
        entity subject;
    public:
        undoRemove(repository& r, entity s):repo{r},subject{s}{};

        void doUndo() override;

};

class undoChange : public undoAction{

    private:
        repository& repo;
        entity subject;
    public:
        undoChange(repository& r, entity s):repo{r},subject{s}{};

        void doUndo() override;

};

