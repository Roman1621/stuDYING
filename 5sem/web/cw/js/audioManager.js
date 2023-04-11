var audioManager = {
    context: [],
    clips: {},
    gainNode: [],
    ctx_index: 0,

    init: async function(path, ctx_amount = 5){
        for(let i = 0; i < ctx_amount; i++){
            this.context[i] = new AudioContext();
            this.gainNode[i] = this.context[i].createGain ? this.context[i].createGain() : this.context[i].createGainNode();
            this.gainNode[i].connect(this.context[i].destination);
        }
        let answer = await fetch(path, {method: "GET"});
        let res = await answer.json();
        for(let i = 0; i < res.length; i++){
            this.loadSound(res[i]);
        }
    },
    loadSound: async function(path){
        let sound = {src: path, buffer: undefined, loaded: false};
        let pathStart = path.lastIndexOf('/')+1;
        let pathCrop = path.substr(pathStart, path.lastIndexOf('.') - pathStart);
        this.clips[pathCrop] = sound;
        let answer = await fetch(path, {method: "GET", headers: {"response-type": "arraybuffer"}});
        let res = await answer.arrayBuffer();
        let decode = await this.context[this.ctx_index].decodeAudioData(res);
        sound.buffer = decode;
        sound.loaded = true;
    },
    playSound: function (name, volume = 1, loop = false){
        let sound = this.clips[name];
        if(!sound.loaded) return;
        let src = this.context[this.ctx_index].createBufferSource();
        src.buffer = sound.buffer;
        src.connect(this.gainNode[this.ctx_index]);
        src.loop = loop;
        this.gainNode[this.ctx_index].gain.value = volume;
        src.start(0);
        this.ctx_index = (this.ctx_index+1)%this.context.length;
    }
}