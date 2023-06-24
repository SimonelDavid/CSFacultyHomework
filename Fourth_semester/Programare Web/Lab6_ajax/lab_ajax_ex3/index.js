$(document).ready(function() {
    // se incarca lista cheilor din fisierul XML
    $.ajax({
      type: "GET",
      url: "database.xml",
      dataType: "xml",
      success: function(xml) {
        // pentru fiecare inregistrare se adauga cheia in lista
        $(xml).find('inregistrare').each(function() {
          var key = $(this).attr('id');
          $('#select-key').append($('<option></option>').attr('value', key).text(key));
        });
        
        // la selectarea unei chei se vor incarca datele corespunzatoare in formular
        $('#select-key').change(function() {
          var selectedKey = $(this).val();
          $(xml).find('inregistrare[id="' + selectedKey + '"]').each(function() {
            var name = $(this).find('nume').text();
            var phone = $(this).find('telefon').text();
            var email = $(this).find('email').text();
            
            $('#input-name').val(name);
            $('#input-phone').val(phone);
            $('#input-email').val(email);
            
            // se activeaza butonul de salvare
            $('#save-btn').prop('disabled', false);
          });
        });
        
        // la schimbarea valorilor din formular se va activa butonul de salvare
        $('input').on('input', function() {
          $('#save-btn').prop('disabled', false);
        });
        
        // la submiterea formularului se vor salva datele
        $('form').submit(function(event) {
          event.preventDefault();
          var selectedKey = $('#select-key').val();
          var name = $('#input-name').val();
          var phone = $('#input-phone').val();
          var email = $('#input-email').val();
          
          // se construieste obiectul XML ce va fi trimis serverului
          var xmlData = '<inregistrare id="' + selectedKey + '">';
          xmlData += '<nume>' + name + '</nume>';
          xmlData += '<telefon>' + phone + '</telefon>';
          xmlData += '<email>' + email + '</email>';
          xmlData += '</inregistrare>';
          
          // se trimite cererea AJAX catre server pentru a salva datele
          $.ajax({
            type: "POST",
            url: "salveaza.php",
            data: {xmlData: xmlData},
            success: function() {
              $('#message').text('Datele au fost salvate cu succes!');
            }
          });
          
          // se dezactiveaza butonul de salvare
          $('#save-btn').prop('disabled', true);
        });
      }
    });
  });
  