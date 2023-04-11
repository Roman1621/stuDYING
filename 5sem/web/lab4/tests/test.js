let routes = require('../routes')

function generate_string(len){
    let chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    let result = ''
    for(let i = 0; i < len; i++){
        result += chars[Math.floor(Math.random()*chars.length)]
    }
    return result;
}

function generate_users(len){
    let users = []
    for(let i = 0; i < len; i++){
        users.push({ id:Math.floor(Math.random()*30000), name:generate_string(20), mail:generate_string(20) })
    }
    return users
}

test('get_id_by_mail test', () => { let users = {users: generate_users(30)};
    let n = Math.floor(Math.random()*30);
    let user_tofind = users.users[n];
    expect(routes.get_id_by_mail(user_tofind.mail, users)).toBe(n)
})