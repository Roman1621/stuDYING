const cors = require('cors')
const express = require("express")
const routes = require("./routes")
const Parser = require("body-parser")
const server = express();
server.use(cors());
server.use(Parser.json());
server.use(Parser.urlencoded({extended: true}));


const http = require("http").Server(server);
const io = require("socket.io")(http, {
    cors: {
        origins: ["*"],
        handlePreflightRequest: (req, res) => {
            res.writeHead(200, {
                "Access-Control-Allow-Credintals": "*",
                "Access-Control-Allow-Origin": "*",
                "Access-Control-Allow-Methods": "GET,POST,PUT,GET,HEAD,PATCH,DELETE",
            });
            res.end();
        }
    }
});

global.server_io = io;
server.use('/', routes.app);
http.listen(4300);