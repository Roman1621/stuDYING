var Enemy = Entity.extend({
    sightDist: 5*128,
    shootDist: 3*128,
    shootInt: 0,
    shootTimer: 0,
    health: 0,
    size: {w: 0, h: 0},
    sprite: "",
    target: null,
    speed: 5,
    speedBullet: 0,
    className: "Enemy",
    dir: 1,
    deathTimer: 0,
    classBullet: null,
    score: 0,
    checkSight: function (obj){
        let v0 = {x: Math.floor(this.pos.x), y: Math.floor(this.pos.y)};
        let v1 = {x: Math.floor(obj.pos.x), y: Math.floor(obj.pos.y)};
        let dx = Math.abs(v1.x - v0.x), sx = v0.x < v1.x ? 1 : -1;
        let dy = -Math.abs(v1.y - v0.y), sy = v0.y < v1.y ? 1 : -1;
        let err = dx + dy; let e2 = 0;
        while(1){
            if(!mapManager.isPassable(v0)) return false;
            if(v0.x == v1.x && v0.y == v1.y){
                return true;
            }
            e2 = err*2;
            if(e2 >= dy){err += dy; v0.x += sx}
            if(e2 <= dx){err += dx; v0.y += sy}
        }
    },
    getTarget: function (){
        for(let i = 0; i < gameManager.objects.length; i++){
            let obj = gameManager.objects[i];
            // if(obj.className == "Player") console.log(this.pos, obj.pos)
            if(obj.className == 'Player' && this.checkSight(obj) && this.distanceTo(obj) <= this.sightDist) {
                this.target = obj;
                break;
            }
        }
    },
    tick: function (){
        if(this.deathTimer > 0) {
            this.deathTimer--;
            if(this.deathTimer == 0){gameManager.removeObject(this); return;}
        }
        Entity.tick.call(this);
        if(this.health <= 0){
            return;
        }
        if(this.shootTimer > 0) this.shootTimer--;
        if(!this.target || !this.checkSight(this.target) || this.distanceTo(this.target) <= this.shootDist*2/3){
            this.vel.x = this.vel.y = 0;
        }
        if(!this.target){
            this.getTarget();
        }

        else{
            if(this.checkSight(this.target) && this.distanceTo(this.target) <= this.sightDist) {
                this.faceToTarget();
            }
            if((this.distanceTo(this.target) > this.shootDist*2/3 || !this.checkSight(this.target)) && this.distanceTo(this.target) <= this.sightDist){
                this.moveToTarget();
            }
            if(this.checkSight(this.target) && this.distanceTo(this.target) <= this.shootDist && this.shootTimer == 0){
                this.shootTimer = this.shootInt;
                let v = {x: this.target.pos.x-this.pos.x, y:this.target.pos.y - this.pos.y};
                let lengthV = Math.sqrt(v.x**2+v.y**2);
                if(lengthV > 0){
                    v.x /= lengthV;
                    v.y /= lengthV;
                }
                v.x *= this.speedBullet;
                v.y *= this.speedBullet;
                let p = {x: this.pos.x+v.x*10, y: this.pos.y + v.y*10}
                shooting(v, p, this.classBullet);
            }
        }

    },
    faceToTarget: function (){
        let dx = this.pos.x - this.target.pos.x;
        let dy = this.pos.y - this.target.pos.y;
        this.rotation = Math.PI * 3/2 - Math.atan2(dy, dx);
        if(this.rotation >= Math.PI * 2) this.rotation -= Math.PI * 2;
        this.rotation *= -1;
    },
    moveToTarget: function (){
        let v = {x: this.pos.x - this.target.pos.x, y: this.pos.y - this.target.pos.y}
        let vlen = Math.sqrt(v.x**2+v.y**2);
        if(vlen > 0){
            v.x /= vlen;
            v.y /= vlen;
        }
        v.x *= -this.speed;
        v.y *= -this.speed;
        // this.vel = v;

        for(let a = 0; a < Math.PI;a += 30*Math.PI/180){
            let ad = a*this.dir;
            let vr = {x: v.x * Math.cos(ad) - v.y*Math.sin(ad), y: v.x * Math.sin(ad) + v.y*Math.cos(ad)}
            this.pos.x += vr.x; this.pos.y += vr.y;
            if(!gameManager.checkMapCollision(this) && !gameManager.checkEdgeCollision(this)){
                this.vel = vr;
                this.pos.x -= vr.x;
                this.pos.y -= vr.y;
                return;
            }
            this.pos.x -= vr.x;
            this.pos.y -= vr.y;
        }
        this.dir *= -1;
        console.log(this.dir);
    },
    die: function (){
        this.sprite = "boom";
        this.size = {w: 114, h: 112};
        this.deathTimer = 50;
        gameManager.score += this.score;
        gameManager.updateScore();
        audioManager.playSound("Death")
    }
})