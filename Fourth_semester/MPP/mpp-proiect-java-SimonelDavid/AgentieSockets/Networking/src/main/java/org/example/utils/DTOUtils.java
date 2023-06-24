package org.example.utils;

import org.example.Angajat;
import org.example.Bilet;
import org.example.Zbor;
import org.example.dto.BiletBuyDTO;
import org.example.dto.UserDTO;

public class DTOUtils {
    public static Angajat getFromDTO(UserDTO usdto){
        String id=usdto.getId();
        String pass=usdto.getPasswd();
        return new Angajat(0, id, pass);

    }
    public static UserDTO getDTO(Angajat user){
        String id=user.getNume();
        String pass=user.getParola();
        return new UserDTO(id, pass);
    }
    public static UserDTO getDTO(Zbor zbor){
        String id=zbor.getDestinatie();
        String pass=zbor.getData();
        return new UserDTO(id, pass);
    }
    public static Zbor getZborFromDTO(UserDTO usdto){
        String id=usdto.getId();
        String pass=usdto.getPasswd();
        return new Zbor(0, id, pass, "", "", 0);

    }

    public static Zbor getZborFromD(BiletBuyDTO dto) {
        return new Zbor(dto.getIdZ(), dto.getDestinatieZ(), dto.getData(), dto.getOra(), dto.getAeroport(), dto.getLocuriZ());
    }

    public static Bilet getBiletFromD(BiletBuyDTO dto) {
        return new Bilet(0, dto.getClientB(), dto.getTuristiB(), dto.getAdresaB(), dto.getLocuriB());
    }

    public static int getLocuriFromD(BiletBuyDTO dto) {
        return dto.getLocuri();
    }

    public static String getDestD(BiletBuyDTO dto) {
        return dto.getDest_();
    }

    public static String getDataD(BiletBuyDTO dto) {
        return dto.getData_();
    }
}
