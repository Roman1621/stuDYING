const fs = require("fs");
const https = require("https");
const private_key = fs.readFileSync("./key/server.key", "utf8")
const certificate = fs.readFileSync("./key/server.csr", "utf8")

if(process.argv[2])
    global.build_opt = process.argv[2];
else
    global.build_opt = "gulp";
global.build_dir = "build_" + global.build_opt + "/";

const express = require("express")
const routes = require("./routes")
const server = express()
server.use(express.json())
server.use("/public", express.static("public"))
server.use("/css", express.static("build_gulp/" + "css"))
server.use("/js", express.static(global.build_dir + "js"))
server.set("view engine", "pug")
server.set("views", "./view")
server.use("/", routes)
const httpsServer = https.createServer({key: private_key, cert: certificate}, server);
httpsServer.listen(3000);