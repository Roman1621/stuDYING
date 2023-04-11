var Enemy_heavy = Enemy.extend({
    health: 20,
    size: {w: 104, h: 104},
    className: "Enemy_heavy",
    sprite: "enemy_heavy",
    shootInt: 300,
    score: 200,
    speedBullet: 10,
    classBullet: EnemyHeavyMissle
})