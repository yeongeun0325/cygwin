/**
 * Created by KICT-20 on 2016-07-19.
 */

const net=require('net');
const PORT=8080;

let object_list=[{
    x:0,
    y:0
}];

net.createServer((socket)=>{
    console.log('connet:'+socket.remoteAddress+':'+socket.remotePort);
    socket.on('error',(evt)=>{
        console.log(evt);
    });
    socket.on('close',(evt)=>{
        console.log('connection closed!')
        console.log(evt);
    });
    socket.on('data',(evt)=>{
        //2byte:header(1004)
        //2byte:request type
        //extra:...
        data=evt;

        let header=data.readInt16LE(0);
        let request_type=data.readInt16LE(2);

        if(header==1004){
            switch(request_type){
                case 100:   //로그인요청
                    break;
                case 200:   //위치정보 전송
                {
                    let index=data.readInt16LE(4);
                    object_list[index].x=data.readFloatLE(8);
                    object_list[index].y=data.readFloatLE(12);
                    console.log(object_list);
                }
                    break;
                case 201:   //위치정보 요청
                {
                    let index=data.readInt16LE(4);
                    let buff=new Buffer(10);
                    buff.writeInt16LE(1004,0);
                    buff.writeFloatLE(object_list[index].x,2);
                    buff.writeFloatLE(object_list[index].y,6);
                    socket.write(buff);
                }
                    break;

            }
        }
        else{
            console.log('packet error');
        }

        console.log("header:"+header);
        console.log('request type:' +request_type);
    })
}).listen(PORT);

console.log('server listen:'+PORT);
