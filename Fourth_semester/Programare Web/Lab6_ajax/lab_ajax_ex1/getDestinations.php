<?php
// Verifica daca exista statia de plecare si daca nu este nula
if (isset($_GET['start']) && $_GET['start'] !== '') {
    // Citeste continutul fisierului XML intr-un string
    $xmlString = file_get_contents('destinations.xml');
    
    // Incarca continutul XML in obiectul SimpleXMLElement
    $destinations = new SimpleXMLElement($xmlString);
    
    // Cauta toate statiile care au aceeasi valoare ca statia de plecare selectata
    $result = $destinations->xpath("//destination[@from='" . $_GET['start'] . "']");
    
    // Construieste un array cu destinatiile gasite
    $destinationsArray = array();
    foreach ($result as $destination) {
        $destinationsArray[] = (string) $destination['to'];
    }
    
    // Returneaza raspunsul ca JSON
    header('Content-Type: application/json');
    echo json_encode($destinationsArray);
}
?>
