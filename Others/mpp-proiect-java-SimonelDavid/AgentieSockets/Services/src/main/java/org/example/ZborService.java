package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

public class ZborService {
    private ZborDBRepository zborDBRepository;

    public ZborService(ZborDBRepository zborDBRepository) {
        this.zborDBRepository = zborDBRepository;
    }

    public List<Zbor> findAll() {
        List<Zbor> res = new ArrayList<Zbor>();
        for(Zbor z : res){
            if(z.getLocuri() > 0)
                res.add(z);
        }
        return res;
    }

    public List<Zbor> findDestinatieData(String destinatie, String data) {
        return (List<Zbor>) zborDBRepository.findByDestinatieData(destinatie, data);
    }

    public boolean biletCumparat(Zbor selected, int locuri) {
        if(selected.getLocuri() < locuri)
            return false;
        selected.setLocuri(selected.getLocuri() - locuri);
        zborDBRepository.update(selected.getId(), selected);
        return true;
    }
}
