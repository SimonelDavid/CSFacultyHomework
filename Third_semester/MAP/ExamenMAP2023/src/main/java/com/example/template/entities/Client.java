package com.example.template.entities;

public class Client {
    private Long id;
    private String name;
    private Integer fidelity;
    private Integer age;
    private Hobby hobby;

    public Client(Long id, String name, Integer fidelity, Integer age, Hobby hobby) {
        this.id = id;
        this.name = name;
        this.fidelity = fidelity;
        this.age = age;
        this.hobby = hobby;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }



    public Integer getFidelity() {
        return fidelity;
    }



    public void setAge(Integer age) {
        this.age = age;
    }

    public Hobby getHobby() {
        return hobby;
    }

    public void setHobby(Hobby hobby) {
        this.hobby = hobby;
    }

    public static Hobby getHobbyFromString(String string){
        return Hobby.valueOf(string);
    }
}
