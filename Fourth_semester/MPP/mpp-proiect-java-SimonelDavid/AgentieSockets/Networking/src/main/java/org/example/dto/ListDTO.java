package org.example.dto;

import org.example.Zbor;

import java.io.Serializable;
import java.util.List;

public class ListDTO implements Serializable {
    private List<Zbor> all;
    private List<Zbor> some;

    public ListDTO(List<Zbor> all, List<Zbor> some) {
        this.all = all;
        this.some = some;
    }

    public List<Zbor> getAll() {
        return all;
    }

    public void setAll(List<Zbor> all) {
        this.all = all;
    }

    public List<Zbor> getSome() {
        return some;
    }

    public void setSome(List<Zbor> some) {
        this.some = some;
    }
}
