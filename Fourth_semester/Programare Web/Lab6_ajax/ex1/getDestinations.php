<?php
// Verifica daca exista statia de plecare si daca nu este nula
if (isset($_GET['start']) && $_GET['start'] !== '') {
    // Incarca continutul fisierului XML in obiectul SimpleXMLElement
    $destinations = simplexml_load_file('destinations.xml');
    
    // Cauta toate statiile care au aceeasi valoare ca statia de plecare selectata
    $result = $destinations->xpath("//destination[starts-with(@from, '" . $_GET['start'] . "')]");
    
    // Construieste un array cu destinatiile gasite
    $destinationsArray = array();
    foreach ($result as $destination) {
        $destinationsArray[] = (string) $destination['to'];
    }
    
    // Returneaza raspunsul ca JSON
    header('Content-Type: application/json');
    echo json_encode($destinationsArray);
}
