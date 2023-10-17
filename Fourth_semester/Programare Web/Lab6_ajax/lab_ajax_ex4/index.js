// Initialize game state variables
var currentPlayer = Math.random() < 0.5 ? 'X' : 'O'; // randomly select starting player
var gameTable = document.getElementById('game-table');
var cells = gameTable.getElementsByTagName('td');

// Add event listeners to each cell in the game table
for (var i = 0; i < cells.length; i++) {
  cells[i].addEventListener('click', cellClicked);
}

// Function to handle clicks on each cell in the game table
function cellClicked(event) {
    var cell = event.target;
    
    // Check if cell is already marked
    if (cell.innerHTML !== '') {
      return;
    }
    
    // Mark the cell with the current player's symbol
    cell.innerHTML = currentPlayer;
    
    // Call server-side script to make the next move
    makeMove(cell);
    
    // Check for game over condition
    var gameResult = checkGameOver();
    if (gameResult === 'TIE') {
      endGame(gameResult);
    } else if (gameResult !== '') {
      endGame(gameResult);
    }
    
    // Switch to the next player
    currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
}
  

// Function to call server-side script to make the next move
function makeMove(cell) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "server-side-script.php", true);
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function() {
      if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
        // handle server response here if needed
      }
    };
    var data = "cell=" + cell.id + "&player=" + currentPlayer;
    xhr.send(data);
}
  

// Function to check if the game is over and return the winning player or 'TIE' if it's a tie
function checkGameOver() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "server-side-script.php?action=checkGameOver", false); // set async flag to false
    xhr.send();
    
    if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
        var gameResult = xhr.responseText;
        if (gameResult !== '') {
            endGame(gameResult);
        }
        return gameResult;
    }
    
    // If game is not over yet, return an empty string
    return '';
}
  

// Function to end the game and display the result
function endGame(result) {
    alert('Game Over! Result: ' + result);
    // Reset game state
    currentPlayer = Math.random() < 0.5 ? 'X' : 'O';
    for (var i = 0; i < cells.length; i++) {
      cells[i].innerHTML = '';
    }
}
  
