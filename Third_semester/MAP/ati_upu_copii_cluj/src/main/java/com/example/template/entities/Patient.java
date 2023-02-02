package com.example.template.entities;

import java.util.Objects;

public class Patient {
    private String cnp;
    private Integer age;
    private Boolean premature;
    private String diagnostic;
    private Integer severity;

    private Boolean pending;

    public Boolean getPending() {
        return pending;
    }

    public void setPending(Boolean pending) {
        this.pending = pending;
    }

    public Patient(String cnp, Integer age, Boolean premature, String diagnostic, Integer severity) {
        this.cnp = cnp;
        this.age = age;
        this.premature = premature;
        this.diagnostic = diagnostic;
        this.severity = severity;
        this.pending = Boolean.TRUE;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Patient patient)) return false;
        return cnp.equals(patient.cnp);
    }

    @Override
    public int hashCode() {
        return Objects.hash(cnp);
    }

    public String getCnp() {
        return cnp;
    }

    public void setCnp(String cnp) {
        this.cnp = cnp;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public Boolean getPremature() {
        return premature;
    }

    public void setPremature(Boolean premature) {
        this.premature = premature;
    }

    public String getDiagnostic() {
        return diagnostic;
    }

    public void setDiagnostic(String diagnostic) {
        this.diagnostic = diagnostic;
    }

    public Integer getSeverity() {
        return severity;
    }

    public void setSeverity(Integer severity) {
        this.severity = severity;
    }
}
