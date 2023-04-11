var spriteManager = {
    images: {},
    sprites: {},
    loadSprites: async function (path){
        let fdir = path.substr(0, path.lastIndexOf("/")+1)
        let answer = await fetch(path, {method: "GET"})
        let data = await answer.json();
        for(let name in data){
            let sprite = data[name];
            if(!this.images[sprite.src]) {
                this.images[sprite.src] = new Image();
                this.images[sprite.src].src = fdir + sprite.src;
            }
            sprite.image = this.images[sprite.src];
            this.sprites[name] = sprite;
        }
    }
}