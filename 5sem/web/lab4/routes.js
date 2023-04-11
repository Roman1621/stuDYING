const express = require('express')
const app = express.Router()
let users = require("../lab3/user_storage.json")
const fs = require('fs')
let news = require("../lab3/news_storage.json")
let friends = require("../lab3/friends_storage.json")
const path = require("path");
const password = require("../lab4/pass.json")
const incoming_form = require('formidable').IncomingForm;

function save(fl, _json){
    fs.writeFile(fl, JSON.stringify(_json), (error) => {if(error) throw error})
}
function get_id_by_mail(mail, local = users){
    for(let i = 0; i < local.users.length; i++){
        if(local.users[i].mail == mail) return i;
    }
}
app.get("*", (req, res)=>{
    res.status(404); // Ошибка – нет такой страницы
    res.end("Page not found");
});
app.get("/", (req, res, next)=>{
    res.end("ROOT PAGE");
});
app.post("/login", (req, res) => {
    if(password[req.body.mail] && password[req.body.mail] == req.body.password){
        res.end(JSON.stringify({id: get_id_by_mail(req.body.mail), is_admin: users.users[get_id_by_mail(req.body.mail)].role == 'Admin'}))
        return
    }
    else{
        res.end(JSON.stringify({error: "Wrong login/password"}));
    }
})
app.post("/register", (req, res) => {
    if(get_id_by_mail(req.body.mail) != undefined){res.end(JSON.stringify({error: "User is already register"})); return;}
    users.users.push({mail: req.body.mail, name: req.body.name, birth: req.body.birth})
    password[req.body.mail] = req.body.password
    save("../lab3/user_storage.json", users)
    save("../lab4/pass.json", password)
    res.end(JSON.stringify({}))
});
app.post("/user_photo", (req, res) => {
    let user = users.users[req.body.id];
    if(user){res.end(JSON.stringify({photo: 'https://localhost:3000/public/images/' + user.photo}))}
    else{res.end(JSON.stringify({error: "Wrong id"}))}
});
app.post("/upload_photo", (req, res) => {
    let user = users.users[req.headers.id];
    if(!user){res.end(JSON.stringify({error: "Wrong id"})); return;}
    let form = new incoming_form();
    form.on("file", (field, file) => {
        let new_fname = file.newFilename + '.' + file.mimetype.substring(file.mimetype.lastIndexOf("/") + 1);
        fs.writeFileSync("../lab3/public/images/" + new_fname, fs.readFileSync(file.filepath));
        user.photo = new_fname;
        res.status(200); res.end();
    });
    form.on("end", () => {});
    form.parse(req);
})
app.post("/user_info", (req, res) => {
    let user = users.users[req.body.id];
    if(!user){res.end(JSON.stringify({error: "Wrong id"})); return;}
    res.end(JSON.stringify({name: user.name, mail: user.mail, birth: user.birth, status: user.status, role: user.role}))
})
app.post("/news", (req, res)=>{
    let user = users.users[req.body.id];
    if(!user){res.end(JSON.stringify({error: "Wrong id"})); return;}
    let news_massive = []
    for(let i = 0; i < news.news.length; i++){
        if(news.news[i].id_user == req.body.id){news_massive.push({user_name: user.name, news_name: news.news[i].news_name, news_body: news.news[i].news_body})}
    }
    for(let i = 0; i < friends.friends.length; i++){
        if(req.body.id == friends.friends[i].id){
            for(let y = 0; y < friends.friends[i].list_friends.length; y++){
                for(let x = 0; x < news.news.length; x++){
                    if(news.news[x].id_user == friends.friends[i].list_friends[y] && users.users[friends.friends[i].list_friends[y]].status != 'Banned'){news_massive.push({user_name: users.users[friends.friends[i].list_friends[y]].name, news_name: news.news[x].news_name, news_body: news.news[x].news_body})}
                }
            }
        }
    }
    res.end(JSON.stringify({news: news_massive}))
})
app.post("/add_news", (req, res) => {
    let user = users.users[req.body.id];
    if(!user){res.end(JSON.stringify({error: "Wrong id"})); return;}
    if(user.status == 'Banned'){res.end(JSON.stringify({error: "User has been banned"})); return;}
    news.news.push({id_user: req.body.id, news_name: req.body.news_name, news_body: req.body.news_body})
    global.server_io.sockets.emit('news')
    res.end(JSON.stringify({}))
})
module.exports = {app, get_id_by_mail};