var renderManager = {
    renderTiles: function (){
        var canvas = document.getElementById('canvasID');
        var ctx = canvas.getContext('2d');
        var cW = canvas.width / mapManager.mapSize.w;
        var cH = canvas.height / mapManager.mapSize.h;
        for(let j = 0; j < mapManager.tiles.length; j++){
            for(let i = 0; i < mapManager.tiles[j].length; i++){
                let x = (i%mapManager.mapSize.w)*cW;
                let y = Math.floor(i/mapManager.mapSize.w)*cH;
                let tile = mapManager.tileset[mapManager.tiles[j][i]];
                if(!tile) continue;
                ctx.drawImage(tile.image, tile.sx, tile.sy, mapManager.tileSize.w, mapManager.tileSize.h, x, y, cW, cH);
            }
        }
    },
    renderObjects: function (){
        var canvas = document.getElementById('canvasID');
        var ctx = canvas.getContext('2d');
        var cW = canvas.width / mapManager.mapSize.w;
        var cH = canvas.height / mapManager.mapSize.h;
        for(let i = 0; i < gameManager.objects.length; i++){
            let obj = gameManager.objects[i];
            let sprite = spriteManager.sprites[obj.sprite];
            if(!sprite) continue;
            let w = obj.size.w/mapManager.tileSize.w*cW;
            let h = obj.size.h/mapManager.tileSize.h*cH;
            let x = obj.pos.x/mapManager.tileSize.w*cW;
            // x -= w/2;
            let y = obj.pos.y/mapManager.tileSize.h*cH;
            // y -= h/2;
            ctx.translate(x, y);
            ctx.rotate(obj.rotation);
            ctx.drawImage(sprite.image, sprite.sx, sprite.sy, sprite.sw, sprite.sh, -w/2, -h/2, w, h);
            ctx.rotate(-obj.rotation);
            ctx.translate(-x, -y);
        }
    }
}