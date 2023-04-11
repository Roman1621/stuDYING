const express = require("express")
const app = require("./app")
//const pug = require("pug")

const server = express()
server.use(express.json())
server.use("/css", express.static("css"))
server.use("/js", express.static("js"))
server.set("view engine", "pug")
server.set("views", "./view")
server.use("/", app)
server.listen(3000)