var Enemy_light = Enemy.extend({
    health: 20,
    size: {w: 76, h: 92},
    className: "Enemy_light",
    sprite: "enemy_light",
    shootInt: 100,
    score: 100,
    speedBullet: 12,
    classBullet: EnemyLightMissle
})