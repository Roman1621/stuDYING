var musicManager = {
    ctx: undefined,
    gainNode: undefined,

    musicData: undefined,
    musicF: undefined,
    musicSrc: undefined,

    init: async function() {
        this.ctx = new AudioContext();
        this.gainNode = this.ctx.createGain ? this.ctx.createGain() : this.ctx.createGainNode();
        this.gainNode.connect(this.ctx.destination);
    },
    set_music: async function(name, volume, replace = true) {
        if(replace){
            this.ctx.close();
            this.ctx = new AudioContext();
            this.gainNode = this.ctx.createGain ? this.ctx.createGain() : this.ctx.createGainNode();
            this.gainNode.connect(this.ctx.destination);
        }

        let decoded;
        if(this.musicF !== name){
            let res = await fetch(name, {method: "GET", headers: {"response-type": "arraybuffer"}});
            let data = await res.arrayBuffer();
            decoded = await this.ctx.decodeAudioData(data);
            this.musicData = decoded;
            this.musicF = name;
        }

        if(this.musicSrc && replace)
            this.musicSrc.stop();

        let src = this.ctx.createBufferSource();
        src.buffer = decoded;
        src.connect(this.gainNode);
        this.gainNode.gain.value = 0.7;
        src.loop = true;
        src.start(0);
        this.musicSrc = src;

        if(this.ctx.state == "suspended")
            setTimeout(() => this.set_music(name, volume, false), 100);
    }
}