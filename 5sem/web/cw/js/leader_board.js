function storeUserName(username){
    if (!username.length)
        return false;
    localStorage.setItem("playername", username);
    return true;
}
function login(){
    let playername = document.getElementById('playername').value;
    const form = document.forms.input_window;
    if (storeUserName(playername))
        window.location = "/game.html";
    else
        alert("Введите имя");
}

leader_board = localStorage['leaderboard'];
const table = document.getElementById("results");
if(leader_board){
    const records = JSON.parse(leader_board);
    for(let i = 0; i < records.length; i++){
        const tableRow = table.insertRow();
        const tableCells = [];
        tableCells.push(tableRow.insertCell(), tableRow.insertCell(), tableRow.insertCell());
        tableCells[0].innerText = i+1;
        tableCells[1].innerText = records[i][0];
        tableCells[2].innerText = records[i][1];

    }
}