var eventManager = {
    binds: [],
    events: [],
    mouse: {x: 0, y: 0},
    onMouseMove: function (event){
        var canvas = document.getElementById('canvasID');
        eventManager.mouse.x = event.clientX - canvas.offsetLeft;
        eventManager.mouse.y = event.clientY - canvas.offsetTop;
    },
    onKeyDown: function (event){
        let e = eventManager.binds[event.keyCode];
        if(e){
            eventManager.events[e] = true;
        }
    },
    onKeyUp: function (event){
        let e = eventManager.binds[event.keyCode];
        if(e){
            eventManager.events[e] = false;
        }
    },
    onMouseDown: function (event){
        eventManager.events["fire"] = true;
    },
    onMouseUp: function (event){
        eventManager.events["fire"] = false;
    },
    init: function (){
        this.binds[87] = 'up';
        this.binds[65] = 'left';
        this.binds[83] = 'down';
        this.binds[68] = 'right';
        document.body.addEventListener("keydown", this.onKeyDown);
        document.body.addEventListener("keyup", this.onKeyUp);
        document.body.addEventListener("mouseup", this.onMouseUp);
        document.body.addEventListener("mousedown", this.onMouseDown);
        document.body.addEventListener("mousemove", this.onMouseMove);
    }
}