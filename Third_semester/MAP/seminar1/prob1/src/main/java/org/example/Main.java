package org.example;

public class Task {
    private String taskId;
    private String descriere;

    public Task(String taskId, String descriere) {
        this.taskId = taskId;
        this.descriere = descriere;
    }

    public void setTaskId(String taskId) {
        this.taskId = taskId;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public String getTaskId() {
        return taskId;
    }

    public String getDescriere() {
        return descriere;
    }

    public abstract execute(){

    }
}