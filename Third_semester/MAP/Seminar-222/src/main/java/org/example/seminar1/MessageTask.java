package org.example.seminar1;

public class MessageTask extends Task {
    private Message message;

    public MessageTask(String taskId, String description, Message message) {
        super(taskId, description);
        this.message = message;
    }

    @Override
    public void execute() {

    }
}
