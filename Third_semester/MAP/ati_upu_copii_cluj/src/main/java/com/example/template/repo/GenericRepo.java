package com.example.template.repo;

import java.util.List;

public interface GenericRepo <T>{
    void getData();
    List<T> getAll();
}
