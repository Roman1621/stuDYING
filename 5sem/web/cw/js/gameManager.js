var gameManager = {
    objects: [],
    score: 0,
    endGame: false,
    gameOverTimer: 3*50,
    winTimer: 3*50,
    winGame: false,
    addObject: function (obj) {
        let clas = window[obj.class]
        if(clas) {
            let o = Object.create(clas)
            o.create()
            o.pos.x = obj.x
            o.pos.y = obj.y
            this.objects.push(o)
        }
    },
    tick: function (){
        if(this.winGame) return this.win();
        if(this.endGame){
            return this.gameOver();
        }
        for(let i = 0; i < this.objects.length; i++){
            this.objects[i].justCollided = false;
        }
        for(let i = 0; i < this.objects.length; i++){
            let obj = this.objects[i];
            let collided = false;
            obj.pos.x += obj.vel.x;
            obj.pos.y += obj.vel.y;
            let col = this.checkMapCollision(obj);
            if(col){
                obj.pos.x -= col==1? obj.vel.x: Math.sign(obj.vel.x)*0.25;
                obj.pos.y -= col==1? obj.vel.y: Math.sign(obj.vel.y)*0.25;
                collided = true;
                obj.touch();
            }
            if(!collided){
                if(this.checkEdgeCollision(obj)){
                    obj.pos.x -= obj.vel.x;
                    obj.pos.y -= obj.vel.y;
                    collided = true;
                    obj.touch();
                }
            }
            if(!collided){
                for(let j = 0; j < this.objects.length; j++){
                    let obj2 = this.objects[j];
                    if(obj2.justCollided || j == i){
                        continue;
                    }
                    if((obj.pos.x-obj.size.w/2) < (obj2.pos.x+obj2.size.w/2) && (obj.pos.x+obj.size.w/2) > (obj2.pos.x-obj2.size.w/2) &&
                    (obj.pos.y-obj.size.h/2) < (obj2.pos.y+obj2.size.h/2) && (obj.pos.y+obj.size.h/2) > (obj2.pos.y-obj2.size.h/2)){
                        obj.pos.x -= obj.vel.x;
                        obj.pos.y -= obj.vel.y;
                        collided = true;
                        obj.touch(obj2);
                        obj2.touch(obj);
                        break;
                    }
                }
            }
            if(collided){
                obj.justCollided = true;
            }
            obj.tick();
        }
    },
    checkMapCollision: function (obj){
        let p = [{x: obj.pos.x - obj.size.w/2, y: obj.pos.y}, {x: obj.pos.x + obj.size.w/2, y: obj.pos.y}, {x: obj.pos.x, y: obj.pos.y - obj.size.h/2}, {x: obj.pos.x, y: obj.pos.y + obj.size.h/2},
            {x: obj.pos.x - obj.size.w/2, y: obj.pos.y - obj.size.h/2}, {x: obj.pos.x - obj.size.w/2, y: obj.pos.y + obj.size.h/2},
            {x: obj.pos.x + obj.size.w/2, y: obj.pos.y - obj.size.h/2}, {x: obj.pos.x + obj.size.w/2, y: obj.pos.y + obj.size.h/2}]
        for(let k = 0; k < 2; k++){
            for(let j = 0; j < p.length; j++){
                if(!mapManager.isPassable(p[j])){
                    return  k+1;
                }
            }
        }
        return false;
    },
    checkEdgeCollision: function (obj){
        if((obj.pos.x - obj.size.w/2) < 0 || (obj.pos.x + obj.size.w/2) > mapManager.mapSize.w*mapManager.tileSize.w ||
            (obj.pos.y - obj.size.h/2) < 0 || (obj.pos.y + obj.size.h/2) > mapManager.mapSize.h*mapManager.tileSize.h){
            return true;
        }
        return false;
    },
    removeObject: function (obj){
        for(let i = 0; i < this.objects.length; i++){
            if(this.objects[i] == obj){
                this.objects.splice(i, 1);
                break;
            }
        }
    },
    gameOver: function (){
        var canvas = document.getElementById('canvasID');
        var ctx = canvas.getContext('2d');
        ctx.fillStyle = 'black';
        ctx.globalAlpha = 0.75;
        ctx.fillRect(0, canvas.height/2-30, canvas.width, 60);
        ctx.globalAlpha = 1;
        ctx.fillStyle = 'red';
        ctx.font = '36px monospace';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText('GAME OVER!', canvas.width/2, canvas.height/2);
        if(this.gameOverTimer > 0){
            this.gameOverTimer--;
        }
        else if(this.gameOverTimer == 0){
            this.gameOverTimer -= 1;
            this.submitScore();
            window.location = "/main.html"
        }
    },
    win: function (){
        var canvas = document.getElementById('canvasID');
        var ctx = canvas.getContext('2d');
        ctx.fillStyle = 'black';
        ctx.globalAlpha = 0.75;
        ctx.fillRect(0, canvas.height/2-30, canvas.width, 60);
        ctx.globalAlpha = 1;
        ctx.fillStyle = 'green';
        ctx.font = '36px monospace';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText('YOU WIN!', canvas.width/2, canvas.height/2);
        if(this.winTimer > 0){
            this.winTimer--;
        }
        else if(this.winTimer == 0){
            this.winTimer -= 1;
            this.submitScore();
            window.location = "/main.html"
        }
    },
    submitScore: function() {
        let hs = localStorage['leaderboard'];
        if(!hs) hs = [];
        else hs = JSON.parse(hs);

        hs.push([localStorage['playername'], this.score]);
        hs.sort((a, b) => b[1] - a[1]);
        hs = hs.slice(0, 9);

        localStorage['leaderboard'] = JSON.stringify(hs);
    },
    updateScore: function (){
        let d = document.getElementById("score")
        d.innerHTML = this.score;
    }
}