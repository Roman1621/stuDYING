var mapManager = {
    tileSize: {w: 0, h: 0},
    mapSize: {w: 0, h: 0},
    tileset: [],
    tiles: [],
    tileImage: null,
    nextMap: "",
    loadMap: async function (path) {
        let fdir = path.substr(0, path.lastIndexOf("/")+1)
        let answer = await fetch(path, {method: "GET"})
        let data = await answer.json();
        for(let i = 0; i < data.layers.length; i++){
            if(!data.layers[i].properties) continue;
            for(let j = 0; j < data.layers[i].properties.length; j++)
            switch (data.layers[i].properties[j].name){
                case "Music": musicManager.set_music(data.layers[i].properties[j].value); break;
                case "NextMap": this.nextMap = data.layers[i].properties[j].value; break;
            }
        }
        this.tileSize.w = data.tilewidth;
        this.tileSize.h = data.tileheight;
        this.mapSize.w = data.width;
        this.mapSize.h = data.height;
        for(let i = 0; i < data.tilesets.length; i++){
            let answer = await fetch(fdir + data.tilesets[i].source, {method: "GET"})
            let tData = await answer.json();
            this.tileImage = new Image();
            this.tileImage.src = fdir + tData.image;
            for(let j = 0; j < tData.tiles.length; j++){
                let tile = tData.tiles[j];
                tile.image = this.tileImage;
                let aW = tData.imagewidth / tData.tilewidth;//colichestvo pixels na 1 tile
                tile.sx = tData.tilewidth * (tile.id%aW);
                tile.sy = tData.tileheight * Math.floor(tile.id/aW);
                tile.id += data.tilesets[i].firstgid;
                for(let k = 0; k < tile.properties.length; k++){
                    tile[tile.properties[k].name] = tile.properties[k].value;
                }
                this.tileset[tile.id] = tile;
            }
        }
        for(let i = 0; i < data.layers.length;i++){
            switch (data.layers[i].type){
                case "tilelayer": this.tiles.push(data.layers[i].data); break;
                case "objectgroup": for(let j = 0; j < data.layers[i].objects.length; j++) gameManager.addObject(data.layers[i].objects[j]); break;
            }
        }
    },
    isPassable: function (pos){
        for(let i = 0; i < this.tiles.length; i++){
            let x = Math.floor(pos.x/this.tileSize.w);
            let y = Math.floor(pos.y/this.tileSize.h);
            let j = y*this.mapSize.w + x;
            let tile = this.tileset[this.tiles[i][j]];
            if(!tile) continue;
            if(!tile.passable) return false
        }
        return true;
    },
    unloadMap: function (){
        gameManager.objects = [];
        this.tiles = [];
        this.tileset = [];
    }
}

