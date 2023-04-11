const CLM = 10;
const BLOCK_SIZE = 32;
const ROW = 20;
const NEW_ROW = 6;
const NEW_CLM = 6;

var canvas = document.getElementById('board');
var ctx = canvas.getContext('2d');
canvas.width = CLM * BLOCK_SIZE;
canvas.height = ROW * BLOCK_SIZE;
var next_figure = document.getElementById('next_figure');
var next_ctx = next_figure.getContext('2d');
next_figure.width = NEW_CLM * BLOCK_SIZE;
next_figure.height = NEW_ROW * BLOCK_SIZE;
//next_ctx.scale(BLOCK_SIZE, BLOCK_SIZE); 
var button = document.getElementById("play");
let count = 0;
let rAF = null;
var score = 0;
let counterOfDeleteLines = 0;
var level = Math.floor(score/1000);
let endGame = false;
document.getElementById("player").innerHTML = localStorage['playername'];

var gamefield = [];
for(let i = -2; i < ROW; i++){
    gamefield[i] = [];
    for(let j = 0; j < CLM; j++){
        gamefield[i][j] = 0;
    }
}
var next_figure_field = [];
for(let i = 0; i < NEW_ROW; i++){
    next_figure_field[i] = [];
    for(let j = 0;j < NEW_CLM; j++){
        next_figure_field[i][j] = 0;
    }
}

var tetroSeq = [];
const tetrominos = {
    'Z': [
        [1,1,0],
        [0,1,1],
        [0,0,0]
    ],
    'S': [
        [0,1,1],
        [1,1,0],
        [0,0,0]
    ],
    'T': [
        [0,1,0],
        [1,1,1],
        [0,0,0]
    ],
    'L': [
        [1,0,0],
        [1,0,0],
        [1,1,0]
    ],
    'J': [
        [0,1,0],
        [0,1,0],
        [1,1,0]
    ],
    'I': [
        [1,0,0,0],
        [1,0,0,0],
        [1,0,0,0],
        [1,0,0,0]
    ],
    'O': [
        [1,1],
        [1,1]
    ]
}
const colors = ['navy', 'red', 'blue', 'yellow', 'green', 'purple', 'orange', 'cyan']
const tetrominosColors = {
    'Z': 1,
    'T': 2,
    'L': 3,
    'I': 4,
    'O': 5,
    'J': 6,
    'S': 7
}
function rotateTetromino(tetromino){
    const len = tetromino.matrix.length - 1;
    var result = [];
    for(let i = len; i >= 0; i--){
        for(let j = 0; j < tetromino.matrix[i].length; j++){
            if(!result[j]) result[j] = [];
            result[j].push(tetromino.matrix[i][j]);
        }
    }
    return result;
}
function isValidMove(tetromino){
    for(let i = 0; i < tetromino.matrix.length; i++){
        for(let j = 0; j < tetromino.matrix[i].length; j++){
            if(tetromino.matrix[i][j] && (tetromino.clm + j < 0 || tetromino.clm + j >= gamefield[0].length || tetromino.row + i >= gamefield.length || gamefield[tetromino.row + i][tetromino.clm + j])) return false;
        }
    }
    return true;
}

function getRandomInt(min, max){
    return Math.floor(Math.random() * (max - min + 1)) + min;
}
function getTetroSeq(){
    const seq = ['Z','T','L','I','O','J','S'];
    while(seq.length){
        const randTet = getRandomInt(0, seq.length-1);//choose random tetromino 
        const Tet = seq.splice(randTet, 1)[0];//delete that random tetromino from seq
        tetroSeq.push(Tet);
    }
}
function getNext(){
    if(tetroSeq.length === 0){
        getTetroSeq();
    }
    const Tet = tetroSeq.pop();
    const matrix = tetrominos[Tet];
    const start_clm = Math.floor(CLM/2)-1;
    const start_row = Tet === 'I' ? -1 : -2;
    return{
        name: Tet,
        matrix: matrix,
        row: start_row,
        clm: start_clm
    };
}
let tetromino = getNext();
let next_tetromino = getNext();
function placeTetromino(){
    for(let y = 0; y < tetromino.matrix.length; y++){
        for(let x = 0; x < tetromino.matrix[y].length; x++){
            if(tetromino.matrix[y][x]){
                if (tetromino.row + y < 0) {
                    return gameOver();
                }
                gamefield[tetromino.row+y][tetromino.clm+x] = tetrominosColors[tetromino.name];
            }
        }
    }
    for(let y = gamefield.length - 1; y >= 0; ){
        if(gamefield[y].every(cell => !!cell)){//if the row is filled
            for(let i = y; i >= 0; i--){//delete row
                for(let j = 0; j < gamefield[i].length; j++){ 
                    gamefield[i][j] = gamefield[i-1][j];
                     
                }
            }
            counterOfDeleteLines++;
        }
        else y--;
    }
    //console.log(counterOfDeleteLines);
    if(counterOfDeleteLines === 1) score += 40;
    else if(counterOfDeleteLines === 2) score += 100;
    else if(counterOfDeleteLines === 3) score += 400;
    else if(counterOfDeleteLines > 3) score += 1000;
    level = Math.floor(score/100);
    document.getElementById("score").innerHTML = score;
    document.getElementById("level").innerHTML = level;
    counterOfDeleteLines = 0;
    //console.log(counterOfDeleteLines);
    tetromino = next_tetromino;
    next_tetromino = getNext();
}
/*function nextFigureFieldClear(){
    for(let i = 0; i < NEW_ROW; i++){
        next_figure_field[i] = [];
        for(let j = 0;j < NEW_CLM; j++){
            next_figure_field[i][j] = 0;
        }
    }*/
function placeNextTetromino(){
    //console.log("Update");
    for(let i = 0; i < NEW_ROW; i++){
        next_figure_field[i] = [];
        for(let j = 0;j < NEW_CLM; j++){
            next_figure_field[i][j] = 0;
        }
    }
    for(let y = 0; y < next_tetromino.matrix.length; y++){
        for(let x = 0; x < next_tetromino.matrix[y].length; x++){
            if(next_tetromino.matrix[y][x]){
                if(next_tetromino.name === 'I'){
                    next_figure_field[1 + y][3 + x] = tetrominosColors[next_tetromino.name];
                }
                else if(next_tetromino.name === 'J' || next_tetromino.name === 'L'){
                    next_figure_field[1 + y][2 + x] = tetrominosColors[next_tetromino.name];
                }
                else next_figure_field[2 + y][2 + x] = tetrominosColors[next_tetromino.name];
            }
        }
    }
}

function play(){
    rAF = requestAnimationFrame(play);
    ctx.clearRect(0,0,canvas.width, canvas.height);
    
    for(let row = 0; row < ROW; row++){
        for(let clm = 0; clm < CLM; clm++){
            const name = gamefield[row][clm];
            ctx.fillStyle = colors[name];
            ctx.fillRect(clm*BLOCK_SIZE, row*BLOCK_SIZE, BLOCK_SIZE-1, BLOCK_SIZE-1);
        }
    }
    next_ctx.clearRect(0,0,next_figure.width,next_figure.height);
    for(let new_row = 0; new_row < NEW_ROW; new_row++){
        for(let new_clm = 0; new_clm < NEW_CLM; new_clm++){
            const new_name = next_figure_field[new_row][new_clm];
            next_ctx.fillStyle = colors[new_name];
            next_ctx.fillRect(new_clm*BLOCK_SIZE, new_row*BLOCK_SIZE, BLOCK_SIZE-1, BLOCK_SIZE-1);
        }
    }
    placeNextTetromino();
    if(tetromino){
        if(++count > (36-level)){
            tetromino.row++;
            count = 0;
            if(!isValidMove(tetromino)){
                tetromino.row--;
                placeTetromino();
            }
        }
    }
    //отрисовка игрового поля с учётом расположенных фигур
    ctx.fillStyle = colors[tetrominosColors[tetromino.name]];
    for(let y = 0; y < tetromino.matrix.length; y++){
        for(let x = 0; x < tetromino.matrix[y].length; x++){
            if(tetromino.matrix[y][x]){
                //рисуем на 1 пиксель меньше, чтобы получился эффект клетки
                ctx.fillRect((tetromino.clm + x)*BLOCK_SIZE, (tetromino.row + y)*BLOCK_SIZE, BLOCK_SIZE-1, BLOCK_SIZE-1); 
            }
        }
    }
}
button.onclick = play;

function gameOver(){
    cancelAnimationFrame(rAF);
    endGame = true;
    ctx.fillStyle = 'black';
    ctx.globalAlpha = 0.75;
    ctx.fillRect(0, canvas.height/2-30, canvas.width, 60);
    ctx.globalAlpha = 1;
    ctx.fillStyle = 'red';
    ctx.font = '36px monospace';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText('GAME OVER!', canvas.width/2, canvas.height/2);
    let leader_board = localStorage['tetris_leaderboard'];
    if(!leader_board){
        leader_board = [];
    }
    else leader_board = JSON.parse(leader_board);
    let cur = null;
    for(let i = 0; i < leader_board.length; i++){
        if(leader_board[i].playername == localStorage['playername']){
            cur = leader_board[i];
            break;
        }
    }
    if(cur){
        if(cur.score < score) cur.score = score;
    }
    else {
    leader_board.push({playername: localStorage['playername'], score})
    }
    leader_board.sort(function(a, b){ return b.score - a.score})
    leader_board = leader_board.slice(0, 6);
    localStorage['tetris_leaderboard'] = JSON.stringify(leader_board)
    window.location = "main.html"
} 


document.addEventListener('keydown', function (e){
    if(endGame) return;
    if(e.which === 38){
        tetromino.matrix = rotateTetromino(tetromino);
        if(!isValidMove(tetromino)){
            tetromino.matrix = rotateTetromino(tetromino);
            tetromino.matrix = rotateTetromino(tetromino);
            tetromino.matrix = rotateTetromino(tetromino);
        }
    }
    else if(e.which === 39){
        tetromino.clm++;
        if(!isValidMove(tetromino))tetromino.clm--;
    }
    else if(e.which === 37){
        tetromino.clm--;
        if(!isValidMove(tetromino)) tetromino.clm++;
    }
    else if(e.which === 40){
        tetromino.row++
        if(!isValidMove(tetromino)){
            tetromino.row--;
            placeTetromino();
            return;
        }
    }
    else if(e.which === 32){
        while(isValidMove(tetromino)){
            tetromino.row++;
            if(!isValidMove(tetromino)){
                tetromino.row--;
                placeTetromino();
                return;
            }
        }
    }
});