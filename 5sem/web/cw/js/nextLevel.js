var NextLevel = Entity.extend({
    size: {w: 128, h: 128},
    touch: function (obj){
        if(obj && obj.className == "Player"){
            gameManager.removeObject(this);
            mapManager.unloadMap();
            console.log(mapManager.nextMap)
            mapManager.loadMap(mapManager.nextMap);
        }
    }
})