package semin1;

import java.time.LocalDateTime;

public class MessageTask extends Task {

    private Message message;

    private String from;
    private String to;
    private LocalDateTime date;
    public MessageTask(String taskId, String descriere, Message message) {
        super(taskId, descriere);
        this.message = message;
    }

    @Override
    public void execute() {

    }


}
