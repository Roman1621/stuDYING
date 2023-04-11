musicManager.init();
mapManager.loadMap("/assets/map.json");
spriteManager.loadSprites("/assets/sprite.json");
audioManager.init("/assets/sounds/sounds.json")
audioManager.loadSound("/assets/sounds/sounds.json");
eventManager.init();
let d = document.getElementById("username");
d.innerHTML = localStorage['playername'];
setInterval(()=>{
    renderManager.renderTiles();
    renderManager.renderObjects();
    gameManager.tick();
}, 20);