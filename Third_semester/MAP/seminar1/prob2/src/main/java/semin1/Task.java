package semin1;

import java.util.Objects;

abstract class Task {
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

    public abstract void execute();

    @Override
    public String toString() {
        return super.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Task task = (Task) o;
        return Objects.equals(taskId, task.taskId) && Objects.equals(descriere, task.descriere);
    }

    @Override
    public int hashCode() {
        return Objects.hash(taskId, descriere);
    }
}