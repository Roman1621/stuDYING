const express = require('express')
const app = express.Router()
const favicon = require('serve-favicon')
const path = require('path')
app.use(favicon(path.join(__dirname,'/favicon.ico')))
const file = require("fs")
const local = require("./user_storage")
const local_news = require("./news_storage")
const local_friends = require("./friends_storage")

function save_user(){
    file.writeFile("./user_storage.json", JSON.stringify(local), (error) =>{
        if(error) throw error
    })
}
function save_news(){
    file.writeFile("./news_storage.json", JSON.stringify(local_news), (error) =>{
        if(error) throw error
    })
}
function save_friends(){
    file.writeFile("./friends_storage.json", JSON.stringify(local_friends), (error) =>{
        if(error) throw error
    })
}

app.get("/", (req, res) =>{
    res.sendFile(path.resolve(global.build_dir + "html/main.html"));
});
app.get("/main", (req, res) => {
    res.set("Content-type", "application/json;charset=utf-8");
    res.end(JSON.stringify(local.users));
});
app.get("/main/:num", (req, res)=>{
    res.set("Content-type", "application/json;charset=utf-8");
    res.end(JSON.stringify(local.users[req.params.num]));
});
app.get("/info", (req, res)=>{
    res.set("Content-type", "application/json;charset=utf-8");
    res.end(JSON.stringify(local_friends.friends));
});
app.get("/news_data", (req, res)=>{
    res.set("Content-type", "application/json;charset=utf-8");
    res.end(JSON.stringify(local_news.news.sort(function (a, b){
        return new Date(a.news_date).getTime() - new Date(b.news_date).getTime();
    })));
});
app.get("/info_data/:num", (req, res)=>{
    let friends_massive = [];
    let friends;
    for(let i = 0; i < local_friends.friends.length; i++){
        if(local_friends.friends[i].id == req.params.num){
            friends = local_friends.friends[i];
            break;
        }
    }
    for(let j = 0; j < friends.list_friends.length; j++) {
        for (let i = 0; i < local.users.length; i++) {
            if (local.users[i].id === friends.list_friends[j]) friends_massive.push(local.users[i]);
        }
    }
    res.end(JSON.stringify(friends_massive));
});
app.get("/info/:num", (req, res) => {
    res.sendFile(path.resolve(global.build_dir + "html/info.html"));
});
app.get("/news", (req, res)=>{
   res.sendFile(path.resolve(global.build_dir + "html/news.html"));
});
app.get("*", (req, res)=>{
    res.status(404); // Ошибка – нет такой страницы
    res.sendFile(path.resolve('404.html'));
});
app.put("/users/:num", (req, res) => {
    const changeable = ["name", "mail", "birth", "status", "role"];
    for(let i = 0; i < changeable.length; ++i){
        cur = changeable[i];
        if(req.body[cur])
            local.users[req.params.num][cur] = req.body[cur];
    }
    save_user();
    res.sendStatus(200);
});

module.exports = app;