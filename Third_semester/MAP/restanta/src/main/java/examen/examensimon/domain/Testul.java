package examen.examensimon.domain;


public class Testul extends Entity<Integer>{
    private Integer idTest;
    private Integer idIntrebare;

    public Testul(Integer integer, Integer idTest, Integer idIntrebare) {
        super(integer);
        this.idTest = idTest;
        this.idIntrebare = idIntrebare;
    }

    public Integer getIdTest() {
        return idTest;
    }

    public Integer getIdIntrebare() {
        return idIntrebare;
    }
}
