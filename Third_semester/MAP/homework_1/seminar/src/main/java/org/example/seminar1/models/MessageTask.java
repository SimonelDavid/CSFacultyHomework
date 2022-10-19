package org.example.seminar1.models;

public class MessageTask extends Task {
    private Message message;

    public MessageTask(String taskID, String description, Message message) {
        super(taskID, description);
        this.message = message;
    }

    @Override
    public void execute() {
        System.out.println(message.getMessage() + " " + message.getFormattedDate());
    }

    @Override
    public String toString() {
        return super.toString() + message.toString();
    }
}
