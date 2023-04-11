var Boss = Enemy.extend({
    health: 200,
    size: {w: 104, h: 120},
    className: "Boss",
    sprite: "boss",
    shootInt: 250,
    sightDist: 20*128,
    shootDist: 15*128,
    speedBullet: 15,
    classBullet: BossMissle,
    score: 1000,
    die: function (){
        Enemy.die.call(this);
        gameManager.winGame = true;
    }
})