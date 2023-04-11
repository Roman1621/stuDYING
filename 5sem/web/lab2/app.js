const express = require('express')
const app = express.Router()
const favicon = require('serve-favicon')
const path = require('path')
app.use(favicon(path.join(__dirname,'/favicon.ico')))
const file = require("fs")
const local = require("./local_storage")
function save_local(){
    file.writeFile("./local_storage.json", JSON.stringify(local), (error) =>{
        if(error) throw error
    })
}

app.get("/groups/:num", (req, res) => {
    let book
    for(let i = 0; i < local.books.length; i++){
        if(local.books[i].id == req.params.num) {
            book = local.books[i]
            break
        }
    }
    res.render("info", {book})
});
app.get("/", (req, res)=>{
    res.render("main", {local, filter: req.headers["filter"], filter_value: req.headers["filter_value"]});
});
app.get("*", (req, res)=>{
    res.status(404); // Ошибка – нет такой страницы
    res.render('404.html');
});

app.post("/groups", (req, res) => {
    let last = local.books[local.books.length - 1].id
    local.books.push({"title": "No name", "author":  "", "release": "", "id": last+1, "availability": true, "cur_reader": null})
    save_local()
    res.status(200)
    res.render("main", {local, filter: req.headers["filter"], filter_value: req.headers["filter_value"]})
});

app.post("/groups/give/:num", (req, res)=>{
    for(var i = 0; i < local.books.length; i++)
        if(local.books[i].id == req.params.num) break
    if(i < local.books.length){
        local.books[i].availability = false;
    }
    save_local();
    // console.log(i);
    // console.log(local.books);
    res.render("info", {"book": local.books[i]})
});
app.post("/groups/return/:num", (req, res)=>{
    for(var i = 0; i < local.books.length; i++)
        if(local.books[i].id == req.params.num) break
    if(i < local.books.length){
        local.books[i].availability = true;
        local.books[i].cur_reader = null;
        local.books[i].return_date = undefined;
    }
    save_local();
    res.render("info", {"book": local.books[i]})
});
app.post("/groups/edit/:num", (req, res)=>{
    for(var i = 0; i < local.books.length; i++)
        if(local.books[i].id == req.params.num) break
    if(i < local.books.length){
        local.books[i].title = req.body.title;
        local.books[i].author = req.body.author;
        local.books[i].release = req.body.release;
        local.books[i].cur_reader = req.body.cur_reader;
        local.books[i].return_date = req.body.return_date;
    }
    //console.log(i);
    save_local();
    //console.log(req.body);
    //console.log(local.books[i]);
    res.render("info", {"book": local.books[i]});
});

app.delete("/groups/", (req, res) => {
    for (elem of req.headers.remove_list) {
        let remove_book = elem / "1";
        console.log(remove_book);
        for (let i = 0; i < local.books.length; i++) {
            if (local.books[i].id === remove_book) local.books.splice(i, 1)
        }
    }
    save_local()
    res.status(200)
    res.render("main", {local, filter: req.headers["filter"], filter_value: req.headers["filter_value"]})
});

module.exports = app;