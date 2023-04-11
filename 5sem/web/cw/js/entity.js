var Entity = {
    // pos: {x: 0, y: 0},
    size: {w: 0, h: 0},
    sprite: "",
    rotation: 0,
    health: 0,
    damage: 0,
    className: "Entity",
    extend: function (cl) {
        let obj = Object.create(this);
        for(let p in cl){
            if(this.hasOwnProperty(p) || typeof obj[p] === "undefined"){
                obj[p] = cl[p];
            }
        }
        return obj;
    },
    distanceTo: function (obj){
        return Math.sqrt((this.pos.x-obj.pos.x)**2 + (this.pos.y-obj.pos.y)**2)
    },
    create: function (){
        this.pos = {x: 0, y: 0};
        this.vel = {x: 0, y: 0};
    },
    onDamage: function (damage){
        this.health -= damage;
        audioManager.playSound("Hit", 0.5)
        console.log(damage)
        if(this.health <= 0){
            this.die();
        }
    },
    die: function (){

    },
    tick: function (){
        if(this.health <= 0){
            this.vel.x = this.vel.y = 0;
        }
    },
    touch: function (obj){}
}