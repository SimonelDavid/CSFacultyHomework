package com.example.template.entities;

public class Location {
    private Integer locationId;
    private String locationName;


    public String getlocationName() {
        return locationName;
    }

    public void setlocationName(String locationName) {
        this.locationName = locationName;
    }

    public Integer getlocationId() {
        return locationId;
    }

    public void setlocationId(Integer locationId) {
        this.locationId = locationId;
    }

    public Location(String locationName, Integer locationId) {
        this.locationName = locationName;
        this.locationId = locationId;
    }
}
