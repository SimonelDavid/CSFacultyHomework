package examen.examensimon.utils.utils;

public class ActualEvent implements Event{
    private final ChangeEventType type;

    public ActualEvent(ChangeEventType type) {
        this.type = type;
    }

    public ChangeEventType getType() {
        return type;
    }

}
