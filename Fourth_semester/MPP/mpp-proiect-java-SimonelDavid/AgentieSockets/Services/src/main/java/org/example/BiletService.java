package org.example;

public class BiletService {
    private BiletDBRepository biletDBRepository;

    public BiletService(BiletDBRepository biletDBRepository) {
        this.biletDBRepository = biletDBRepository;
    }

    public void cumparaBilet(Bilet bilet) {
        biletDBRepository.save(bilet);
    }
}
