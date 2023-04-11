var Missle = Entity.extend({
    damage: 0,
    health: 1,
    size: {w: 16, h: 28},
    sprite: "bulletPlayer",
    touch: function (obj) {
        if (obj) obj.onDamage(this.damage);
        gameManager.removeObject(this);
    }
})

var PlayerMissle = Missle.extend({
    damage: 20
})

var EnemyLightMissle = Missle.extend({
    damage: 20,
    sprite: "bulletLight",
    size: {w: 24, h: 32}
})
var EnemyHeavyMissle = Missle.extend({
    damage: 50,
    sprite: "bulletHeavy",
    size: {w: 24, h: 32}
})
var BossMissle = Missle.extend({
    damage: 75,
    sprite: "bulletBoss",
    size: {w: 16, h: 36}
})

function shooting (vel, pos, cl){
    let m = Object.create(cl);
    m.create();
    m.vel = vel;
    m.pos = pos;
    m.rotation = Math.PI * 3/2 - Math.atan2(m.vel.y, m.vel.x);
    if(m.rotation >= Math.PI * 2) m.rotation -= Math.PI * 2;
    m.rotation *= -1;
    audioManager.playSound("Shot", 0.5);
    gameManager.objects.push(m);
}