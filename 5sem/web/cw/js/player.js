var Player = Entity.extend({
    health: 100,
    size: {w: 84, h: 92},
    speed: 10,
    shootTimer: 0,
    shootDelay: 50*2,
    sprite: "player",
    className: "Player",
    tick: function () {
        Entity.tick.call(this);
        let d = document.getElementById("health");
        d.innerHTML = this.health;
        if(this.health <= 0){
            return;
        }
        if(this.vel.x != 0 || this.vel.y != 0){
            if(this.vel.x > 0 && this.vel.y > 0) this.rotation = -45;
            else if(this.vel.x < 0 && this.vel.y > 0) this.rotation = 45;
            else if(this.vel.x < 0 && this.vel.y < 0) this.rotation = 135;
            else if(this.vel.x > 0 && this.vel.y < 0) this.rotation = -135;
            else if(this.vel.x > 0) this.rotation = -90;
            else if(this.vel.x < 0) this.rotation = 90;
            else if(this.vel.y > 0) this.rotation = 0;
            else if(this.vel.y < 0) this.rotation = 180;
            this.rotation *= Math.PI/180;
        }
        this.vel.x = this.vel.y = 0;
        if(eventManager.events['up']) this.vel.y = -this.speed;
        if(eventManager.events['left']) this.vel.x = -this.speed;
        if(eventManager.events['down']) this.vel.y = this.speed;
        if(eventManager.events['right']) this.vel.x = this.speed;

        if(eventManager.events['fire'] && this.shootTimer == 0){
            this.shootTimer = this.shootDelay;
            var canvas = document.getElementById('canvasID');
            var cW = canvas.width / mapManager.mapSize.w;
            var cH = canvas.height / mapManager.mapSize.h;
            let x = this.pos.x/mapManager.tileSize.w*cW;
            let y = this.pos.y/mapManager.tileSize.h*cH;
            let v = {x: eventManager.mouse.x-x, y: eventManager.mouse.y-y};
            let lengthV = Math.sqrt(v.x**2 + v.y**2)
            if(lengthV > 0){
                v.x /= lengthV;
                v.y /= lengthV;
            }
            let speedBullet = this.speed + 2;
            v.x *= speedBullet;
            v.y *= speedBullet;
            let p = {x: this.pos.x+v.x*7, y: this.pos.y + v.y*7}
            shooting(v, p, PlayerMissle);
        }
        if(this.shootTimer > 0){
            this.shootTimer--;
        }
    },
    die: function (){
        gameManager.endGame = true;
        audioManager.playSound("Death")
    }
})