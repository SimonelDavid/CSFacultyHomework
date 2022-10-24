package org.example.seminar1.models;

import java.time.LocalDateTime;

import static org.example.seminar1.utils.Utils.DATE_TIME_FORMATTER;

public class Message {
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    public Message(String message, String from, String to, LocalDateTime date) {
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public String getFormattedDate() {
        return date.format(DATE_TIME_FORMATTER);
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "|message=" + message + "|from=" + from + "|to=" + to + "|date=" + getFormattedDate();
    }
}
