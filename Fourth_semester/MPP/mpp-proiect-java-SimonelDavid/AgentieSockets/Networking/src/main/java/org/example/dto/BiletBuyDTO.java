package org.example.dto;

import java.io.Serializable;

public class BiletBuyDTO implements Serializable {
    private String turistiB;
    private String adresaB;
    private Integer locuriB;
    private String clientB;
    private Integer idZ;
    private String destinatieZ;
    private String data;
    private String ora;
    private String aeroport;
    private Integer locuriZ;
    private Integer locuri;
    private String dest_;
    private String data_;

    public BiletBuyDTO(String turistiB, String adresaB, Integer locuriB, String clientB, Integer idZ, String destinatieZ, String data, String ora, String aeroport, Integer locuriZ, Integer locuri, String dest_, String data_) {
        this.turistiB = turistiB;
        this.adresaB = adresaB;
        this.locuriB = locuriB;
        this.clientB = clientB;
        this.idZ = idZ;
        this.destinatieZ = destinatieZ;
        this.data = data;
        this.ora = ora;
        this.aeroport = aeroport;
        this.locuriZ = locuriZ;
        this.locuri = locuri;
        this.dest_ = dest_;
        this.data_ = data_;
    }

    public Integer getIdZ() {
        return idZ;
    }

    public void setIdZ(Integer idZ) {
        this.idZ = idZ;
    }



    public String getTuristiB() {
        return turistiB;
    }

    public void setTuristiB(String turistiB) {
        this.turistiB = turistiB;
    }

    public String getAdresaB() {
        return adresaB;
    }

    public void setAdresaB(String adresaB) {
        this.adresaB = adresaB;
    }

    public Integer getLocuriB() {
        return locuriB;
    }

    public void setLocuriB(Integer locuriB) {
        this.locuriB = locuriB;
    }

    public String getClientB() {
        return clientB;
    }

    public void setClientB(String clientB) {
        this.clientB = clientB;
    }

    public String getDestinatieZ() {
        return destinatieZ;
    }

    public void setDestinatieZ(String destinatieZ) {
        this.destinatieZ = destinatieZ;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public String getOra() {
        return ora;
    }

    public void setOra(String ora) {
        this.ora = ora;
    }

    public String getAeroport() {
        return aeroport;
    }

    public void setAeroport(String aeroport) {
        this.aeroport = aeroport;
    }

    public Integer getLocuriZ() {
        return locuriZ;
    }

    public void setLocuriZ(Integer locuriZ) {
        this.locuriZ = locuriZ;
    }

    public Integer getLocuri() {
        return locuri;
    }

    public void setLocuri(Integer locuri) {
        this.locuri = locuri;
    }

    public String getDest_() {
        return dest_;
    }

    public void setDest_(String dest_) {
        this.dest_ = dest_;
    }

    public String getData_() {
        return data_;
    }

    public void setData_(String data_) {
        this.data_ = data_;
    }

    @Override
    public String toString() {
        return "BiletBuyDTO{" +
                "turistiB='" + turistiB + '\'' +
                ", adresaB='" + adresaB + '\'' +
                ", locuriB=" + locuriB +
                ", clientB='" + clientB + '\'' +
                ", idZ=" + idZ +
                ", destinatieZ='" + destinatieZ + '\'' +
                ", data='" + data + '\'' +
                ", ora='" + ora + '\'' +
                ", aeroport='" + aeroport + '\'' +
                ", locuriZ=" + locuriZ +
                ", locuri=" + locuri +
                '}';
    }
}
