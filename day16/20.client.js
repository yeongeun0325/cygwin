/**
 * Created by KICT-20 on 2016-07-19.
 */

const net=require('net');

const ip ="192.168.0.21";
const PORT=8080;

let socket=new net.Socket();

socket.connect(PORT,ip,()=>{
    console.log("connect to :"+ip+PORT);
    let req={
        name:'ye',
        value:35
    }
    socket.write(JSON.stringify(req));
});

socket.on('data',(evt)=>{
    console.log(String(evt));
    //socket.destroy();
    socket.end("bye");
});
socket.on('error',(evt)=>{

});
socket.on('close',(evt)=>{

});
