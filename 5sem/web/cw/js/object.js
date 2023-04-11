var Object_heal = Entity.extend({
    size: {w: 40, h: 56},
    sprite: "object_heal",
    className: "Object_heal",
    heal: 50,
    touch: function (obj){
        if(obj && obj.className == "Player"){
            obj.health += this.heal;
            if(obj.health > 100) obj.health = 100;
            gameManager.removeObject(this);
        }
    }
})