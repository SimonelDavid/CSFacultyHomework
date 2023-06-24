$(document).ready(function() {
    // Function to get destinations
    function getDestinations(start) {
        $.ajax({
            url: 'getDestinations.php',
            data: { start: start },
            type: 'GET',
            dataType: 'json',
            success: function(destinations) {
                // Clear the destinations list
                $('#end').empty();
                
                // Add the destinations to the list
                $.each(destinations, function(index, value) {
                    $('#end').append($('<option>', {
                        value: value,
                        text: value
                    }));
                });
            },
            error: function() {
                alert('Error getting destinations');
            }
        });
    }

    // Event listener for when a departure station is selected
    $('#start').on('change', function() {
        var start = $(this).val();
        if (start !== '') {
            getDestinations(start);
        }
    });
});
