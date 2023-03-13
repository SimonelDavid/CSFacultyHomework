package examen.restantasimonel.domain;


public class Intrebare extends Entity<Integer>{
    private Integer nrIntrebare;
    private String descriere;
    private String v1;
    private String v2;
    private String v3;
    private String corect;
    private Float punctaj;
    private Integer test;

    public Intrebare(Integer nrIntrebare, String descriere, String v1, String v2,
                     String v3, String corect, Float punctaj, Integer test) {
        super(nrIntrebare);
        this.nrIntrebare = nrIntrebare;
        this.descriere = descriere;
        this.v1 = v1;
        this.v2 = v2;
        this.v3 = v3;
        this.corect = corect;
        this.punctaj = punctaj;
        this.test = test;
    }

    public Integer getTest() {
        return test;
    }

    public Integer getNrIntrebare() {
        return nrIntrebare;
    }

    public String getDescriere() {
        return descriere;
    }

    public String getV1() {
        return v1;
    }

    public String getV2() {
        return v2;
    }

    public String getV3() {
        return v3;
    }

    public String getCorect() {
        return corect;
    }

    public Float getPunctaj() {
        return punctaj;
    }
}
