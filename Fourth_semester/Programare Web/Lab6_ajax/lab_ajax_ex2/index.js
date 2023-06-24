var xmlData = null;
var currentPage = 0;
var pageSize = 3;

function loadData() {
  // make AJAX call to get data
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      xmlData = this.responseXML;
      displayData();
      // enable/disable buttons based on total number of pages
      var rows = xmlData.getElementsByTagName("row");
      var totalPages = Math.ceil(rows.length / pageSize);
      document.getElementById("prev-btn").disabled = currentPage == 0;
      document.getElementById("next-btn").disabled = currentPage == totalPages - 1;
    }
  };
  xhttp.open("GET", "database.xml", true);
  xhttp.send();
}


function displayData() {
  var startIndex = currentPage * pageSize;
  var endIndex = startIndex + pageSize;
  var rows = xmlData.getElementsByTagName("row");
  var totalPages = Math.ceil(rows.length / pageSize);

  // disable/enable buttons based on current page
  document.getElementById("prev-btn").disabled = currentPage == 0;
  document.getElementById("next-btn").disabled = currentPage == totalPages - 1;

  // build HTML table with rows from XML data
  var tableHtml = "<table>";
  for (var i = startIndex; i < endIndex && i < rows.length; i++) {
    var row = rows[i];
    var cells = row.getElementsByTagName("cell");
    var name = cells[0].textContent + " " + cells[1].textContent;
    var phone = cells[2].textContent;
    var email = cells[3].textContent;
    tableHtml += "<tr><td>" + name + "</td><td>" + phone + "</td><td>" + email + "</td></tr>";
  }
  tableHtml += "</table>";

  // display HTML table in container div
  document.getElementById("data-container").innerHTML = tableHtml;
}

// attach event listeners to buttons
document.getElementById("prev-btn").addEventListener("click", function() {
  if (currentPage > 0) {
    currentPage--;
    displayData();
  }
});
document.getElementById("next-btn").addEventListener("click", function() {
  var rows = xmlData.getElementsByTagName("row");
  var totalPages = Math.ceil(rows.length / pageSize);
  if (currentPage < totalPages - 1) {
    currentPage++;
    displayData();
  }
});

// load data on page load
loadData();
